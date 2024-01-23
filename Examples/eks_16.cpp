/**
 *   Programeksempel nr 16 - Introduksjon til virtuell-behovet.
 *
 *   Fortsetter i EKS_17.CPP .....
 *
 *   @file     EKS_16.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Person (med navn).
 */
class Person  {
  private:
      string navn;
  public:
      void lesData() { cout << "Navn:  ";  getline(cin, navn); }
};


/**
 *  Kvinne (med antall fødsler) - subklasse av Person. 
 */
class Kvinne : public Person  {
  private:
      int antFodsler;
  public:
      void lesData() {
          cout << "Kvinne - ";
          Person::lesData();
          antFodsler = lesInt("Antall fødsler", 0, 20);
      }
};


/**
 *  Mann (med om har skjegg eller ei) - subklasse av Person.
 */
class Mann : public Person  {
  private:
      bool harSkjegg;
  public:
      void lesData() {
          cout << "Mann - ";
          Person::lesData();
          harSkjegg = (lesChar("Har skjegg (j/N)") == 'J');
      }
};


/**
 *  Hovedprogrammet:
 */
int main() {
    Person*  personPeker;
    Kvinne*  kvinnePeker;
    Mann*    mannPeker;

    kvinnePeker = new Kvinne;    //  'kvinnePeker' peker på 'Kvinne'.
    kvinnePeker->lesData();      //  Ønsket 'lesData' kjøres.

    mannPeker = new Mann;        //  'mannPeker' peker på 'Mann'.
    mannPeker->lesData();        //  Ønsket 'lesData' kjøres.

    personPeker = new Person;    //  'personPeker' peker til 'Person'.
    personPeker->lesData();      //  Ønsket 'lesData' kjøres.

    delete kvinnePeker;
    delete mannPeker;
    delete personPeker;


//  NB  NB:  EN BASEPEKER KAN OGSÅ PEKE TIL ALLE AVLEDEDE KLASSER/OBJEKTER!!!
//           (Men en avledet peker kan i utgangspunktet ikke peke til 
//           objekter av baseklasser (klasser oppover i arvehierarkiet).) 

    cout << "\n\n'personPeker' peker på 'new Kvinne'\n";
    personPeker = new Kvinne;    //  'personPeker' peker til 'Kvinne' !!!
    personPeker->lesData();      //  Ønsket 'lesData' kjøres IKKE !!!
    delete personPeker;

    cout << "\n\nOg tilsvarende: 'personPeker' peker på 'new Mann'\n";
    personPeker = new Mann;      //  'personPeker' peker til 'Mann' !
    personPeker->lesData();      //  Ønsket 'lesData' kjøres IKKE !
    delete personPeker;


    //  Hvordan få til dette riktig???    Se EKS_17.CPP 

    return 0;
}