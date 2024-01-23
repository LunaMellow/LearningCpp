/**
 *   Programeksempel nr 17 - Virtueller, pekere og casting.
 *
 *   @file     EKS_17.CPP
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
  public:                          //  ORDET 'VIRTUAL' ER DET ENESTE ENDREDE/
                                   //    TILLEGGET INNI ALLE DE 3x KLASSENE!!!
      virtual void lesData() { cout << "Navn:  ";  getline(cin, navn); }
};


/**
 *  Kvinne (med antall f�dsler) - subklasse av Person.
 */
class Kvinne : public Person  {
  private:
      int antFodsler;
  public:
      virtual void lesData() {     //  ORDET 'VIRTUAL' ER DET ENESTE ENDREDE/
          cout << "Kvinne - ";     //    TILLEGGET INNI ALLE DE 3x KLASSENE!!!
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
      virtual void lesData() {     //  ORDET 'VIRTUAL' ER DET ENESTE ENDREDE/
          cout << "Mann - ";       //    TILLEGGET INNI ALLE DE 3x KLASSENE!!!
          Person::lesData();
          harSkjegg = (lesChar("Har skjegg (j/N)") == 'J');
      }
};


/**
 *  Hovedprogrammet:
 */
int main() {
    Person*  personPeker;
    Mann*    mannPeker;

    cout << "\n\n'personPeker' peker p� 'new Kvinne'\n";
    personPeker = new Kvinne;    //  'personPeker' peker til 'Kvinne' !!!
    personPeker->lesData();      //  �nsket 'lesData' KJ�RES !!!
    delete personPeker;

    cout << "\n\nOg tilsvarende: 'personPeker' peker p� 'new Mann'\n";
    personPeker = new Mann;      //  'personPeker' peker til 'Mann' !
    personPeker->lesData();      //  �nsket 'lesData' KJ�RES !

    cout << "\n\n";


//  CASTING av 'personPeker' til 'Mann', 
//    slik at 'mannPeker' peker til objekt av rett klasse:

    mannPeker = dynamic_cast <Mann*> (personPeker);
    mannPeker->lesData();
    delete personPeker;

    mannPeker = new Mann;
    personPeker = mannPeker;     //  Basepeker kan peke direkte p� ALT (uten 
    personPeker->lesData();      //    casting) av avledede klasser/objekter.

    return 0;
}


// ***************************************************************************
// ***************************************************************************
/*
    Noen fakta om  ARVEHIERARKI, VIRTUELLER og PEKERE:

1)  Ved virtueller fors�kes det � utf�re den aktuelle funksjon i det
    objektet som det refereres til. Om en slik ikke finnes, s� utf�res
    den n�rmeste likenavnede funksjonen i en av klassene i rett
    oppadstigende linje i det ovenforliggende hierarkiet.

2)  En peker som er definert til � peke p� en baseklasse, kan ogs�
    peke til objekter av alle avledede klasser til denne baseklassen.
    En slik peker kalles en "VID PEKER". Vha. denne pekeren kan man
    KUN aksessere det som er definert i baseklassen, det som den evnt.
    selv har arvet fra andre, eller det som den kjenner som virtuelt
    nedover i hierarkiet.

3)  En pekervariabel som er definert til � v�re av typen "ett-sted-nede-i-
    hierarkiet" kan i utgangspunktet (om den ikke castes som i eksemplet
    ovenfor) IKKE peke til noen av sine baseklasser (dvs. til klasser
    lengre opp i hierarkiet). En slik peker kalles "TRANG PEKER".
    Vha. en slik peker kan man ofte aksessere mye data/mange funksjoner,
    dvs. ALT det synlige som den har arvet nedover i hierarkiet, og som
    den evnt. m�tte kjenne til som virtuelt videre nedover i hierarkiet.

4)  Om baseklassen har definert en funksjon som virtuell, s� blir den
    virtuell nedover i hierarkiet, selvom klassene nedover ikke har med
    ordet "virtual".

5)  DESTRUCTORER I ARVEHIERARKI M�/B�R OGS� V�RE VIRTUELLE !!!

6)  Noen uttrykk brukt hittil og i en del litteratur:
    "IS A"  - "IS"
        Om et objekt er av en bestemt klasse.
    "KIND OF" - "IN":
        Om et objekt er av en bestemt klasse ELLER et objekt som er
        avledet fra vedkommende klasse.
    "HAS A":
        Brukes ved aggregation/containership. Dvs. at et objekt 
        inneholder referanser til andre objekt(er) inni seg.
    "QUA" - CASTING - BETRAKTET SOM:
        En "vid peker" blir 'omdefinert' slik at den kan f� tak i
        data/funksjoner som f�rst er definert i klasser lengre ned
        i arvehierakiet.
*/
// ***************************************************************************
// ***************************************************************************