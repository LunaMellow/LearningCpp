/**
 *   Løsningsforslag til konteeksamen i OOProg (i C++), august 2023, oppg 2.
 *
 *   Programmet holder orden på ulikt militært personell sine
 *   tatte (ferdighets)merker.
 *
 *   Programmet:
 *      - inneholder:  EN <map> med navn og pekere til 'Personell'-objekter
 *      -              'Personell' som bl.a. inneholder vedkommendes merker
 *      - lar brukeren legge inn:  ET nytt personell (med alle sine data)
 *      -                          ET nytt merke (automatisk) hos et personell
 *      - skriver at ALT personell  eller  ALT om ETT personell
 *      - leser HELE datastrukturen fra fil
 *
 *   @file     EX_S23_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream
#include <string>
#include <vector>
#include <map>
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const float MINPOENG =     1,      ///<  Minimum antall poeng å få.
            MAXPOENG = 10000;      ///<  Maksimum antall poeng å få.
const int   MINTIME  =     0,      ///<  Minimum time brukt.
            MAXTIME  =    10;      ///<  Maksimum time brukt.


/**
 *  Valor (merkenes ulike valører: Bronse, Sølv eller Gull).
 */
enum Valor {  Bronse,  Solv,  Gull  };


class Merke;                      //  PRE-deklarasjon, da 'Personell' henviser
                                  //    til 'Merke' som defineres lengre nede.

/**
 *  Personell (med fornavn, miltær grad og tjenestested).
 */
class Personell {
  private:                         //  'etternavn' er 'first' i map'en.
    string fornavn,
           grad,                   //  Militær grad.
           sted;                   //  Tjenestested.
    vector <Merke*> merkene;       //  Alle merkene totalt tatt.

   int antallMerker(const string tittel, const Valor valor) const;  // Oppg.2G
   Merke* lagMerke(const char type, const string t, const Valor v); // Oppg.2C
   Valor  lesValor() const;                   //  (Ferdiglaget nedenfor)

  public:
    Personell()  {    }
    Personell(ifstream & inn);                //  Oppgave 2I
    ~Personell();
    void lesData();                           //  Oppgave 2A
    void nyttMerke();                         //  Oppgave 2E
    void nyttMerke2();                        //  Oppgave 2H
    void skrivHovedData() const;              //  Oppgave 2B
    void skrivAlleData() const;               //  Oppgave 2F
};


/**
 *  Merke (med tittel/beskrivelse, dato tatt og merkets valør).
 */
class Merke {
  private:
    string tittel;                //  Tittel/beskrivelse av merket.
    int    dato;                  //  På formen:  ÅÅMMDD   (år-måned-dag).
    Valor  valor;                 //  Merkets valør:  Bronse, Solv eller Gull.

  public:
    Merke(const string t, const Valor v)  {  tittel = t;  valor = v; }
    Merke(ifstream & inn);                    //  Oppgave 2I
    string hentTittel()  {  return tittel;  }
    Valor  hentValor()   {  return valor;   }
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


/**
 *  PoengMerke (med poengene oppnådd ifm. merketagelsen).
 */
class PoengMerke : public Merke {
  private:
    float  poeng;

  public:
    PoengMerke(const string t, const Valor v) : Merke(t, v)  {  }
    PoengMerke(ifstream & inn);               //  Oppgave 2I
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


/**
 *  TidMerke (tiden brukt ifm. merketagelsen).
 */
class TidMerke : public Merke {
  private:
    int tid;             //  Tid i hele sekunder (= time*3600 + min*60 + sek).

  public:
    TidMerke(const string t, const Valor v) : Merke(t, v)  {  }
    TidMerke(ifstream & inn);                 //  Oppgave 2I
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


void  lesFraFil();                             //  Oppgave 2I
void  nyttMerke();                             //  Oppgave 2D
void  nyttPersonell();                         //  Oppgave 2A
void  skrivAltOmEttPersonell();                //  Oppgave 2F
void  skrivAltPersonell();                     //  Oppgave 2B
void  skrivMeny();


map <string, Personell*> gPersonellet;     ///<  ALT personell som tar merker.


/**
 *  Hovedprogrammet.
 */
int main() {
  char valg;

  lesFraFil();                                        //  Oppgave 2I

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'P':  nyttPersonell();            break;  //  Oppgave 2A
       case 'A':  skrivAltPersonell();        break;  //  Oppgave 2B
       case 'M':  nyttMerke();                break;  //  Oppgave 2D
       case 'E':  skrivAltOmEttPersonell();   break;  //  Oppgave 2F
       default:   skrivMeny();                break;
     }
     valg = lesChar("\nKommando");
  }

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 *   @see      PoengMerke::PoengMerke(...)
 *   @see      TidMerke::TidMerke(...)
 */
Personell::Personell(ifstream & inn)  {
  int  antMerker;
  char merkeType;

  getline(inn, fornavn);               //  Leser fra filen: fornavn
  inn >> grad;   inn.ignore();         //                   grad
  getline(inn, sted);                  //                   tjenestested

  inn >> antMerker;  inn.ignore();     //                   antall merker.
  for (int i = 1;  i <= antMerker;  i++)  {
      inn >> merkeType;  inn.ignore();
      switch (merkeType)  {            //  Nytt merke opprettes og leser selv:
        case 'P':  merkene.push_back(new PoengMerke(inn));       break;
        case 'T':  merkene.push_back(new TidMerke(inn));         break;
        default:  cout << "\n\tUgyldig merketype på fila!\n\n";  break;
      }
  }
}


/**
 *   Sletter ALLE merkene og ALLE pekerne til disse.
 */
Personell::~Personell()  {
  for (auto & val : merkene)           //  Sletter/fjerner ALLE merkene:
      delete val;
  merkene.clear();                     //  Sletter alle PEKERNE til merkene.
}


/**
 *   Oppgave 2G - Finner og returnerer antallet av et gitt merke.
 *
 *   @param    tittel  -  Merkets tittel/navn/beskrivelse
 *   @param    valor   -  Merkets valør (Bronse, Solv, Gull)
 *   @return   Antall merker med EKSAKT 'tittel' OG 'valor'
 *   @see      Merke::hentTittel()
 *   @see      Merke::hentValor()
 */
int Personell::antallMerker(const string tittel, const Valor valor) const  {
  int antall = 0;
  for (const auto & val : merkene)     //  Finner antallet av aktuelt merke:
      if (val->hentTittel() == tittel  &&  val->hentValor() == valor)
        antall++;

  return antall;
}


/**
 *   Oppgave 2C - Oppretter og returnerer et aktuelt merke.
 *
 *   @param    type  -  Aktuell merketype ('P/T') å lage nytt merke av
 *   @param    t     -  Merkets tittel/navn/beskrivelse
 *   @param    v     -  Merkets valør (Bronse, Solv, Gull)
 *   @return   Peker til nyopprettet aktuelt merke
 *   @see      PoengMerke::PoengMerke(...)
 *   @see      TidMerke::TidMerke(...)
 */
Merke* Personell::lagMerke(const char type, const string t, const Valor v) {
  switch (type)  {
    case 'P':  return (new PoengMerke(t, v));  //  Lager og returnerer
    case 'T':  return (new TidMerke(t, v));    //    aktuelt merke.
    default:   cout << "\n\tUgyldig merketype!\n";  return nullptr;
  }
}



/**
 *  Oppgave 2A - Leser inn ALLE egne data fra tastaturet.
 */
void Personell::lesData()  {
  cout << "\tFornavn:      ";  getline(cin, fornavn);
  cout << "\tGrad:         ";  getline(cin, grad);
  cout << "\tTjenestested: ";  getline(cin, sted);
}


/**
 *   Leser inn og returnerer valør for ett merke.
 *
 *   @return   Merkevalør (Bronse, Solv, Gull)
 */
Valor Personell::lesValor() const  {
  char tegn;

  do  {
     tegn = lesChar("\tValor (B(ronse), S(olv), G(ull))"); //  Leser og sikrer
  } while (tegn != 'B'  &&  tegn != 'S'  &&  tegn != 'G'); //    lovlig tegn.

  switch (tegn)  {
    case 'B':   return Bronse;                 //  Returnerer aktuell merke-
    case 'S':   return Solv;                   //    valør ut fra tegnet.
    case 'G':   return Gull;
  }
}


/**
 *   Oppgave 2E -  Legger inn ett nytt merke (versjon 1).
 *
 *   @see      skrivAlleData()
 *   @see      lesValor()
 *   @see      lagMerke(...)
 *   @see      Merke::lesData()
 *   @see      Merke::skrivData()
 */
void Personell::nyttMerke()  {
  Merke* nyttM;
  string tittel;
  Valor  valor;
  char   merkeType;

  skrivAlleData();                                     //  Skriver ALT hittil.

  cout << "\n\tMerketittel: ";   getline(cin, tittel); //  Leser tittel og
  valor = lesValor();                                  //    merke-valør.

  do  {                                                //  Leser og sikrer
    merkeType = lesChar("\tMerketype (P(oeng), T(id))"); //  lovlig
  }  while (merkeType != 'P'  &&  merkeType != 'T');     //  merke-type.

  nyttM = lagMerke(merkeType, tittel, valor);          //  Oppretter nytt
                                                       //    aktuelt merke.
  nyttM->lesData();                            //  Merkets andre data leses.

  merkene.push_back(nyttM);                    //  Legges bakerst i vectoren.

  cout << "\n\tMerkene er naa:\n";
  for (const auto & val : merkene)             //  Alle merkene nå skrives:
      val->skrivData();                        //  Hvert merke skriver selv.
}


/**
 *   Oppgave 2H - Legger inn ett nytt merke (versjon 2).
 *
 *   @see   skrivAlleData()
 *   @see   antallMerker(...)
 *   @see   lagMerke(...)
 *   @see   Merke::lesData()
 *   @see   Merke::skrivData()
 */
void Personell::nyttMerke2()  {
  Merke* nyttM;
  string tittel;
  char   mType;
  int    antall;

  skrivAlleData();                             //  Skriver ALT hittil.
  cout << "\n\tMerketittel: ";   getline(cin, tittel);  //  Leser tittel, men
                                                        //    IKKE valøren.
  do  {
    mType = lesChar("\tMerketype (P(oeng), T(id))"); // Leser og sikrer lovlig
  }  while (mType != 'P'  &&  mType != 'T');         //   merke-type.

  antall = antallMerker(tittel, Gull);         //  Finner antall gull hittil.
  if (antall > 0)                              //  Minst ett gull allerede:
     nyttM = lagMerke(mType,tittel, Gull);     //  Får da et nytt gull.
  else  {                                      //  0 (null) gull hittil:
     antall = antallMerker(tittel, Solv);      //  Finner antall sølv hittil.
     if (antall == 3)                          //  3 sølv hittil:
        nyttM = lagMerke(mType, tittel, Gull); //  Får da det første gullet.
     else if (antall > 0)                      //  1 eller 2 sølv hittil:
        nyttM = lagMerke(mType, tittel, Solv); //  Får da et nytt sølv.
     else {                                    //  0 (null) sølv hittil:
        antall = antallMerker(tittel, Bronse); // Finner antall bronse hittil.
        if (antall == 3)                       //  3 bronse hittil:
           nyttM = lagMerke(mType, tittel, Solv); // Får da det første sølvet.
        else                                   //  0, 1 eller 2 bronse hittil:
           nyttM = lagMerke(mType, tittel, Bronse);   //  Får da en ny bronse.
     }
  }

  nyttM->lesData();                            //  Merkets andre data leses.

  merkene.push_back(nyttM);                    //  Legges bakerst i vectoren.

  cout << "\n\tMerkene er naa:\n";             //  Alle merkene nå skrives:
  for (const auto & val : merkene)             //  Hvert merke skriver selv.
      val->skrivData();
}


/**
 *   Oppgave 2B - Skriver alle egne HOVEDdata ut på skjermen.
 */
void Personell::skrivHovedData() const  {
  cout << ", " << fornavn << "    " << grad << "  tjenestested: " << sted
       << "\n\t\tAntall merker: " << merkene.size() << '\n';
}


/**
 *   Oppgave 2F - Skriver ALLE egne data ut på skjermen.
 *
 *   @see   skrivHovedData()
 *   @see   Merke::skrivData()
 */
void Personell::skrivAlleData() const  {
  skrivHovedData();                            //  HOVEDdataene skrives.
  cout << "\tDette er merkene:\n";
  for (const auto & val : merkene)             //  Alle merkene skrives:
      val->skrivData();                        //  Hvert merke skriver selv.
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
Merke::Merke(ifstream & inn)  {
  char valorr;
  inn >> dato >> valorr >> tittel;  inn.ignore();  //  Leser alle egne data.
  switch (valorr)  {
    case 'B':  valor = Bronse;    break;           //  Tegnet 'B/S/G' gjøres
    case 'S':  valor = Solv;      break;           //    om til aktuell
    case 'G':  valor = Gull;      break;           //    merke-valør.
    default:   cout << "\n\tUgyldig merketype på fila!\n\n";   break;
  }
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void Merke::lesData()  {
  dato = lesInt("\tDato", 100101, 301231);           //  Leser alle egne data.
}


/**
 *   Oppgave 2F - Skriver ALLE egne data ut på skjermen.
 */
void Merke::skrivData() const  {
  switch (valor)  {
    case Bronse:  cout << "Bronse";    break;         // enum-verdi skrives ut
    case Solv:    cout << "Solv  ";    break;         //   som aktuell tekst:
    case Gull:    cout << "Gull  ";    break;
  }
  cout << "  " << tittel << "   " << (dato % 100) << '/'  //  Utskriftsformat:
       << ((dato / 100) % 100) << '-' << dato / 10000;    //     DD/MM-ÅÅ
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
PoengMerke::PoengMerke(ifstream & inn) : Merke(inn)  {
  inn >> poeng;   inn.ignore();                      //  Leser alle egne data.
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *   @see   Merke::lesData()
 */
void PoengMerke::lesData()  {
  Merke::lesData();                           //  Baseklassen leser sine data.
  poeng = lesFloat("\tPoeng", MINPOENG, MAXPOENG);  //  Leser egne data.
}


/**
 *   Oppgave 2F - Skriver ALLE egne (og baseklassens) data ut på skjermen.
 *
 *   @see   Merke::skrivData()
 */
void PoengMerke::skrivData() const  {
  cout << "\t\tPOENG: ";
  Merke::skrivData();                       //  Baseklassen skriver sine data.
  cout << "  poeng: " << poeng << '\n';     //  Skriver egne data.
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
TidMerke::TidMerke(ifstream & inn) : Merke(inn)  {
  inn >> tid;   inn.ignore();                        //  Leser alle egne data.
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *   @see   Merke::lesData()
 */
void TidMerke::lesData()  {
  int time, min, sek;
  Merke::lesData();                           //  Baseklassen leser sine data.
  time = lesInt("\tTime  ", MINTIME, MAXTIME); //  Leser egne data:
  min  = lesInt("\tMinutt", 0, 59);
  sek  = lesInt("\tSekund", 0, 59);
  tid = (time*3600) + (min*60) + sek;         //  Beregner TOTALT i sekunder.
}


/**
 *   Oppgave 2F - Skriver ALLE egne (og baseklassens) data ut på skjermen.
 *
 *   @see   Merke::skrivData()
 */
void TidMerke::skrivData() const  {
  cout << "\t\tTID:   ";
  Merke::skrivData();                      //  Baseklassen skriver sine data.
  cout << "  tid: " << (tid / 3600) << ':' //  Skriver egne data, på formatet:
       << ((tid % 3600) / 60) << ':' << tid % 60 << '\n';  //  time:min:sek
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser ALT personell og ALLE deres merker inn fra fil.
 *
 *  @see   Personell::Personell(...)
 */
void lesFraFil()  {
  ifstream innfil("EX_S23_MERKER.DTA");
  int         antallPersonell;               //  Antall personell på filen.
  string      etternavn;                     //  etternavn = 'first'

  if (innfil) {                              //  Filen finnes:
      cout << "\n\n\tLeser fra filen 'EX_S23_MERKER.DTA'......\n\n";
                                              //  Leser antallet på filen:
      innfil >> antallPersonell;   innfil.ignore();
                                              //  Leser ALT personellet:
      for (int i = 1; i <= antallPersonell; i++)  {
          getline(innfil, etternavn);         //  Leser 'first'.
          gPersonellet[etternavn] = new Personell(innfil);
      }
      innfil.close();                         //  Lukker filen manuelt.
  } else                                      //  Filen finnes IKKE:
      cout << "\n\n\tFant ikke filen 'EX_S23_MERKER.DTA'!\n\n";
}


/**
 *  Oppgave 2D - Legger inn (om mulig) et nytt merke.
 *
 *  @see   Personell::nyttMerke()
 */
void nyttMerke()  {
  string navn;

  cout << "\n\tNytt merke hos etternavn: ";   getline(cin, navn);

  auto it = gPersonellet.find(navn);      //  Prøver å finne personellet.

  if (it != gPersonellet.end())  {        //  Ble funnet:
      cout << "\n\t" << (*it).first;      //  Skriver etternavnet.
      ((*it).second)->nyttMerke2();       //  Nytt merke legges inn hos
  } else                                  //    vedkommende personell.
      cout << "\n\n\tIngen personell med dette etternavnet!\n\n";
}


/**
 *  Oppgave 2A - Legger inn (om mulig) et nytt personell.
 *
 *  @see   Personell::Personell()
 *  @see   Personell::lesData()
 */
void nyttPersonell()  {
  Personell* nyttPersonell;
  string navn;

  cout << "\n\tUNIKT nytt etternavn: ";   getline(cin, navn);

  if (gPersonellet.find(navn) == gPersonellet.end())  {  //  Finnes IKKE:
      nyttPersonell = new Personell();                   //  Lager ny.
      nyttPersonell->lesData();                          //  Leser selv data.
      gPersonellet[navn] = nyttPersonell;                //  Legges inn.
  } else
      cout << "\n\n\tFinnes allerede et personell med dette etternavnet!\n\n";
}


/**
 *  Oppgave 2F - Skriver ut ALT om ETT personell.
 *
 *  @see   Personell::skrivAlleData()
 */
void skrivAltOmEttPersonell()  {
  string etternavn;

  if (!gPersonellet.empty())  {                        //  IKKE tomt:
     cout << "\tEtternavn: ";   getline(cin, etternavn);
     auto it = gPersonellet.find(etternavn);
     if (it != gPersonellet.end())  {                  //  Personellet funnet:
        cout << "\n\t" << (*it).first;                 //  Skriver etternavn.
        (*it).second->skrivAlleData();                 //  Skriver ALT annet.
     } else
        cout << "\n\tIkke noe personell med dette etternavnet!\n\n";
  } else
     cout << "\n\tIkke noe personell registrert ennaa!\n\n";
}


/**
 *  Oppgave 2B - Skriver ut HOVEDdata om ALT personell.
 *
 *  @see   Personell::skrivHovedData()
 */
void skrivAltPersonell()  {
  for (const auto & val : gPersonellet)  {  //  Går igjennom ALT personellet:
      cout << '\t' << val.first;            //  Personellets etternavn.
      (val.second)->skrivHovedData();       //  Hvert personell skriver
  }                                         //    resten selv.
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   P  - nytt Personell\n"
       << "   A  - skriv ut Alt personellet\n"
       << "   M  - nytt Merke\n"
       << "   E  - skriv ut alt om Ett personell\n"
       << "   S  - statistikk over medaljer\n"
       << "   Q  - Quit / avslutt\n";
}
