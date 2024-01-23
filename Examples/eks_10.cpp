/**
 *   Programeksempel nr 10 - Grunnleggende om arv (inheritance).
 *
 *   Arv = å lage avledet klasse (subklasse) fra baseklasse (superklasse).
 * 
 *   @file     EKS_10.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Landemerke (med navn, sted og om på "UNESCO World Heritage List" eller ei).
 */
class Landemerke {
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

    void skrivData() const {
        cout << '\t' << navn << ", " << sted 
             << ((UWHL) ? " på UWHL" : "") << '\n';
    }
};


/**
 *  Bygning (subklasse av "Landemerke", med byggeår).
 */
class Bygning : public Landemerke {  //  NB NB: 'public' BETYR AT DET SOM ER
  private:                           //         ARVET SOM PUBLIC SKAL FORBLI
      int byggeAar;                  //         PUBLIC. Dette er (for oss) den
                                     //         mest vanlige måten å arve på!
  public:
      void lesAar()         {  byggeAar = lesInt("Byggeår", -4000, 2020);    }
      void skrivAar() const {  cout << "\t\tByggeår: " << byggeAar << '\n';  }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Landemerke landemerke1;                  //  Som hittil - objekt:
    landemerke1.lesData();     cout << '\n';
    landemerke1.skrivData();   cout << '\n';

    Landemerke* landemerke2;                 //  Det samme - peker til objekt:
    landemerke2 = new Landemerke;            //  Lager nytt baseklasseobjekt.
    landemerke2->lesData();    cout << '\n';
    landemerke2->skrivData();  cout << '\n';

    Bygning bygning1;                        //  Objekt som har arvet:
    bygning1.lesData();                      //  DEN HAR DA TOTALT 4X
    bygning1.lesAar();         cout << '\n'; //    FUNKSJONER TILGJENGELIG!!!
    bygning1.skrivData();
    bygning1.skrivAar();       cout << '\n';

    Bygning* bygning2;                       //  Det samme - peker til objekt:
    bygning2 = new Bygning;                  //  Lager nytt avledet objekt.
    bygning2->lesData();
    bygning2->lesAar();        cout << '\n';
    bygning2->skrivData();
    bygning2->skrivAar();      cout << '\n';

    return 0;
}

// ***************************************************************************
// **   ALTSÅ: Fortsatt mulig med objekter av typen "baseklasse", disse     **
// **          forblir uendret, akkurat som om subklasser ikke finnes.      **
// **   Baseklasse har IKKE tilgang til innholdet i avledede klasser.       **
// **   (for den vet jo ikke at de(n) finnes!)                              **
// ***************************************************************************