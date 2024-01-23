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
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
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
 *  Kvinne (med antall f�dsler) - subklasse av Person. 
 */
class Kvinne : public Person  {
  private:
      int antFodsler;
  public:
      void lesData() {
          cout << "Kvinne - ";
          Person::lesData();
          antFodsler = lesInt("Antall f�dsler", 0, 20);
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

    kvinnePeker = new Kvinne;    //  'kvinnePeker' peker p� 'Kvinne'.
    kvinnePeker->lesData();      //  �nsket 'lesData' kj�res.

    mannPeker = new Mann;        //  'mannPeker' peker p� 'Mann'.
    mannPeker->lesData();        //  �nsket 'lesData' kj�res.

    personPeker = new Person;    //  'personPeker' peker til 'Person'.
    personPeker->lesData();      //  �nsket 'lesData' kj�res.

    delete kvinnePeker;
    delete mannPeker;
    delete personPeker;


//  NB  NB:  EN BASEPEKER KAN OGS� PEKE TIL ALLE AVLEDEDE KLASSER/OBJEKTER!!!
//           (Men en avledet peker kan i utgangspunktet ikke peke til 
//           objekter av baseklasser (klasser oppover i arvehierarkiet).) 

    cout << "\n\n'personPeker' peker p� 'new Kvinne'\n";
    personPeker = new Kvinne;    //  'personPeker' peker til 'Kvinne' !!!
    personPeker->lesData();      //  �nsket 'lesData' kj�res IKKE !!!
    delete personPeker;

    cout << "\n\nOg tilsvarende: 'personPeker' peker p� 'new Mann'\n";
    personPeker = new Mann;      //  'personPeker' peker til 'Mann' !
    personPeker->lesData();      //  �nsket 'lesData' kj�res IKKE !
    delete personPeker;


    //  Hvordan f� til dette riktig???    Se EKS_17.CPP 

    return 0;
}