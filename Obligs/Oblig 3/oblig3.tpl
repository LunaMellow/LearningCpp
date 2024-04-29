/** 
 *   Skjelett for obligatorisk oppgave nr 3 i PROG1003 - OOP.
 *
 *   Programmet inneholder en oversikt over studenter og ansatt på en skole.
 *   Disse er identifisert via sitt UNIKE student-/ansattnummer,
 *   og alle ligger lagret i EN <map>. Brukeren/programmet kan:
 *       - se ALLE personene som er lagret i datastrukturen (map'en)
 *       - legge inn en ny student/ansatt
 *       - endre data om en gitt student/ansatt
 *       - HELE datastrukturen leses fra/skrives til fil
 *
 *   @file    OBLIG3.TPL
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <map>
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Person (med navn).
 */
class Person {
  private:
      string navn;
  public:
      Person()  {  navn = "";  }
      Person(ifstream & inn);
      virtual void endreData() = 0;
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Student (med studieprogram/klasse og antall studiepoeng).
 */
class Student : public Person {
  private:
      string studieprogram;
      float  stp;
  public:
      Student()  {  studieprogram = "";  stp = 0.0F;  }
      Student(ifstream & inn);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Ansatt (med rom-/kontornummer og årslønn).
 */
class Ansatt : public Person {
  private:
      string rom;
      int    lonn;
  public:
      Ansatt()  {  rom = "";  lonn = 0;  }
      Ansatt(ifstream & inn);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


void endreEnPerson();
void lesFraFil();
void nyPerson();
void skrivAllePersoner();
void skrivMeny();
void skrivTilFil();


map <int, Person*> gPersoner;      ///<  Datastrukturen med alle personene.


/**
 *  Hovedprogrammet:
 */
int main(void)  {
    char kommando;

    lesFraFil();

    skrivMeny();
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'N':  nyPerson();               break;
          case 'A':  skrivAllePersoner();      break;
          case 'E':  endreEnPerson();          break;
          default:   skrivMeny();              break;
        }
        kommando = lesChar("Kommando");
    }

    skrivTilFil();

   return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Leser navnet fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Person::Person(ifstream & inn) {
    //  LAG INNMATEN
}


/**
 *  Leser navnet fra brukeren/tastaturet.
 */
void Person::lesData() {
    //  LAG INNMATEN
}


/**
 *  Skriver ut navnet til/på skjermen. 
 */
void Person::skrivData() const {
    //  LAG INNMATEN
}


/**
 *  Skriver ut navnet til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Person::skrivTilFil(ofstream & ut) const {
    //  LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *  Leser studiepoeng og studieprogram/klasse fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Student::Student(ifstream & inn) : Person(inn) {
    //  LAG INNMATEN
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Student::endreData() {
    //  LAG INNMATEN
}


/**
 *  Leser baseklassens data, studieproram/klasse og studiepoeng fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Student::lesData() {
    //  LAG INNMATEN
}


/**
 *  Skriver baseklassens data, studieproram/klasse og studiepoeng til skjerm.
 *
 *  @see  Person::skrivData()
 */
void Student::skrivData() const {
    //  LAG INNMATEN
}


/**
 *  Skriver 'S', baseklassens data, studiepoeng og studieprogram til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Student::skrivTilFil(ofstream & ut) const {
    //  LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *  Leser årslønn og rom/kontor fra fil. 
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Ansatt::Ansatt(ifstream & inn) : Person(inn) {
    //  LAG INNMATEN
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Ansatt::endreData() {
    //  LAG INNMATEN
}


/**
 *  Leser baseklassens data, rom/kontor og årslønn fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Ansatt::lesData() {
    //  LAG INNMATEN
}


/**
 *  Skriver baseklassens data, rom/kontor og årslønn til/på skjermen.
 *
 *  @see  Person::skrivData()
 */
void Ansatt::skrivData() const {
    //  LAG INNMATEN
}


/**
 *  Skriver 'A', baseklassens data, årslønn og rom/kontor.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Ansatt::skrivTilFil(ofstream & ut) const {
    //  LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Lar brukeren (om mulig) endre dataene for et avledet objekt (subklasse).
 *
 *  @see   virtual Person::endreData()
 */
void endreEnPerson() {
    //  LAG INNMATEN
}


/**
 *  Leser ALLE personer inn fra fil, og legger de inn i 'gPersoner'.
 */
void lesFraFil() {
    //  LAG INNMATEN
}


/**
 *  Legger inn (om mulig) en ny person.
 *
 *  @see   virtual Person::lesData()
 */
void nyPerson() {
    //  LAG INNMATEN
}


/**
 *  Skriver alle dataene om alle personene ut på skjermen.
 *
 *  @see   virtual Person::skrivData()
 */
void skrivAllePersoner() {
    //  LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny person (student eller ansatt)\n"
         << "\tA - skriv Alle personer\n"
         << "\tE - Endre EN gitt person\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Skriver hele datastrukturen til fil.
 *
 *  @see   virtual Person::skrivTilFil(...)
 */
void skrivTilFil() {
    //  LAG INNMATEN
}