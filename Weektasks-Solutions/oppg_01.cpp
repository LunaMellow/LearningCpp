/**
 *   Løsningsforslag til oppgave nr 1 (basert på oppg.nr 17 i PROG1001).
 *
 *   @file	  OPPG_01.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <iomanip>                 //  setprecision
#include <cctype>                  //  toupper
using namespace std;

const int MAXLOPERE = 10;          ///<  Max. antall løpere å lese tider for.

/**
 *  Hovedprogrammet:
 */
int main()  {
    int   distanse,               //  Aktuell distanse.
          ant500,                 //  'distanse' består av 'ant500' 500-metre.
          min, sek, hundr,        //  Minutt, sekund og hundredeler.
          antallLopere;           //  Antall løpere det beregnes poengsum for.
    float poeng;                  //  Poengsummen på distansen.
    char  brukerSvar;             //  Brukerønske om å gjenta hele programmet.

    do  {
      do  {
        cout << "\nSkriv en skøytedistanse (500, 1500, 3000, 5000):  ";
        cin >> distanse;          //  Leser en distanse.
      } while (distanse != 500   &&  distanse != 1500 &&
               distanse != 3000  &&  distanse != 5000); // Gjentar til lovlig.

      ant500 = distanse / 500;    //  Beregner antall 500-metre i distansen.

      do  {
        cout << "\nAntall løpere å lese tider for (1-" << MAXLOPERE << "): ";
        cin >> antallLopere;      //  Leser inntil lovlig løperantall:
      } while (antallLopere < 1  ||  antallLopere > MAXLOPERE);

      cout << fixed << showpoint << setprecision(3);  //  Setter 3 desimaler.
      for (int i = 1;  i <= antallLopere;  i++)  {    //  For hver løper:
          do  {
            cout << "\nTid (mm ss hh):  ";
            cin >> min >> sek >> hundr;             //  Leser POSITIVE verdier
          } while (min < 0  ||  sek < 0  || hundr < 0);  //   i tiden.
                                                    //  Beregner poengsummen:
          poeng =  ((min*60) + sek + (hundr/100.0F)) / ant500;
          cout << "\tPoengsum:  " << poeng;         // Skriver denne.
      }

      cout << "\n\nLese tider om en ny distanse (j/N):  ";
      cin >> brukerSvar;
      brukerSvar = toupper(brukerSvar);
    } while (brukerSvar == 'J');              //  Gjenta HELE proogrammet?

    return 0;
}
