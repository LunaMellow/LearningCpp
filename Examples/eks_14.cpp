/**
 *   Programeksempel nr 14 - Større programeksempel.
 *
 *   Eksemplet viser/vektlegger klasser, arv og datastruktur.
 *
 *   Hovedfunksjonalitet:
 *     - Inneholder objekter av typene 'Ansatt' og 'Student'
 *       som begge er subklasser/avledede klasser fra 'Person'.
 *     - De to subklassene inneholder constructorer (den ene også destructor),
 *       og funksjoner for å lese, skrive og endre sine data.
 *     - Brukeren kan legge inn nye objekter av begge typer, få skrevet ALLE
 *       ansatte eller studenter, samt endre på en ønsket ansatt/student.
 *     - For en student er det i tillegg mulig å legge inn en karakter
 *       for et nytt emne.
 *     - Alle de ansatte og studenter lagres i hver sine vectorer,
 *       og deres navn er UNIKE (ingen duplikater) i vedkommende vector.
 *     - NB:  Alt ifm. "endringer" er bevisst ennå ikke ferdig kodet/laget.
 *            Disse er markert med labelene "LATER".
 *            (En fin øvelse å kode/utvide med dette selv.)
 *
 *   @file     EKS_14.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Grad (studiegrad/-nivå - bachelor, master, PhD).
 */
enum Grad { IkkeAngitt, Bachelor, Master, PhD  };


/**
 *  Data om ett emne (emnekode og karakter).
 *
 *  NB:  Brukes KUN inni klassen 'Student',
 *       så kunne like gjerne ha vært deklarert der!
 */
struct EmneData {
    string kode;
    char   karakter;
};


/**
 *  Person (med navn - ABSTRAKT baseklasse for 'Ansatt' og 'Student').
 */
class Person  {
  protected:               //  'protected' slik at subklasser fritt kan
      string navn;         //     oppdatere og bruke (skrive ut) 'navn'.

  public:
      Person()          {  cout << "'Person' MÅ opprettes med et navn!\n";  }
      Person(const string nvn)  {  navn = nvn;   }
      bool harNavnet(const string nvn) const  {  return (navn == nvn);  }
      void lesData()          {  cout << "Navn:  ";   getline(cin, navn);  }
      void skrivData() const  {  cout << "Navn:  " << navn << '\n';  }
};                         //  NB: 2x aller siste funksjoner er IKKE I BRUK!!


/**
 *  Ansatt (med tittel, romnummer, år ansatt, lønnstrinn og om er leder).
 */
class Ansatt : public Person  {
  private:
      string tittel,
             romNr;
      int    ansattAar,
             lonnstrinn;
      bool   lederstilling;

  public:
      Ansatt()  {  cout << "'Ansatt' MÅ opprettes med et navn!\n";  }
      Ansatt(const string nvn) : Person(nvn)  {  tittel = romNr = "";
                        ansattAar = lonnstrinn = 0;  lederstilling = false;  }
      void endreData();
      void lesData();
      void skrivData() const;
};



/**
 *  Stdent (med grad/nivå, studiets startår, karakterene i de ulike emnene).
 */
class Student : public Person {
  private:
    Grad  grad;
    int   startAar;
    vector <EmneData*> emner;

  public:
    Student()   {  cout << "'Student' MÅ opprettes med et navn!\n";  }
    Student(const string nvn) : Person(nvn)
                {  grad = IkkeAngitt;   startAar = 0;  }
    ~Student()  {  for (int i = 0;  i < emner.size();  i++) // Frigir allokert
                       delete emner[i];                     // memory og
                   emner.clear();  }                        // vector-innhold:
    void endreData();
    void lesData();
    void lesNyKarakter();
    void skrivData() const;
};


void endreAnsatt();
void endreStudent();
int  finnAnsatt(const string nvn);
int  finnStudent(const string nvn);
void frigiAllokertMemory();
void nyAnsatt();
void nyKarakterForStudent();
void nyStudent();
void skrivAlleAnsatte();
void skrivAlleStudenter();
void skrivMeny();


vector <Ansatt*>  gAnsatte;          ///<  Datastrukturen med ALLE ansatte.
vector <Student*> gStudentene;       ///<  Datastrukturen med ALLE studentene.


/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
      switch (kommando) {
        case 'A': nyStudent();               break;
        case 'B': skrivAlleStudenter();      break;
        case 'C': endreStudent();            break;
        case 'D': nyKarakterForStudent();    break;
        case 'X': nyAnsatt();                break;
        case 'Y': skrivAlleAnsatte();        break;
        case 'Z': endreAnsatt();             break;
        default:  skrivMeny();               break;
      }
      kommando = lesChar("\nKommando");
    }

    frigiAllokertMemory();

    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Endrer en ansatts data - ut fra brukerens ønsker.
 */
void Ansatt::endreData() {

//  LATER:   Tilbyr og endrer på alle(?) den ansattes data.
}


/**
 *  Leser inn ALLE klassens datamedlemmer.
 */
void Ansatt::lesData()  {
//                        evt. senere:     Person::lesData();
    cout << "\tTittel:  ";   getline(cin, tittel);
    lederstilling = (lesChar("\tLederstilling (j/N)") == 'J');
    ansattAar  = lesInt("\tAnsattår", 1980, 2020);
    lonnstrinn = lesInt("\tLønnstrinn", 19, 101);
    cout << "\tRomnr:   ";   getline(cin, romNr);
}


/**
 *  Skriver ALLE datamedlemmer, inkludert arvet 'navn'.
 */
void Ansatt::skrivData() const  {
//                        evt. senere:     Person::skrivData();
    cout << navn << ", " << tittel << ((lederstilling) ? ", Leder" : "")
         << "\n\t\tRom: " << romNr << ", ansatt i " << ansattAar
         << " og har nå ltr." << lonnstrinn << '\n';
}

// ---------------------------------------------------------------------------

/**
 *  Endrer en students data - ut fra brukerens ønsker.
 */
void Student::endreData() {

//  LATER:   Tilbyr og endrer på alle(?) studentens data.
}


/**
 *  Leser inn ALLE klassens datamedlemmer.
 */
void Student::lesData() {
//                        evt. senere:     Person::lesData();
    int grad = lesInt("\tNåværende grad (1=Bachelor, 2=Master, 3=PhD)", 1, 3);
    if      (grad == 1)  this->grad = Bachelor; //  Gjør om int til enum:
    else if (grad == 2)  this->grad = Master;   //  Bruker 'this' da likt navn
    else                 this->grad = PhD;      //  på variabel og datamedlem.
    startAar = lesInt("\tStudiets startår", 2015, 2020);
}


/**
 *  Leser inn og lagrer emnekode og karakter for et (nytt) emne.
 */
void Student::lesNyKarakter() {
    char karakter;
    EmneData*  nyED = new EmneData; //  Lager en ny emne/karakter-struct.
    cout << "\tEmnekode: ";   getline(cin, nyED->kode);    //  Leser emnekode.
    do {                            //  Sikrer at karakter er A-F:
        karakter = lesChar("\tKarakter (A-F)");
    } while (karakter < 'A' || karakter > 'F');
    nyED->karakter = karakter;
    emner.push_back(nyED);          //  Lagrer ny kode og karakter i vectoren.
}


/**
 *  Skriver ALLE datamedlemmer, inkludert arvet 'navn'.
 */
void Student::skrivData() const  {
//                        evt. senere:     Person::skrivData();
    cout << navn << " startet i " << startAar << " på ";
    switch (grad) {                                //  Utskrift av enum-verdi:
      case Bachelor: cout << "Bachelor";  break;
      case Master:   cout << "Master";    break;
      case PhD:      cout << "PhD";       break;
    }
    cout << '\n';
    if (!emner.empty()) {                          //  Karakter(er) finnes:
        cout << "\t\tHar karakterene:\n";
        for (int i = 0; i < emner.size(); i++)     //  Skriver ALLE emnekoder
            cout << "\t\t\t" << emner[i]->kode     //    og karakterer:
                 << ": " << emner[i]->karakter << '\n';  //  Skriver en og en:
        cout << "\t\t\t\t\t\t\t\tSkriv ENTER/CR .....";   getchar();
    }
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Tilbyr brukeren å endre data om EN NAVNGITT ansatt.
 *
 *  @see  finnAnsatt(...)
 *  @see  Ansatt::endreData()
 */
void endreAnsatt() {

//  LATER:   Spør om ansattnavn, bruker finnAnsatt(...) for å finne denne.
//           Funn: bruker vedkommendes endreData(), ellers kommer en melding.
}


/**
 *  Tilbyr brukeren å endre data om EN NAVNGITT student.
 *
 *  @see  finnStudent(...)
 *  @see  Student::endreData()
 */
void endreStudent() {

//  LATER:   Spør om studentnavn, bruker finnStudent(...) for å finne denne.
//           Funn: bruker vedkommendes endreData(), ellers kommer en melding.
}


/**
 *  Finner (om mulig) indeksen for en navngitt Ansatt.
 *
 *  @param    nvn  -  Den søkte ansattes navn
 *  @return   Ansattes indeks i vectoren, eller -1 om ikke funnet.
 *  @see      Person::harNavnet(...)
 */
int  finnAnsatt(const string nvn)  {
    for (int i = 0;  i < gAnsatte.size();  i++)
        if (gAnsatte[i]->harNavnet(nvn))  return i;
    return -1;
}


/**
 *  Finner (om mulig) indeksen for en navngitt Student.
 *
 *  @param    nvn  -  Den søkte studentens navn
 *  @return   Studentens indeks i vectoren, eller -1 om ikke funnet.
 *  @see      Person::harNavnet(...)
 */
int  finnStudent(const string nvn)  {
    for (int i = 0;  i < gStudentene.size();  i++)
        if (gStudentene[i]->harNavnet(nvn))  return i;
    return -1;
}


/**
 *  Frigir ALL allokert memory under run-time.
 */
void frigiAllokertMemory() {
  for (int i = 0; i < gAnsatte.size(); i++)   //  Går gjennom ALLE ansatte:
        delete  gAnsatte[i];                  //  Alle OBJEKTENE slettes.
  gAnsatte.clear();                           //  Alle PEKERNE slettes.
                             //  Alternativ skrivemåte (vha. range-based for):
  for (auto & val : gStudentene)              // Går gjennom ALLE studentene:
        delete  val;                          // Alle OBJEKTENE slettes.
  gStudentene.clear();                        // Alle PEKERNE slettes.
}


/**
 *  Oppretter, leser data for og legger inn (om mulig)
 *  en ny Ansatt i datastrukturen.
 *
 *  @see   finnAnsatt(...)
 *  @see   Ansatt::lesData()
 */
void nyAnsatt() {                         //  "Identisk" til 'nyStudent()'.
    string navn;
    Ansatt* nyAnsatt;

    cout << "\tNy ansatts navn:  ";   getline(cin, navn);
    if (finnAnsatt(navn) < 0) {           //  Den ansatte finnes IKKE fra før:
        nyAnsatt = new Ansatt(navn);      //  Lager en ny ansatt.
        nyAnsatt->lesData();              //  Leser selv sine egne data.
        gAnsatte.push_back(nyAnsatt);     //  Legges inn i Ansatt-vectoren.
        cout << "\n\tNy ansatt er registrert og lagt inn.\n";
    } else
        cout << "\n\tAnsatt med dette navn finnes allerede!\n";
}


/**
 *  Legger inn et nytt emne og karakter hos en NAVNGITT student.
 *
 *  @see   finnStudent(...)
 *  @see   Student::lesNyKarakter()
 */
void nyKarakterForStudent() {
    string navn;
    int nr;
    cout << "\tNy karakter for studenten:  ";   getline(cin, navn);
    if ((nr = finnStudent(navn)) >= 0)     //  Studenten finnes:
        gStudentene[nr]->lesNyKarakter();  //  Registrerer emne/karakter selv.
    else
        cout << "\n\tIngen student med dette navnet!\n";
}


/**
 *  Oppretter, leser data for og legger inn (om mulig)
 *  en ny Student i datastrukturen.
 *
 *  @see   finnStudent(...)
 *  @see   Student::lesData()
 */
void nyStudent() {                        //  "Identisk" til 'nyAnsatt()'.
    string navn;
    Student* nyStudent;

    cout << "\tNy students navn:  ";   getline(cin, navn);
    if (finnStudent(navn) < 0) {          //  Studenten finnes IKKE fra før:
        nyStudent = new Student(navn);    //  Lager en ny student.
        nyStudent->lesData();             //  Leser selv sine egne data.
        gStudentene.push_back(nyStudent); //  Legges inn i Student-vectoren.
        cout << "\n\tNy student er registrert og lagt inn.\n";
    } else
        cout << "\n\tStudent med dette navn finnes allerede!\n";
}


/**
 *  Skriver ALT om ALLE ansatte.
 *
 *  @see   Ansatt::skrivData()
 */
void skrivAlleAnsatte() {           //  "Identisk" til 'skrivAlleStudenter()'.
    cout << "\n\tData om ALLE ansatte:\n\n";
    for (int i = 0; i < gAnsatte.size(); i++) {    //  Går gjennom de ansatte:
        cout << '\t' << setw(3) << i + 1 << ": ";  //  Skriver nr/indeks
        gAnsatte[i]->skrivData();                  //  Skriver selv sine data.
    }
}


/**
 *  Skriver ALT om ALLE studenter.
 *
 *  @see  Student::skrivData()
 */
void skrivAlleStudenter() {           //  "Identisk" til 'skrivAlleAnsatte()'.
    cout << "\n\tData om ALLE studenter:\n\n";
    for (int i = 0; i < gStudentene.size(); i++) { //  Går gjennom studentene:
        cout << '\t' << setw(3) << i + 1 << ": ";  //  Skriver nr/indeks.
        gStudentene[i]->skrivData();               //  Skriver selv sine data.
    }
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tA - NY student\n"
         << "\tB - SKRIV ALLE studentene\n"
         << "\tC - ENDRE student\n"
         << "\tD - NY KARAKTER for student\n"
         << "\tX - NY ansatt\n"
         << "\tY - SKRIV ALLE ansatte\n"
         << "\tZ - ENDRE ansatt\n"
         << "\tQ - Quit / avslutt\n";
}
