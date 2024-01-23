/**
 *   Løsningsforslag til oppgave nr 11.
 *
 *  Program som leser inn og skriver ut posisjonen (bredde- og lengdegrad)
 *  for tre skip. Inneholder objekter inni objekter (aggregation/composition).
 *
 *   @file    OPPG_11.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Posisjon (med lengde-/breddegrad, minutt, sekund og retning).
 */
class Posisjon  {
  private:
    int  grad;             //  Grad (0-90 eller 0-180).
    int  minutt;           //  Minutter (0-59).
    int  sekund;           //  Sekunder (0-59).
    char retning;          //  N/S  eller  E/W.

  public:                   
    Posisjon()  {          //  Initierer/nullstiller 4x datamedlemmer:
        grad = minutt = sekund = 0;   retning = 'X'; 
    }                                 //  Dummyverdi for 'retning'.
                           //  Leser inn 4x LOVLIGE verdier/datamedlemmer:
    void lesData(int gr, char r1, char r2)  {
        grad    = lesInt("grad", 0, gr);
        minutt  = lesInt("Minutter", 0, 59);
        sekund  = lesInt("Sekunder", 0, 59);
        do {               //  Sikrer at retninger er lovlig (NS eller EW):
            cout << "Retning (" << r1 << ',' << r2 << "):  ";
            retning = lesChar("");
        } while (retning != r1  &&  retning != r2);
    }

    void skrivData() const  {    // Skriver på formen: XºX'X" X  
        cout << grad << char(248)   //  248 = grad-symbol, evt. nr.167(?)
             << minutt << '\'' << sekund << '\"' << ' ' << retning;
    }
};


/**
 *  Skip (med nummer, navn og objekter for bredde og lengdegrad).
 */
class Skip {                //  Klassen "Skip":
private:
    int      nr;                //  (Unikt) nummer.
    string   navn;              //  Navn.
    Posisjon breddegrad;        //  Posisjon i breddegrad (0-90 N/S)
    Posisjon lengdegrad;        //    og lengdegrad (0-180 E/W).

public:
    Skip(int n, string s)  {    //  Setter skipets (unike) nummer og navn:
        nr = n;     navn = s;
    } 

    void lesData()  {          //  Leser inn eksakt posisjon:
        cout << "\nBredde";  breddegrad.lesData(90, 'N', 'S');
        cout << "\nLengde";  lengdegrad.lesData(180, 'E', 'W');
    }

    void skrivData() const  {        //  Skriver alle skipets data:
        cout << "\nSkipets nr: " << nr << "  og navn:  " << navn
             << "\t\tbreddegrad: ";  breddegrad.skrivData();
        cout << "\tlengdegrad: ";    lengdegrad.skrivData();
    }
};


/**
 *  Hovedprogrammet:
 */
int main()  {             //  Lager 3x skips-objekter, gir dem nummer og navn:
    Skip MorningStar(71, "Morning Star"), 
         BalticQueen(94, "Baltic Queen"), 
         SongOfSurinam(312, "Song of Surinam");
                               //  Leser inn resten av data om alle 3x skip:
    cout << "\n\nPosisjon for Morning Star:";        MorningStar.lesData();
    cout << "\n\nPosisjon for Baltic Queen:";        BalticQueen.lesData();
    cout << "\n\nPosisjon for Song of Surinam:";     SongOfSurinam.lesData();

    MorningStar.skrivData();   //  Skriver ut ALLE data om alle 3x skip:
    BalticQueen.skrivData();
    SongOfSurinam.skrivData();

    cout << "\n\n";
    return 0;
}
