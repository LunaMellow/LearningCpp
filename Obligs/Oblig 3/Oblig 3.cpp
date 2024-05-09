
/**     Oblig 3
 *
 *      Programbeskrivelse:
 *          - Les inn personer fra fil
 *          - Skriv personer til fil
 *          - Lag nye personer
 *
 *      @file Oblig 3.cpp
 *      @date 13-Mar-2024
 *
 *      @author Luna Sofie Bergh
 *      @alias LunaMellow
 */

// Imports
#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <map>
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data

// Namespace
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
int main()  {
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
    inn.ignore();
    getline(inn, navn);
}


/**
 *  Leser navnet fra brukeren/tastaturet.
 */
void Person::lesData() {
    cout << "\tNavn på personen: ";
    getline(cin, navn);
}


/**
 *  Skriver ut navnet til/på skjermen.
 */
void Person::skrivData() const {
    cout << "\n\tNavn: " << navn << ", ";
}


/**
 *  Skriver ut navnet til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Person::skrivTilFil(ofstream & ut) const {
    ut << navn << endl;
}


// ---------------------------------------------------------------------------

/**
 *  Leser studiepoeng og studieprogram/klasse fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Student::Student(ifstream & inn) : Person(inn) {
    inn >> stp;
    inn.ignore();
    getline(inn, studieprogram);
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Student::endreData() {
    cout << "\tStudieprogram: ";
    getline(cin, studieprogram);
    stp = lesFloat("Studiepoeng", 0, 300);
}


/**
 *  Leser baseklassens data, studieprogram/klasse og studiepoeng fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Student::lesData() {
    Person::lesData();
    cout << "\tStudieprogram: ";
    getline(cin, studieprogram);
    stp = lesFloat("\tStudiepoeng", 0, 300);
}


/**
 *  Skriver baseklassens data, studieproram/klasse og studiepoeng til skjerm.
 *
 *  @see  Person::skrivData()
 */
void Student::skrivData() const {
    Person::skrivData();
    cout << "\tStudiepoeng: "     << stp              << endl
         << "\tStudieprogram:: "  << studieprogram    << endl;
}


/**
 *  Skriver 'S', baseklassens data, studiepoeng og studieprogram til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Student::skrivTilFil(ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << stp << " " << studieprogram << endl;
}


// ---------------------------------------------------------------------------

/**
 *  Leser årslønn og rom/kontor fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Ansatt::Ansatt(ifstream & inn) : Person(inn) {
    inn >> lonn;
    inn.ignore();
    getline(inn, rom);
}


/**
 *  Tilbyr brukren å endre på alle egne data.
 *
 *  @see  skrivData()
 */
void Ansatt::endreData() {
    skrivData();
    lonn = lesInt("\tLønn", 0, 100000000);
    cout << "\tRom: ";
    getline(cin, rom);
}


/**
 *  Leser baseklassens data, rom/kontor og årslønn fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Ansatt::lesData() {
    Person::lesData();
    lonn = lesInt("\tLønn", 0, 100000000);
    cout << "\tRom: ";
    getline(cin, rom);
}


/**
 *  Skriver baseklassens data, rom/kontor og årslønn til/på skjermen.
 *
 *  @see  Person::skrivData()
 */
void Ansatt::skrivData() const {
    Person::skrivData();
    cout << "\tLønn: "    << lonn     << endl
         << "\tRom: "     << rom      << endl;
}


/**
 *  Skriver 'A', baseklassens data, årslønn og rom/kontor.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Ansatt::skrivTilFil(ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << lonn << rom << endl;
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
    int nr = lesInt("\tPerson ID", 1, 100000);
    for (auto & it : gPersoner) {
        if (it.first == nr) {
            it.second->endreData();
            break;
        }
        cout << "Personen eksisterer ikke. Ugyldig ID." << endl;
        return;
    }
}


/**
 *  Leser ALLE personer inn fra fil, og legger de inn i 'gPersoner'.
 */
void lesFraFil() {
    ifstream innfil("oblig3.dta");

    int nr;
    char type;

    if (!innfil) {
        cout << "Fant ikke oblig3.dta" << endl;
        return;

    }

    while (innfil >> nr >> type) {
        switch (type) {
            case 'A':
                gPersoner[nr] = new Ansatt(innfil);
                break;
            case 'S':
                gPersoner[nr] = new Student(innfil);
                break;
            default:
                cout << "Noe gikk galt ved lesing av filmedlem" << endl;
                return;
        }
    }

    innfil.close();
}


/**
 *  Legger inn (om mulig) en ny person.
 *
 *  @see   virtual Person::lesData()
 */
void nyPerson() {
    Person* nyPers;

    int nr;
    char type = lesChar("\tType ( (A)nsatt / (S)tudent )");

    switch (type) {
        case 'A':
            nr = lesInt("\tNr", 1, 1000);
            for (auto & it : gPersoner) {
                if (it.first == nr) {
                    cout << "Ansatt nr. " << nr << " eksisterer allerede." << endl;
                    return;
                }
            }
            nyPers = new Ansatt;
            nyPers->lesData();
            gPersoner[nr] = nyPers;

            break;
        case 'S':
            nr = lesInt("\tNr", 1001, 100000);
            for (auto & it : gPersoner) {
                if (it.first == nr) {
                    cout << "Student nr. " << nr << " eksisterer allerede." << endl;
                }
            }

            nyPers = new Student;
            nyPers->lesData();
            gPersoner[nr] = nyPers;

            break;
        default:
            cout << "Noe gikk galt. Godkjente valg ( (A)nsatt / (S)tudent )" << endl;
            return;
    }
}


/**
 *  Skriver alle dataene om alle personene ut på skjermen.
 *
 *  @see   virtual Person::skrivData()
 */
void skrivAllePersoner() {
    for (auto & it : gPersoner) {
        it.second->skrivData();
    }
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
    ofstream utfil("oblig3.dta");

    for (auto & it : gPersoner) {
        utfil << it.first << " ";
        if (it.first < 1001) {
            utfil << "A ";
        }
        else {
            utfil << "S ";
        }
        it.second->skrivTilFil(utfil);
    }

    utfil.close();
}