/**
 *   Programeksempel nr 11 - Overskrivende/likenavnede funksjoner.
 * 
 *   Eksemplet er en MEGET LITEN omskriving av EKS_10.CPP.
 *
 *   @file     EKS_11.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Landemerke (med navn, sted og om på "UNESCO World Heritage List" eller ei).
 */
class Landemerke {           //  UENDERT FRA/IDENTISK TIL EKS_10.CPP.
  private:
    string  navn,
            sted;
    bool    UWHL;            //  = UNESCO World Heritage List

  public:
    void lesData() {
        cout << "Navn:  ";  getline(cin, navn);
        cout << "Sted:  ";  getline(cin, sted);
        UWHL = (lesChar("På UNESCOs World Heritage List (j/N)") == 'J');
    }

    void skrivData() const  {
        cout << '\t' << navn << ", " << sted 
             << ((UWHL) ? " på UWHL" : "") << '\n';
    }
};


/**
 *  Bygning (subklasse av "Landemerke", med byggeår).
 */
class Bygning : public Landemerke {
  private:
      int byggeAar;
  public:
      void lesData()  {                     //  Omnavnet siden EKS_10.CPP.
          Landemerke::lesData();            //  NYTT:  Kaller baseklassen sin.
          byggeAar = lesInt("Byggeår", -4000, 2020);
      }

      void skrivData() const  {             //  Omnavnet siden EKS_10.CPP.
          Landemerke::skrivData();          //  NYTT:  Kaller baseklassen sin.
          cout << "\t\tByggeår: " << byggeAar << '\n';
      }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Landemerke landemerke1;
    landemerke1.lesData();     cout << '\n';   //  Tilkaller de i baseklassen:
    landemerke1.skrivData();   cout << '\n';

    Bygning bygning1;
    bygning1.lesData();        cout << '\n';   //  Tilkaller de i subklassen:
    bygning1.skrivData();      cout << '\n';
    
    return 0;
}