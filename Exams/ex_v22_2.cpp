/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2022, oppgave 2.
 *
 *   Programmet holder orden på ulike personer (barn og voksne) sine "kjøp"
 *   på ett eller annet sted (arrangement/fornøyelsespark/dyrepark/lekeland).
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Person'-objekter.
 *        I praksis er dette enten 'Barn'- eller 'Voksen'-objekter.
 *      - lar brukeren legge inn EN ny person (med alle sine data)
 *      - lar en person kjøpe/hente EN vare
 *      - lar en person eller hel familie/gruppe dra/reise/sjekke ut
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V22_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>
#include <vector>
#include <list>
#include <algorithm>               //  find_if, count(_if)
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int PRIS =  20;              ///<  Den vanligste prisen pr.enhet/ting.


/**
 *  Vare (de ulike varene brukerne totalt kan hente ut/kjøpe).
 */
enum Vare { polse, popcorn, godtepose,    //  Menyvalg:   P  C  G
            sjokolade, is, brus,          //              S  I  B
            hamburger, kaffe };           //              H  K


/**
 *  Person (med UNIKT nummer, navn, mobilnr og ALLE vedkommendes kjøp).
 */
class Person {
  private:
    int nummer,                               //  ID - sortert på dette.
        mobil;
    string navn;

    void skrivKjop(const Vare vare) const;    //  Oppgave 2F

  protected:
    vector <Vare> kjopene;                    //  ALLE kjøpene/uthentinger.

    int  antallKjop(const Vare vare) const;   //  Oppgave 2E
    void registrerEttKjop(const char kjop);   //        (Ferdiglaget)

  public:
    Person(const int nr)  { nummer = nr;   }  //        (Ferdiglaget)
    Person(ifstream & inn);                   //  Oppgave 2J
    int  hentID() const   { return nummer; }  //        (Ferdiglaget)
    void lesData();                           //  Oppgave 2A
    void skrivData() const;                   //  Oppgave 2F
    virtual void lesKjop() = 0;               //  Oppgave 2C - Pure virtual,
                                              //     dvs. "barna" MÅ lage den.
    virtual int  skalBetale() const = 0;      //  Oppgave 2G - Pure virtual.
    virtual void skrivTilFil(ofstream & ut) const; //  EXTRA
};


/**
 *  Barn (UTEN egne datamedlemmer, men med virtuelle funksjoner).
 */
class Barn : public Person {
  public:
    Barn(const int nr)   : Person(nr)  {  }   //        (Ferdiglaget)
    Barn(ifstream & inn) : Person(inn) {  }   //        (Ferdiglaget)
    virtual void lesKjop();                   //  Oppgave 2C
    virtual int  skalBetale() const;          //  Oppgave 2G
    virtual void skrivTilFil(ofstream & ut) const; //  EXTRA
};


/**
 *  Voksen (UTEN egne datamedlemmer, men med virtuelle funksjoner).
 */
class Voksen : public Person {
  public:
    Voksen(const int nr)   : Person(nr)  {  } //        (Ferdiglaget)
    Voksen(ifstream & inn) : Person(inn) {  } //        (Ferdiglaget)
    virtual void lesKjop();                   //  Oppgave 2C
    virtual int  skalBetale() const;          //  Oppgave 2G
    virtual void skrivTilFil(ofstream & ut) const; //  EXTRA
};


void avreiseFamilie();                        //  Oppgave 2I
int  avreisePerson();                         //  Oppgave 2H
void lesFraFil();                             //  Oppgave 2J
void nyPerson();                              //  Oppgave 2B
void personKjoperEnVare();                    //  Oppgave 2D
void skrivMeny();
void skrivTilFil();                           //  EXTRA


int  gSisteNummer = 0;                   ///<  Siste FORTLØPENDE nummer brukt.
list <Person*> gPersonene;               ///<  ALLE personene som kjøper noe.


/**
 *  Hovedprogrammet:
 */
int main() {
  char valg;

  lesFraFil();                                    //  Oppgave 2J

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'N': nyPerson();              break;  //  Oppgave 2B
       case 'K': personKjoperEnVare();    break;  //  Oppgave 2D
       case 'E': avreisePerson();         break;  //  Oppgave 2H
       case 'F': avreiseFamilie();        break;  //  Oppgave 2I
       default:  skrivMeny();             break;
     }
     valg = lesChar("\nKommando");
  }

  skrivTilFil();                                   //  EXTRA

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2J - Leser inn ALLE egne data fra fil.
 *
 *  @param  inn   -  Filobjektet det leses inn data fra
 *  @see    registrerEttKjop(...)
 */
Person::Person(ifstream & inn) {
  int  antallKjop;
  char kjop;

  inn >> nummer >> mobil >> antallKjop;  inn.ignore();

  for (int i = 1;  i <= antallKjop;  i++)  {
     inn >> kjop;
     registrerEttKjop(kjop);                //  Kjøpet/uthentingen unnalagres.
  }
  inn.ignore();
  getline(inn, navn);
}


/**
 *  Oppgave 2E - Finner og returnerer antall kjøp/uthentinger av en gitt vare.
 *
 *  @param    vare   -  Varen det skal sjekkes antall kjøp/uthentinger av
 *  @return   Antall kjøp/uthentinger av den gitte varen
 */
int Person::antallKjop(const Vare vare) const  {
  int antall = 0;

  for (const auto & val : kjopene)
      if (val == vare)  antall++;            //  Av aktuell type:  teller opp

  return antall;

//  Eller HELE innmaten bare:
//     return (count(kjopene.begin(), kjopene.end(), vare));

//  Evt heller:
//     return (count_if(kjopene.begin(), kjopene.end(),
//            [vare](const auto & val){ return val == vare; } ));
}


/**
 *  Oppgave 2A - Leser inn ALLE egne data fra tastaturet.
 */
void Person::lesData()  {
  cout << "\tNavn:  ";   getline(cin, navn);
  mobil = lesInt("\tMobilnummer", 10000000, 99999999);
}


/**
 *  Legger inn medsendt kjøp (enum) i egen datastruktur/vector.
 *
 *  @param    kjop   -  kjøpet/uthentingen som skal unnalagres
 */
void Person::registrerEttKjop(const char kjop)  {
  switch (kjop)  {
    case 'P':  kjopene.push_back(polse);      break;
    case 'C':  kjopene.push_back(popcorn);    break;
    case 'G':  kjopene.push_back(godtepose);  break;
    case 'S':  kjopene.push_back(sjokolade);  break;
    case 'I':  kjopene.push_back(is);         break;
    case 'B':  kjopene.push_back(brus);       break;
    case 'H':  kjopene.push_back(hamburger);  break;
    case 'K':  kjopene.push_back(kaffe);      break;
    default:   cout << "\n\tUlovlig vare-type som parameter!\n\n";  break;
  }
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på skjermen.
 *
 *  @see   skrivKjop(...)
 */
void Person::skrivData() const  {
  cout << "\n\tNr." << setw(3) << nummer << '\t'
       << navn << ",  tlf: " << mobil << '\n';
  if (!kjopene.empty())  {
     cout << "\n\tHar følgende kjøp/uttak:\n";
     skrivKjop(polse);      skrivKjop(popcorn);   skrivKjop(godtepose);
     skrivKjop(sjokolade);  skrivKjop(is);        skrivKjop(brus);
     skrivKjop(hamburger);  skrivKjop(kaffe);
  } else
     cout << "\n\tHar foreløpig ingen kjøp/uttak.\n\n";
}


/**
 *  Oppgave 2F - Skriver ut på skjermen ANTALL kjøp/uttak av en gitt vare.
 *
 *  @param    vare   -  Varen det skal skrives ut antallet av
 *  @see      antallKjop(...)
 */
void Person::skrivKjop(const Vare vare) const  {
  int antall = antallKjop(vare);             //  Henter antall kjøp av 'vare'.

  if (antall)  {
     cout << "\t\t" << setw(2) << antall << " stk av ";
     switch(vare)  {
       case polse:      cout << "Pølse";       break;
       case popcorn:    cout << "Popcorn";     break;
       case godtepose:  cout << "Godtepose";   break;
       case sjokolade:  cout << "Sjokolade";   break;
       case is:         cout << "Is";          break;
       case brus:       cout << "Brus";        break;
       case hamburger:  cout << "Hamburger";   break;
       case kaffe:      cout << "Kaffe";       break;
     }
     cout << '\n';
  }
}


/**
 *  EXTRA - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Person::skrivTilFil(ofstream & ut) const  {
  int antall = kjopene.size();

  ut << ' ' << nummer << ' ' << mobil << ' ' << antall;
  for (int i = 0;  i < antall;  i++)  {
      ut << ' ';
      switch (kjopene[i])  {
        case polse:       ut << 'P';   break;
        case popcorn:     ut << 'C';   break;
        case godtepose:   ut << 'G';   break;
        case sjokolade:   ut << 'S';   break;
        case is:          ut << 'I';   break;
        case brus:        ut << 'B';   break;
        case hamburger:   ut << 'H';   break;
        case kaffe:       ut << 'K';   break;
      }
  }
  ut << ' ' << navn << '\n';
}

// --------------------------------------------------------------------------

/**
 *  Oppgave 2C - Registrerer ETT kjøp/uthenting av barnet.
 *
 *  @see      registrerEttKjop(...)
 */
void Barn::lesKjop() {
  string lovligeTegn = "PCGSIB";            //  Alle lovlige bokstavvalg.
  char kjop;

  cout << "\n\tAktuelt for et barn å hente:\n\t\t"
       << "Pølse, popCorn, Godtepose, Sjokolade, Is eller Brus\n";
  do  {
    kjop = lesChar("\tDet hentes (P / C / G / S / I / B)");  //  Til bokstaven
  } while (lovligeTegn.find(kjop) >= lovligeTegn.length());  //  er i teksten.

  registrerEttKjop(kjop);                   //  Registrerer/legger inn kjøpet.
}


/**
 *  Oppgave 2G - Beregner hvor mye som skal betales for alle kjøpene/uttakene.
 *
 *  @return   Totalt antall kroner som alle kjøpene/uttakene koster
 *  @see      antallKjop(...)
 */
int Barn::skalBetale() const  {
  return ( (antallKjop(polse)* PRIS)
         + (antallKjop(popcorn)* PRIS)
         + (antallKjop(godtepose)* PRIS)
         + (antallKjop(sjokolade)* PRIS)
         + (antallKjop(is)* PRIS)
         + (antallKjop(brus)* PRIS) );
//  Eller KUN:
//    return (kjopene.size() * PRIS);
}


/**
 *  EXTRA - Skriver objektets arvede data til fil.
 *
 *  @param  ut   -  Filobjektet det skrives ut data til
 *  @see    Person::skrivTilFil(...)
 */
void Barn::skrivTilFil(ofstream & ut) const  {
  ut << 'B';                        //  Skriver at nå kommer et 'Barn'-objekt.
  Person::skrivTilFil(ut);          //  Ingen egne data å skrive til fil,
}                                   //    "mor" skriver derfor bare sine.

// --------------------------------------------------------------------------

/**
 *  Oppgave 2C - Registrerer ETT kjøp/uthenting av den voksne.
 *
 *  @see      registrerEttKjop(...)
 */
void Voksen::lesKjop() {
  string lovligeTegn = "HKSIB";             //  Alle lovlige bokstavvalg.
  char kjop;

  cout << "\n\tAktuelt for en voksen å hente:\n\t\t"
       << "Hamburger, Kaffe, Sjokolade, Is eller Brus\n";
  do  {
    kjop = lesChar("\tDet hentes (H / K / S / I / B)");      //  Til bokstaven
  } while (lovligeTegn.find(kjop) >= lovligeTegn.length());  //  er i teksten.

  registrerEttKjop(kjop);                   //  Registrerer/legger inn kjøpet.
}



/**
 *  Oppgave 2G - Beregner hvor mye som skal betales for alle kjøpene/uttakene.
 *
 *  @return   Totalt antall kroner som alle kjøpene/uttakene koster
 *  @see      antallKjop(...)
 */
int Voksen::skalBetale() const  {
  return ( (antallKjop(hamburger)* PRIS * 2)  // Burger koster det DOBBELTE !!
         + (antallKjop(kaffe)* PRIS)
         + (antallKjop(sjokolade)* PRIS)
         + (antallKjop(is)* PRIS)
         + (antallKjop(brus)* PRIS) );
//  Eller KUN:
//    return ((kjopene.size() * PRIS) + (antallKjop(hamburger) * PRIS));

}


/**
 *  EXTRA - Skriver objektets arvede data til fil.
 *
 *  @param  ut   -  Filobjektet det skrives ut data til
 *  @see    Person::skrivTilFil(...)
 */
void Voksen::skrivTilFil(ofstream & ut) const  {
  ut << 'V';                      //  Skriver at nå kommer et 'Voksen'-objekt.
  Person::skrivTilFil(ut);        //  Ingen egne data å skrive til fil,
}                                 //    "mor" skriver derfor bare sine.


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - En hel familie/gruppe sjekker ut/reiser.
 *
 *  @see    avreisePerson()
 */
void avreiseFamilie()  {
  int totalSum = 0,  sum;

  do  {
    sum = avreisePerson();              //  Henter EN persons sum å betale.
    totalSum += sum;                    //  Oppsummerer gruppens totalsum.
  } while (sum != 0);                   //  Leser inntil person skylder intet.

  cout << "\n\n\tTotalt skal familien/gruppen betale kr: "
       << totalSum << "\n\n";
}


/**
 *  Oppgave 2H - EN enkelt person sjekker ut/reiser, finner hva skal betales.
 *
 *  @return   Summen vedkommende skal betale for sine kjøp/uttak
 *  @see      Person::hentID
 *  @see      Person::skrivData()
 *  @see      Barn::skalBetale()
 *  @see      Voksen::skalBetale()
 */
int avreisePerson()  {
  int nummer, sum = 0;

  if (!gPersonene.empty()) {                 //  Personer finnes:
     nummer = lesInt("\tPersonens nummer", 1, gSisteNummer);
                                             //  Prøver å finne personen:
     auto it = find_if(gPersonene.begin(), gPersonene.end(),
                       [nummer] (const auto & val)
                       { return (val->hentID() == nummer); } );

     if (it != gPersonene.end())  {          //  Funnet:
        (*it)->skrivData();                  //  Skriver vedkommendes data.

        sum = (*it)->skalBetale();           //  Finner ut hva skal betale.
        cout << "\n\tSkal totalt betale kr: " << sum  << "\n\n";

        delete (*it);                        //  Sletter Person-OBJEKTET.

        gPersonene.erase(it);                //  Sletter PEKEREN til personen.

     } else
       cout << "\n\tIngen person med dette nummeret!\n\n";
  } else
    cout << "\n\tIngen personer (barn/voksen) registrert foreløpig!\n\n";

  return sum;
}


/**
 *  Oppgave 2J - Leser ALLE personene (barn/voksne) inn fra fil.
 *
 *  @see   Barn::Barn(...)
 *  @see   Voksen::Voksen(...)
 *  @see   Person::hentID()
 */
void lesFraFil()  {
  ifstream innfil("EX_V22_KJOP.DTA");
  int  antallPersoner;                      //  Antall personer på filen.
  char personType;

  if (innfil) {                             //  Filen finnes:
      cout << "\n\n\tLeser fra filen 'EX_V22_KJOP.DTA'......\n\n";
                                              //  Leser global/lokal variabel:
      innfil >> gSisteNummer >> antallPersoner;   innfil.ignore();
                                              //  Leser ALLE personene:
      for (int i = 1; i <= antallPersoner; i++)  {
          innfil >> personType;  innfil.ignore();
          switch (personType)  {            // Ny legges bakerst.
            case 'B':  gPersonene.push_back(new Barn(innfil));    break;
            case 'V':  gPersonene.push_back(new Voksen(innfil));  break;
            default:   cout << "\n\tUgyldig person-type på fila!\n\n"; break;
          }
      }
                                          //  Sorterer (for sikkerhets skyld):
      gPersonene.sort([](Person* p1, Person* p2)
                              { return (p1->hentID() < p2->hentID()); });

      innfil.close();                       //  Lukker filen manuelt.
  } else                                    //  Filen finnes IKKE:
      cout << "\n\n\tFant ikke filen 'EX_V22_KJOP.DTA'!\n\n";
}


/**
 *  Oppgave 2B - Legger inn en ny person (barn eller voksen).
 *
 *  @see   Barn::Barn(...)
 *  @see   Voksen::Voksen(...)
 *  @see   Person::lesData()
 */
void nyPerson() {
  Person* nyPerson;
  char personType;

  do  {
    personType = lesChar("\tNy person (B(arn), V(oksen))");
  } while (personType != 'B'  &&  personType != 'V');

  cout << "\n\tPersonens unike nummer:  " << ++gSisteNummer << '\n';

  switch (personType)  {                    //  Oppretter aktuell person:
    case 'B':  nyPerson = new Barn(gSisteNummer);     break;
    case 'V':  nyPerson = new Voksen(gSisteNummer);   break;
  }

  nyPerson->lesData();                      //  Leser selv inn alle sine data.

  gPersonene.push_back(nyPerson);           //  Legges ALLTID inn BAKERST.
}                                           //    Så lenge alle har stigende
                                            //    UNIKT nummer, så trengs
                                            //    ingen sortering.
/**
 *  Oppgave 2D - Person kjøper/henter ut EN vare.
 *
 *  @see   Person::hentID()
 *  @see   Barn::lesKjop()
 *  @see   Voksen::lesKjop()
 */
void personKjoperEnVare()  {
  int nummer;

  if (!gPersonene.empty()) {                //  Personer finnes:
     nummer = lesInt("\tPersonens nummer", 1, gSisteNummer);
                                            //  Prøver å finne personen:
     auto it = find_if(gPersonene.begin(), gPersonene.end(),
                       [nummer] (const auto & val)
                       { return (val->hentID() == nummer); } );

     if (it != gPersonene.end())            //  Funnet:
        (*it)->lesKjop();                   //  Kjøp/uthenting foretas.
     else
       cout << "\n\tIngen person med dette nummeret!\n\n";

//  De syv foregående linjene kan også (litt mindre elegant)
//  byttes med følgende åtte linjer:
/*
    bool funn = false;
    for (const auto & val:  gPersonene)
        if (nummer == val->hentID()) {
           funn = true;
           val->lesKjop();
        }
    if (!funn)
       cout << "\n\tIngen person med dette nummeret!\n\n";
*/

  } else
    cout << "\n\tIngen personer (barn/voksen) registrert foreløpig!\n\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   N  - Ny person (barn eller voksen)\n"
       << "   K  - en person Kjøper/henter en vare\n"
       << "   E  - avreise/utsjekk av En person\n"
       << "   F  - avreise/utsjekk av en hel Familie/gruppe\n"
       << "   Q  - Quit / avslutt\n";
}


/**
 *  EXTRA - Skriver ALLE personene (barn/voksne) ut til fil.
 *
 *  @see   Barn::skrivTilFil(...)
 *  @see   Voksen::skrivTilFil(...)
 */
void skrivTilFil()  {
  ofstream utfil("EX_V22_KJOP.DT2");

  cout << "\n\tSkriver alle personer til filen 'EX_V22_KJOP.DT2' .....\n";
                                              //  Skriver global variabel og
                                              //    antallet i listen:
  utfil << gSisteNummer << '\n' << gPersonene.size() << '\n';

  for (const auto & val : gPersonene)       //  Hver person skriver selv:
      val->skrivTilFil(utfil);

  utfil.close();                            //  Lukker filen manuelt.
}
