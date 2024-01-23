/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2022, oppgave 2.
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
 *   @file     EX_V22_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>
#include <vector>
#include <list>
#include <algorithm>               //  Du får sikkert bruk for noen av disse.
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
};


void avreiseFamilie();                        //  Oppgave 2I
int  avreisePerson();                         //  Oppgave 2H
void lesFraFil();                             //  Oppgave 2J
void nyPerson();                              //  Oppgave 2B
void personKjoperEnVare();                    //  Oppgave 2D
void skrivMeny();


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

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Finner og returnerer antall kjøp/uthentinger av en gitt vare.
 *
 *  @param    vare   -  Varen det skal sjekkes antall kjøp/uthentinger av
 *  @return   Antall kjøp/uthentinger av den gitte varen
 */
int Person::antallKjop(const Vare vare) const  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2A - Leser inn ALLE egne data fra tastaturet.
 */
void Person::lesData()  {

    //   LAG INNMATEN
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

    //   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ut på skjermen ANTALL kjøp/uttak av en gitt vare.
 *
 *  @param    vare   -  Varen det skal skrives ut antallet av
 *  @see      antallKjop(...)
 */
void Person::skrivKjop(const Vare vare) const  {

    //   LAG INNMATEN
}


// --------------------------------------------------------------------------

/**
 *  Oppgave 2C - Registrerer ETT kjøp/uthenting av barnet.
 *
 *  @see      registrerEttKjop(...)
 */
void Barn::lesKjop() {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2G - Beregner hvor mye som skal betales for alle kjøpene/uttakene.
 *
 *  @return   Totalt antall kroner som alle kjøpene/uttakene koster
 *  @see      antallKjop(...)
 */
int Barn::skalBetale() const  {

    //   LAG INNMATEN
}


// --------------------------------------------------------------------------

/**
 *  Oppgave 2C - Registrerer ETT kjøp/uthenting av den voksne.
 *
 *  @see      registrerEttKjop(...)
 */
void Voksen::lesKjop() {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2G - Beregner hvor mye som skal betales for alle kjøpene/uttakene.
 *
 *  @return   Totalt antall kroner som alle kjøpene/uttakene koster
 *  @see      antallKjop(...)
 */
int Voksen::skalBetale() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - En hel familie/gruppe sjekker ut/reiser.
 *
 *  @see    avreisePerson()
 */
void avreiseFamilie()  {

    //   LAG INNMATEN
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

    //   LAG INNMATEN
}


/**
 *  Oppgave 2J - Leser ALLE personene (barn/voksne) inn fra fil.
 *
 *  @see   Barn::Barn(...)
 *  @see   Voksen::Voksen(...)
 *  @see   Person::hentID()
 */
void lesFraFil()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Legger inn en ny person (barn eller voksen).
 *
 *  @see   Barn::Barn(...)
 *  @see   Voksen::Voksen(...)
 *  @see   Person::lesData()
 */
void nyPerson() {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Person kjøper/henter ut EN vare.
 *
 *  @see   Person::hentID()
 *  @see   Barn::lesKjop()
 *  @see   Voksen::lesKjop()
 */
void personKjoperEnVare()  {

    //   LAG INNMATEN
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
