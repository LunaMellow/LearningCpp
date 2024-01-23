/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2023, oppgave 2.
 *
 *   Programmet holder orden på en persons lunsj- og middagsbesøk på
 *   ulike spisesteder/kafeer/restauranter.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Spisesteder'-objekter.
 *      - skriver ut ALLE spisesteder, eller ALT om ETT spiested
 *      - legger inn et nytt spisested eller måltid
 *      - skriver alle måltider spist på en gitt dato
 *      - frigir alt allokert minne
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V23_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>
#include <list>
#include <map>
#include <algorithm>               //  find_if, for_each
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


class Maaltid;                     //  Pre-deklarasjon.


/**
 *  Spisested (navn, adresse, telefon og ALLE måltidene spist der).
 */
class Spisested {
  private:
    string navn,                     //  UNIKT navn - sortert på dette.
           adresse,
           tlf;                      //  'tlf' er string, da også KAN
                                     //    inneholde '+', landskode og blanke.
    map <int, Maaltid*> maaltidene;  //  'int' er dato på formatet: MMDD
                                     //    og er UNIKT for hvert spisested.
  public:
    Spisested(const string nvn)  {  navn = nvn;  }      //       (Ferdiglaget)
    Spisested(ifstream & inn);                          //  Oppgave 2I
    ~Spisested();                                       //  Oppgave 2H
    Maaltid* finnMaaltidPaaDato(const int dato) const;  //  Oppgave 2E
    string hentID() const  { return navn; }             //       (Ferdiglaget)
    void lesData();                                     //  Oppgave 2D
    void nyttMaaltid();                                 //  Oppgave 2F
    void skrivAlleData()  const;                        //  Oppgave 2C
    void skrivHovedData() const;                        //  Oppgave 2A
    void skrivTilFil(ofstream & ut) const;              //  EXTRA
};


/**
 *  Baseklassen Maaltid (kun med navnet på måltidets hovedrett).
 */
class Maaltid  {
  protected:
    string hovedrett;         //  Tekst (lunsj/middag) eller blank (middag).

  public:
    Maaltid()  {  }
    Maaltid(ifstream & inn);                            //  Oppgave 2I
    virtual ~Maaltid()  {  }
    virtual void lesData() = 0;             //  = 0 betyr 'pure virtual',
    virtual void skrivData() const = 0;     //    dvs. subklasser MÅ lage dem.
    virtual void skrivTilFil(ofstream & ut) const = 0;  //  EXTRA
};


/**
 *  Avledet klasse Lunsj (kun med om har drukket kaffe eller ei til lunsj).
 */
class Lunsj : public Maaltid  {
  private:
    bool kaffe;               //  Drikker evt. KUN vann i tillegg (til lunsj).

  public:
    Lunsj()  {  }
    Lunsj(ifstream & inn);                              //  Oppgave 2I
    virtual ~Lunsj()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
    virtual void skrivTilFil(ofstream & ut) const;      //  EXTRA
};


/**
 *  Avledet klasse Middag (med evt navn på forrett, dessert og/eller drikken).
 */
class Middag: public Maaltid  {
  private:
    string forrett,           //  Tekst eller blank.
           dessert,           //  Tekst eller blank.
           drikke;            //  Tekst eller blank.

  public:
    Middag()  {  }
    Middag(ifstream & inn);                             //  Oppgave 2I
    virtual ~Middag()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
    virtual void skrivTilFil(ofstream & ut) const;      //  EXTRA
};


Spisested* finnSpisested(const string navn);  //  Oppgave 2B
void frigiAllokertMinne();                    //  Oppgave 2H
void lesFraFil();                             //  Oppgave 2I
void nyttMaaltid();                           //  Oppgave 2F
void nyttSpisested();                         //  Oppgave 2D
void skrivAlleSpisesteder();                  //  Oppgave 2A
void skrivEttSpisested();                     //  Oppgave 2C
void skrivMeny();
void skrivTilFil();                           //  EXTRA
void spistEnGittDato();                       //  Oppgave 2G


list <Spisested*> gSpisestedene;              ///<  ALLE aktuelle spisesteder.


/**
 *  Hovedprogrammet:
 */
int main() {
  char valg;

  lesFraFil();                                     //  Oppgave 2I

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'A': skrivAlleSpisesteder();   break;  //  Oppgave 2A
       case 'E': skrivEttSpisested();      break;  //  Oppgave 2C
       case 'S': nyttSpisested();          break;  //  Oppgave 2D
       case 'M': nyttMaaltid();            break;  //  Oppgave 2F
       case 'D': spistEnGittDato();        break;  //  Oppgave 2G
       default:  skrivMeny();              break;
     }
     valg = lesChar("\nKommando");
  }

  skrivTilFil();                                   //  EXTRA

  frigiAllokertMinne();                            //  Oppgave 2H

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser inn fra fil ALT om ETT spisested.
 *
 *  @param    inn  -  Filen det leses inn fra
 *  @see      Lunsj::Lunsj(...)
 *  @see      Middag::Middag(...)
 */
Spisested::Spisested(ifstream & inn)  {
  int antallMaaltider, dato;
  char maaltidType;
  Maaltid* nyttMaaltid;

  getline(inn, navn);                     //  Leser inn alle egne enkelt-data:
  getline(inn, adresse);
  getline(inn, tlf);

  inn >> antallMaaltider;  inn.ignore();  //  Leser antall måltider på stedet.
  for (int i = 1;  i <= antallMaaltider;  i++)  {  //  Leser ALLE måltidene:
      inn >> dato >> maaltidType;  inn.ignore();   //  Leser dato og type.
      switch (maaltidType)  {                      //  Aktuelt måltid lages,
        case 'L':  maaltidene[dato] = new Lunsj(inn);    break;  // og legges
        case 'M':  maaltidene[dato] = new Middag(inn);   break;  // inn i map.
        default:  cout << "\n\tUlovlig maaltidstype paa filen!\n";
      }
  }
}


/**
 *  Oppgave 2H - Sletter/fjerner ALLE data inni ETT spisested.
 */
Spisested::~Spisested()  {
  for (const auto & val : maaltidene)        //  Går gjennom måltidene:
      delete val.second;                     //  Sletter TILPEKT 'Maaltid'.
  maaltidene.clear();                        //  Sletter ALLE keyer og PEKERE.

// En alternativ måte:
//  while (!maaltidene.empty())  {
//    delete (maaltidene.begin())->second;   //  Sletter 1.TILPEKTE 'Maaltid'.
//    maaltidene.erase(maaltidene.begin());  //  Sletter PARET key og PEKER.
//  }

//  En annen alternativ måte:
//      while (!maaltidene.empty())  {
//        auto it = maaltidene.begin();        //  Iterator til 1.element.
//        delete (it->second);                 //  Sletter TILPEKTE 'Maaltid'.
//        maaltidene.erase(it);                //  Sletter PARET key og PEKER.
//      }
}


/**
 *  Oppgave 2E - Finner og returnerer (om mulig) 'Maaltid' på en gitt dato.
 *
 *  @param    dato  -  Datoen det ønskes å finne et måltid på
 *  @return   Måltidet på gitt dato, evt. nullptr (om ingen dato-match)
 */
Maaltid* Spisested::finnMaaltidPaaDato(const int dato) const  {
  auto it = maaltidene.find(dato);          //  Prøver å finne måltid på dato.
                                            //  Om funn: retur av 'Maaltid'et.
  return ((it != maaltidene.end()) ? (*it).second : nullptr);

// En alternativ måte:
//      for (const auto & val : maaltidene)
//          if (val.first == dato) return val.second;
//      return nullptr;

//  Enda en alternativ måte:
//      for (auto it = maaltidene.begin();  it != maaltidene.end();  it++)
//          if ((*it).first == dato) return (*it).second;
//      return nullptr;

//  Eller bare (men da kan ikke funksjonen være 'const'):
//      return ((maaltidene.find(dato) != maaltidene.end()) ?
//                                              maaltidene[dato] : nullptr);
}


/**
 *  Oppgave 2D - Leser inn spisestedets resterende enkelt-datamedlemmer.
 */
void Spisested::lesData()  {
  cout << "\tAdresse:  ";   getline(cin, adresse);
  cout << "\tTelefon:  ";   getline(cin, tlf);
}


/**
 *  Oppgave 2F - Legger inn (om mulig) nytt måltid på en ny dato.
 *
 *  @see   finnMaaltidPaaDato(...)
 *  @see   Lunsj::Lunsj()
 *  @see   Middag::Middag()
 *  @see   Maaltid::lesData()
 */
void Spisested::nyttMaaltid()  {
  int  dag = lesInt("\tDag   ", 1, 31),      //  Leser dag og måned:
       mnd = lesInt("\tMaaned", 1, 12),
       dato;
  char valg;                                 //  Brukervalg ('L' eller 'M').
  Maaltid* nyttMaaltid;

  dato = mnd * 100 + dag;                    //  Omgjør til formatet:  MMDD

  if (!finnMaaltidPaaDato(dato))  {          //  Ingen måltid på denne datoen:
     do  {
        valg = lesChar("\tL(unsj) eller M(iddag)");
     } while (valg != 'L'  &&  valg != 'M'); //  Sikrer 'L' eller 'M'.

     switch (valg)  {                        //  Lager nytt aktuelt måltid:
       case 'L':  nyttMaaltid = new Lunsj;    break;
       case 'M':  nyttMaaltid = new Middag;   break;
     }

     nyttMaaltid->lesData();                 //  Måltidets data leses inn, og
     maaltidene[dato] = nyttMaaltid;         //    det legges inn i datastr.

  } else
    cout << "\n\tEr allerede et maaltid med denne datoen paa dette stedet!\n";
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT spisested.
 *
 *  @see   skrivHovedData()
 *  @see   Maaltid::skrivData()
 */
void Spisested::skrivAlleData() const  {
  cout << "\n\tFolgende er lagret om dette stedet:\n";

  skrivHovedData();                           //  Skriver alle HOVEDdata.

  if (!maaltidene.empty())  {                 //  Måltider er spist på stedet:
     cout << "\tMaaltidene:\n";
     for (const auto & val : maaltidene)  {   //  Skriver ut datoen på
         cout << '\t' << setw(2) << (val.first % 100)  // formatet  DD/MM:
              << '/'    << setw(2) << (val.first / 100) << ":  ";
         (val.second)->skrivData();           //  Alle måltidsdata skrives ut.
     }
  }
}


/**
 *  Oppgave 2A - Skriver ut på skjermen enkelt-datamedlemmene.
 */
void Spisested::skrivHovedData() const  {
  cout << '\t' << navn << ",   " << adresse << "   (" << tlf << ")  - "
       << maaltidene.size() << " maaltid\n";
}

/**
 *  EXTRA - Skriver ut på fil ALLE spisestedets data.
 *
 *  @param    ut  -  Filen det skal skrives til
 *  @see      Maaltid::skrivTilFil(...)
 */
void Spisested::skrivTilFil(ofstream & ut) const  {
  ut << navn << '\n' << adresse << '\n' << tlf << '\n'
     << maaltidene.size() << '\n';

  for (const auto & val : maaltidene)  {
      ut << val.first << ' ';                 //  Skriver dato, og
      (val.second)->skrivTilFil(ut);          //    ALLE andre datamedlemmer.
  }
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser inn 'Maaltid'ets eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Maaltid::Maaltid(ifstream & inn)  {
  getline(inn, hovedrett);
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser inn fra fil 'Lunsj' sitt eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Lunsj::Lunsj(ifstream & inn) : Maaltid(inn)  {
  char ka;
  inn >> ka;   inn.ignore();
  kaffe = (ka == '+');                      //  Omgjør '+'/'-' til bool-verdi.
}


/**
 *  Oppgave 2F - Leser inn (hoved)retten under lunsjen.
 */
void Lunsj::lesData()  {
  do  {
    cout << "\tHovedrett:  ";   getline(cin, hovedrett);
  } while (!hovedrett.length());         //  Sikrer at ikke bare ENTER/blankt.

  kaffe = (lesChar("\tKaffe (j/N)") == 'J');
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Lunsj::skrivData() const  {
  cout << hovedrett << ",  drakk " << (!kaffe ? "IKKE " : "") << "kaffe\n";
}


/**
 *  EXTRA - Skriver ut til fil ALLE datamedlemmer.
 *
 *  @param    ut  -  Filen det skrives ut til
 */
void Lunsj::skrivTilFil(ofstream & ut) const  {
  ut << "L " << hovedrett << '\n' << (kaffe ? "+" : "-") << '\n';

}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser inn fra fil 'Middag' sine tre datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Middag::Middag(ifstream & inn) : Maaltid(inn)  {
  getline(inn, forrett);
  getline(inn, dessert);
  getline(inn, drikke);
}


/**
 *  Oppgave 2F - Leser inn evt rettene og drikken under middagen.
 */
void Middag::lesData()  {
  do  {
    cout << "\tForrett:    ";   getline(cin, forrett);    //  Minst en MÅ
    cout << "\tHovedrett:  ";   getline(cin, hovedrett);  //    være ulikt
    cout << "\tDessert:    ";   getline(cin, dessert);    //    bare blankt:
  } while (!forrett.length()  &&  !hovedrett.length()  &&  !dessert.length());

  cout << "\tDrikke:     ";   getline(cin, drikke);
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Middag::skrivData() const  {
  cout << '\n';
  if (forrett.length())   cout << "\t\tForrett:    " << forrett << '\n';
  if (hovedrett.length()) cout << "\t\tHovedrett:  " << hovedrett << '\n';
  if (dessert.length())   cout << "\t\tDessert:    " << dessert << '\n';
  if (drikke.length())    cout << "\t\tDrikke:     " << drikke << '\n';
}


/**
 *  EXTRA - Skriver ut til fil ALLE datamedlemmer.
 *
 *  @param    ut  -  Filen det skrives ut til
 */
void Middag::skrivTilFil(ofstream & ut) const  {
  ut << "M " << hovedrett << '\n'
     << forrett << '\n'<< dessert << '\n'<< drikke << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------


/**
 *  Oppgave 2B- Finner og returnerer (om mulig) peker til et gitt spisested.
 *
 *  @param    navn  -  Navnet på det søkte spisestedet
 *  @return   Peker til aktuelt navngitt spisested eller nullptr
 *  @see      Spisested::hentID()
 */
Spisested* finnSpisested(const string navn)  {     //  Prøver å finne navngitt
  auto it = find_if(gSpisestedene.begin(), gSpisestedene.end(), //  spisested:
                   [navn] (const auto & val)
                          {  return (val->hentID() == navn); } );
  return ((it != gSpisestedene.end())  ?  (*it)  :  nullptr);

// En alternativ måte:
//   for (const auto & val : gSpisestedene)      //  Går gjennom spisestedene:
//       if(val->hentID() == navn) return val;   //  Funn - matchende navn.
//   return nullptr;                             //  Ingen funn/matchende navn.
}


/**
 *  Oppgave 2H - Frigir/sletter ALT allokert minne/memory.
 *
 *  @see   Spisested::~Spisested()
 */
void frigiAllokertMinne()  {
  for (const auto & val : gSpisestedene)
      delete val;                         //  Fjerner ALLE de TILPEKTE.
  gSpisestedene.clear();                  //  Fjerner ALLE PEKERNE.

//  En alternativ måte:
//  while (!gSpisestedene.empty()) {      //  Ennå spisesteder igjen:
//    delete gSpisestedene.front();       //  Sletter 1.TILPEKTE 'Spisested'.
//    gSpisestedene.pop_front();          //  Fjerner den 1.PEKEREN.
//  }

//  Enda en alternativ måte:
//    for_each(gSpisestedene.begin(), gSpisestedene.end(),
//             [] (auto & val) {  delete val; } );
//    gSpisestedene.clear();
}



/**
 *  Oppgave 2I - Leser ALLE spisestedene med måltider inn fra fil.
 *
 *  @see   Spisested::Spisested(...)
 *  @see   Spisested::hentID()
 */
void lesFraFil()  {
  ifstream innfil("EX_V23_SPISESTEDER.DTA");
  int  antallSpisesteder;                     // Antall spisesteder på filen.

  if (innfil)  {                              //  Filen finnes:
    cout << "\n\tLeser inn fra filen 'EX_V23_SPISESTEDER.DTA' .....\n\n";
    innfil >> antallSpisesteder;   innfil.ignore();
                                              //  Leser ALLE spisestedene, og
    for (int i = 1; i <= antallSpisesteder; i++)  //  legger inn i datastr:
        gSpisestedene.push_back(new Spisested(innfil));
                                              //  Sorterer spisestedene:
    gSpisestedene.sort([] (Spisested* s1, Spisested* s2)
                          {  return (s1->hentID() < s2->hentID()); }  );

    innfil.close();                           //  Lukker filen manuelt.
  } else                                      //  Filen finnes IKKE:
    cout << "\n\n\tFant ikke filen 'EX_V23_SPISESTEDER.DTA'!\n\n";
}


/**
 *  Oppgave 2F - Legger inn (om mulig) ett nytt måltid på et spisested.
 *
 *  @see   finnSpisested(...)
 *  @see   Spisested::nyttMaaltid()
 */
void nyttMaaltid()  {
  Spisested* spisested;
  string navn;

  if (!gSpisestedene.empty())  {                //  Spisested(er) finnes:
     cout << "\tSpisesteds navn:  ";   getline(cin, navn);
     spisested = finnSpisested(navn);           //  Navngitt spisested finnes?

     if (spisested)                             //  Ja:
        spisested->nyttMaaltid();               //  Nytt måltid legges inn.
     else
        cout << "\n\tIngen spisested med dette navnet!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede spisesteder!\n\n";
}


/**
 *  Oppgave 2D - Legger inn (om mulig) ett nytt spisested.
 *
 *  @see   Spisested::Spisested(...)
 *  @see   Spisested::lesData()
 *  @see   Spisested::hentID()
 */
void nyttSpisested()  {
  string navn;
  Spisested* nyttSpisested;

  cout << "\tNytt spisesteds navn:  ";   getline(cin, navn);

  if (!finnSpisested(navn))  {             //  Navngitt spisested finnes IKKE:
     nyttSpisested = new Spisested(navn);      //  Lager et nytt.
     nyttSpisested->lesData();                 //  Dets data leses inn.
     gSpisestedene.push_back(nyttSpisested);   //  Det legges inn i datastr.
     gSpisestedene.sort([] (Spisested* s1, Spisested* s2)  //  Sortering:
                           {  return (s1->hentID() < s2->hentID()); }  );
  } else
     cout << "\n\tFinnes allerede et spisested med dette navnet!\n";
}


/**
 *  Oppgave 2A - Skriver ut på skjermen HOVEDdataene om ALLE spisesteder.
 *
 *  @see   Spisested::skrivHovedData()
 */
void skrivAlleSpisesteder()  {
  if (!gSpisestedene.empty())  {             //  Spisesteder finnes:
     cout << "\nHoveddatene om de hittil " << gSpisestedene.size()
          << " registrerte/lagrede spisestedene:\n";

    for (const auto & val : gSpisestedene)   //  Alle skrives ut på skjermen:
        val->skrivHovedData();

//  En alternativ måte:
//          for_each(gSpisestedene.begin(), gSpisestedene.end(),
//                  [] (const auto & val) { val->skrivHovedData(); } );
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede spisesteder!\n\n";
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT gitt spisested.
 *
 *  @see   finnSpisested(...)
 *  @see   Spisested::skrivAlleData()
 */
void skrivEttSpisested()  {
  Spisested* spisested;
  string navn;

  if (!gSpisestedene.empty())  {             //  Spisesteder finnes:
     cout << "\tSpisesteds navn:  ";   getline(cin, navn);
     spisested = finnSpisested(navn);        //  Navngitt spisested finnes?

     if (spisested)                          //  Ja:
        spisested->skrivAlleData();          //  ALLE dets data skrives ut:
     else
        cout << "\n\tIngen spisested med dette navnet!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede spisesteder!\n\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   A  - skriv Alle spisesteder\n"
       << "   E  - skriv Ett spisested\n"
       << "   S  - nytt Spisested\n"
       << "   M  - nytt Maaltid\n"
       << "   D  - steder spist paa en gitt Dato\n"
       << "   Q  - Quit / avslutt\n";
}

/**
 *  EXTRA - Skriver ALLE spisestedene med måltider ut til fil.
 *
 *  @see   Spisested::skrivTilFil(...)
 */
void skrivTilFil()  {
  ofstream utfil("EX_V23_SPISESTEDER.DT2");

  cout << "\n\tSkriver alle data til filen 'EX_V23_SPISESTEDER.DT2' .....\n";

  utfil <<  gSpisestedene.size() << '\n';    //  Skriver antallet i listen.

  for (const auto & val : gSpisestedene)     //  Hvert spisested skriver selv:
      val->skrivTilFil(utfil);

  utfil.close();                             //  Lukker filen manuelt.
}


/**
 *  Oppgave 2G - Skriver ut på skjermen (om mulig) alle måltider spist en
 *               gitt dato, og på hvilket spisested dette har forekommet.
 *
 *  @see   Spisested::finnMaaltidPaaDato(...)
 *  @see   Spisested::hentID()
 *  @see   Maaltid::skrivData()
 */
void spistEnGittDato()  {
  Maaltid* maaltid;
  int  dag, mnd, dato;
  bool funn = false;


  if (!gSpisestedene.empty())  {            //  Spisesteder finnes:
     dag = lesInt("\tDag   ", 1, 31);       //  Leser dag og måned:
     mnd = lesInt("\tMaaned", 1, 12);

     dato = mnd * 100 + dag;                //  Omgjør til formatet:  MMDD

     cout << "\n\tSpist paa denne datoen paa folgende steder:\n";

     for (const auto & val : gSpisestedene)  {   //  Går gjennom spisestedene:
         maaltid = val->finnMaaltidPaaDato(dato);  //  Måltid på datoen?
         if (maaltid)  {                           //  Ja:
            funn = true;                           //  Minst EN utskrift.
            cout << "\n\tSted: " << val->hentID() << '\t'; // Spisestednavn
// Ovenstående setning kan evt. erstattes med bare:   val->skrivHovedData();
            maaltid->skrivData();                          //   og måltidets
         }                                                 //   data skrives.
     }
     if (!funn)                                  //  Ingen måltid noe sted
        cout << "\n\t\tIngen!\n";                //    på denne datoen.
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede spisesteder!\n\n";
}
