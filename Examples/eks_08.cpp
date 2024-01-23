/**
 *   Programeksempel nr 8 - vector med objekt-pekere,
 *                          samt litt om 'this' og const-funksjoner.
 *
 *   @file     EKS_08.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Emne (med kode, tittel, studiepoeng og antall timer totalt pr.uke)
 */
class Emne {
  private:
    string  kode,
            tittel;
    float   stp;
    int     timerPrUke;
  public:
    Emne()  { 
        kode = tittel = "";   stp = timerPrUke = 0; 
    }

    Emne(string k, string t, float stp, int timerPrUke)  {
        kode = k;   
        tittel = t;   
        this->stp = stp;    // OM parametre skulle hete eksakt det samme som
                            //   datamedlemmet, må det løses på denne måten
                            //   (mye brukt i Java):
        this->timerPrUke = timerPrUke;
    }

    void lesData()  {
        cout << "\tKode:    ";   getline(cin, kode);
        cout << "\tTittel:  ";   getline(cin, tittel);
        stp = lesFloat("\tStudiepoeng", 2.5, 30);
        timerPrUke = lesInt("\tTimer pr.uke", 1, 12);
    }

    void skrivData() const {         //  const - da ENDRER IKKE DATAMEDLEMMER.
        cout << '\t' << kode << ",  " << stp << " stp, " 
             << timerPrUke << " t pr.uke   " << tittel << '\n';
    }
};


vector <Emne*> gEmnene;       ///<  Datastrukturen med pekere til ALLE emnene.


/**
 *  Hovedprogrammet:
 */
int main()  {
    Emne* nyttEmne;           //  Hjelpepeker til nye objekter.

                              //  Legger initielt inn 2x emner:
    nyttEmne = new Emne("PROG1001", "Grunnleggende programmering", 7.5, 6);
    gEmnene.push_back(nyttEmne);
    nyttEmne = new Emne("PROG1003", "Objekt-orientert programmering", 7.5, 6);
    gEmnene.push_back(nyttEmne);
                              //  Skriver det hittil lagrede:
    cout << "\nAntall emner lagret hittil:  " << gEmnene.size()
        << "  og det er:\n";
    gEmnene[0]->skrivData();
    gEmnene[1]->skrivData();

                              //  Leser inn nye emner:
    cout << "\n\nLeser inn nye emner:\n";
    do {
        nyttEmne = new Emne;             //  Parameterløs constructor kjøres.
        nyttEmne->lesData();             //  Leser selv sine datamedlemmer.
        gEmnene.push_back(nyttEmne);     //  Legger inn i vectoren.
                                         //  Skriver dets nr. i arrayen:
        cout << "\n\tLagt inn emne nr." << gEmnene.size() << "\n\n";
    } while (lesChar("Flere emner (J/n)") != 'N');


    for (int i = 0; i < gEmnene.size(); i++)   //  Skriver ALLE emnene:
        gEmnene[i]->skrivData();


    for (int i = 0; i < gEmnene.size(); i++)   //  Sletter ALLE emnene:
        delete gEmnene[i];
    gEmnene.clear();                           //  Sletter alle PEKERNE.
                                              
                                               //  vectoren er nå tom igjen:
    cout << "\nAntall emner lagret nå:  " << gEmnene.size() << "\n\n";

    return 0;
}