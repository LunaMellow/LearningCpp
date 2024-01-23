/**
 *   L�sningsforslag til oppgave nr 12.
 *
 *   Program som lager et �nsket antall Kunde-objekter.
 *   Pr.kunde sp�rres det etter navn og antall bankkontoer vedkommende har,
 *   og innest�ende bel�p p� hver konto leses inn fra brukeren.
 *   Til slutt skrives en oversikt over alle kundene og deres kontoer (bel�p),
 *   f�r alle objektene og deres allokerte data slettes/frigis.
 *
 *   @file    OPPG_12.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


class Kunde {
  private:
      string navn;                      //  Kundens navn.
      vector <float>* kontoer;          //  PEKER til kontoene og deres bel�p.

  public:
    Kunde()  { cout << "\n'Kunde' M� opprettes med kontoantall-parameter."; }

    Kunde(const int n)  {
        kontoer = new vector <float>(n);     //  Oppretter dynamisk en vector.
        for (int i = 0; i < n; i++)  (*kontoer)[i] = 0.0F;   // NB:  KODEN !!!
    }

    ~Kunde()  {  delete kontoer;  }     //  Sletter konto-vectoren.

     void lesData()  {                  //  Leser navn og bel�pene pr.konto:
         cout << "\tKundens navn:  ";   getline(cin, navn);
         for (int i = 0;  i < kontoer->size();  i++)  {
             cout << "\tBel�pet p� konto nr." << i+1;
             (*kontoer)[i] = lesFloat("", 0, 10000000);      //  Skrivem�ten!!
         }
     }

    void skrivData() const  {    //  Viser navnet og bel�pet p� ALLE kontoene:
        cout << " (" << navn << ") har kontoer med f�lgende bel�p:";
        for (int i = 0;  i < kontoer->size();  i++)
            cout << "\n\tKonto nr." << i+1 << ": " << (*kontoer)[i];
    }
};


vector <Kunde*> gKunder;                ///<  Kunde-datastrukturen.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;                       //  Brukervalg til flere kunder eller ei.
    Kunde* nyKunde;                  //  Nytt Kunde-objekt.

    do {
        cout << "\n\n\nAntall kontoer for kunde nr." << gKunder.size()+1;
                                     //  Leser antall kontoer og oppretter
        nyKunde = new Kunde(lesInt("", 1, 20));    //   nytt Kunde-objekt.

        nyKunde->lesData();          //  Kunden leser selv sine kontobel�p.

        gKunder.push_back(nyKunde);  //  Lagrer kunden i datastrukturen.
                                     //  Flere kunder?
    } while (lesChar("\n\nRegistrere flere kunder (J/n)") != 'N');


    cout << "\n\n";                   //  Skriver kundene og deres kontobel�p:
    for (int i = 0;  i < gKunder.size();  i++)  {
        cout << "\n\nKunde nr." << i+1;
        gKunder[i]->skrivData();
        delete gKunder[i];            //  Sletter Kunde-objektet.
    }
    gKunder.clear();                 //  Sletter ALLE PEKERNE.

    cout << "\n\n";
    return 0;
}
