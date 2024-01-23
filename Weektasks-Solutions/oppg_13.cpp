/**
 *   Løsningsforslag til oppgave nr 13.
 *
 *   Program som inneholder klassen 'Publikasjon' og dens 
 *   subklasser/avledede klasser 'Bok' og 'Blad'.
 *
 *   @file    OPPG_13.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Publikasjon (med navn og årstall for utgivelse).
 */
class Publikasjon  {
  private:
    string navn;
    int    aar;

  public:
    void lesData()  {                              //  Leser ALLE egne data:
        cout << "\tPublikasjonstittel:  ";   getline(cin, navn);
        aar   = lesInt("\tÅr   ", 1900, 2020);
    }

    void skrivData() const  {                      //  Skriver ALLE egne data:
        cout << "\tNavn: " << navn << ",  "  << aar << '\n';
    }
};


/**
 *  Bok (med forfatter, ISBN-nummer og pris).
 */
class Bok : public Publikasjon  {
  private:
    string forfatter,
           ISBN;
    float  pris;

  public:
    void lesData()   {
        cout << "\nLeser bok-detaljer:\n";
        Publikasjon::lesData();                  //  Kaller den i baseklassen.
        cout << "\tForfatternavn:  ";   getline(cin, forfatter); // Leser ALLE
        cout << "\tISBN-nummer:    ";   getline(cin, ISBN);      // egne data:
        pris = lesFloat("\tPris", 1, 2000);
    }

    void skrivData()  const  {
        cout << "\nBok-data:\n";
        Publikasjon::skrivData();                //  Kaller den i baseklassen.
        cout << "\t\tForfatter:  " << forfatter  //  Skriver ALLE egne data:
             << "  ISBN: " << ISBN << "  Pris: " << pris << '\n';
    }
};


/**
 *  Blad (med nummer, ukenummer, abonnementspris pr.år).
 */
class Blad : public Publikasjon  {
  private:
      int   nummer,
            ukeNr,
            aarsAbonnement;

  public:
    void lesData()  {
        cout << "\nLeser blad-detaljer:\n";
        Publikasjon::lesData();                  //  Kaller den i baseklassen.
        nummer = lesInt("\tNummer", 1, 53);      //  Leser ALLE egne data:
        ukeNr  = lesInt("\tUkenr ", 1, 53);
        aarsAbonnement = lesInt("\tÅrsabonnementspris", 50, 5000);
    }

    void skrivData()  const  {
        cout << "\nBlad-data:\n";
        Publikasjon::skrivData();                //  Kaller den i baseklassen.
        cout << "\t\tUke: " << ukeNr << "  Nr: " << nummer //  Skriver ALLE 
             << "  Årspris: " << aarsAbonnement << '\n';   //    egne data:
    }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Bok bok;                //  Lager 2x objekter av de avledede klassene:
    Blad blad;

    bok.lesData();          //  ALLE datamedlemmene i begge objektene leses:
    blad.lesData();
    cout << "\n\n";

    bok.skrivData();        //  ALLE datamedlemmene i begge objektene skrives:
    blad.skrivData();

    return 0;
}