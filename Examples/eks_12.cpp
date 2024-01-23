/**
 *   Programeksempel nr 12 - Datamedlemmer som er 'protected'.
 * 
 *   Eksemplet er en MEGET LITEN omskriving av EKS_11.CPP.
 *
 *   @file     EKS_12.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


/**
 *  Landemerke (med navn, sted og om p� "UNESCO World Heritage List" eller ei).
 */
class Landemerke {
  protected:                 //  protected - ENESTE ENDRING SIDEN EKS_11.CPP!!
    string  navn,            //              DERMED F�R AVLEDEDE KLASSER 
            sted;            //              ADGANG TIL ENS DATA !!!
    bool    UWHL;            //  Sp�rsm�let er da ofte om en data heretter
                             //    skal v�re 'private' eller 'protected'?
  public:
    void lesData() {
        cout << "Navn:  ";  getline(cin, navn);
        cout << "Sted:  ";  getline(cin, sted);
        UWHL = (lesChar("P� UNESCOs World Heritage List (j/N)") == 'J');
    }

    void skrivData() const  {                  //  Kalles/brukes IKKE av
        cout << '\t' << navn << ", " << sted   //       avledet klasse, da den
             << ((UWHL) ? " p� UWHL" : "") << '\n'; //  har laget sin egen.
    }
};


/**
 *  Bygning (subklasse av "Landemerke", med bygge�r).
 */
class Bygning : public Landemerke {
  private:
      int byggeAar;
  public:
      void lesData()  {
          Landemerke::lesData();
          byggeAar = lesInt("Bygge�r", -4000, 2020);
      }

      void skrivData() const  {         //  ENESTE OMSKREVNE siden EKS_11.CPP:
          cout << '\t' << navn << " (fra " << byggeAar << "), " << sted
              << ((UWHL) ? " p� UWHL" : "") << '\n';
      }
};


/**
 *  Hovedprogrammet:
 */
int main()  {                                  //  IDENTISK TIL EKS_11.CPP:
    Landemerke landemerke1;
    landemerke1.lesData();     cout << '\n';   //  Tilkaller de i baseklassen:
    landemerke1.skrivData();   cout << '\n';

    Bygning bygning1;
    bygning1.lesData();        cout << '\n';   //  Tilkaller de i subklassen:
    bygning1.skrivData();      cout << '\n';
    
    return 0;
}