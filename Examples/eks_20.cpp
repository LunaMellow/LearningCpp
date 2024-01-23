/**
 *   Programeksempel nr 20 - Direkteposisjonering på fil.
 *
 *   Eksemplet viser/vektlegger hvordan regne ut og DIREKTEPOSISJONERE
 *   seg (lese og skrive) på en ASCII-fil, der alle postene er like lange.
 *
 *   @file     EKS_20.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <fstream>                 //  fstream
#include <iomanip>                 //  setw
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;

/**
 *  Merke (med katalognummer, pålydende/påtrykt verdi,
 *         estimert katalogverdi, har (ikke) merket, antall duplikater).
 */
class Merke  {
  private:
    int  nummer;
    int  paalydendeVerdi;
    int  katalogVerdi;
    bool harMerket;
    int  antallBytte;

  public:
    Merke(fstream & inn);
    void editerData();
    void skrivData();
    void skrivTilFil(fstream & ut);
};


const int ANTMERKER = 2000;    ///<  EKSAKT 2000 norske frimerker pr 4/1-2019.
const int TEGNPRLINJE = 32;    ///<  Antall tegn pr post (linje) inkl '\n'.
                               //      (KAN være 31 på noen plattformer/OSer.)

/**
 *  Hovedprogrammet:
 */
int main()  {
    int nr;                              //  Frimerkenummer som brukeren
                                         //    vil se/editere på.
    Merke* merket;                       //  Det ENE merket innlest fra fil.

                                //  Åpner fil for BÅDE innlesning OG utskrift:
    fstream fil("eks_20.dta", ios::in | ios::out);

    if (fil)  {                          //  Mulig å åpne filen:

        nr = lesInt("Hvilket merke vil du se (0 = avslutte)", 0, ANTMERKER);

        while (nr != 0)  {               //  Så lenge vil se/editere merker:
                                //  Posisjonerer GETpointer EKSAKT for lesing:
          fil.seekg((nr-1) * TEGNPRLINJE, ios::beg);
                                         //  'ios::beg' er overflødig,
                                         //    da dette er default.
                                         //  SE TABLE 13-5 og 13-6 !!!
          cout << "\n\tgetpointer:  " << fil.tellg() << '\n';  // Hvor er den?

          merket = new Merke(fil);       //  Merket opprettes og leser.
          cout << "\n\tgetpointer:  " << fil.tellg() << '\n';  // Hvor er den?

          merket->skrivData();           //  Merkets data skrives på SKJERMEN.

          if (lesChar("Editere verdiene (j/N)") == 'J')  {
                    merket->editerData();      //  Endrer data(ene).

                    merket->skrivData(); //  Merkets nye(?) data skrives ut.

                              //  Posisjonerer PUTpointer EKSAKT for skriving:
                    fil.seekp((nr-1) * TEGNPRLINJE, ios::beg);
                    cout << "\n\tputpointer:  " << fil.tellp() << '\n';

                    merket->skrivTilFil(fil);  //  Skriver ALT til FIL.
                    cout << "\n\tputpointer:  " << fil.tellp() << '\n';
          }

          delete merket;                 //  Opprettet merke slettes.

          nr = lesInt("Hvilket merke vil du se (0 = avslutte)", 0, ANTMERKER);
        }

        fil.close();
    } else
        cout << "\n\tFant ikke filen 'EKS_20.DTA'!\n\n";

    return 0;
}


/**
 *  ALLE merkets datamedlemmer leses inn fra fil.
 *
 *  @param   inn  - Filen det leses inn fra
 */
Merke::Merke(fstream & inn)  {
    int har;
    inn >> nummer >> paalydendeVerdi >> katalogVerdi >> har >> antallBytte;
    harMerket = (har == 1);
}


/**
 *  Tilbyr og lar brukeren endre på tre av merkets verdier.
 */
void Merke::editerData() {
    int valg;

    do {
        cout << "\n\nHvilken verdi vil du endre:\n"   //  Ber om aktuell verdi
            << "\t1 = Katalog verdi\n"                //    å endre:
            << "\t2 = Har merket i samlingen\n"
            << "\t3 = Antall til bytte\n"
            << "\t0 = avslutt\n";
        valg = lesInt("Angi nummer", 0, 3);

        switch (valg) {                           //  Oppdaterer ny verdi:
          case 1:  katalogVerdi = lesInt("Ny verdi", 1, 20);            break;
          case 2:  harMerket    = (lesChar("Har merket (J/n)") != 'N'); break;
          case 3:  antallBytte  = lesInt("Ant.bytte", 0, 19);           break;
        }
    } while (valg != 0);
}


/**
 *  ALLE merkets datamedlemmer skrives ut på skjermen.
 */
void Merke::skrivData()  {
    cout << "\n\nNummer:\t\t"     << nummer
         << "\n\tPålydende:\t"    << paalydendeVerdi
         << "\n\tKatalogverdi:\t" << katalogVerdi
         << "\n\tHar merket:\t"   << ((harMerket) ? "Ja" : "Nei")
         << "\n\tAntall bytte:\t" << antallBytte << '\n';
}


/**
 *  ALLE merkets datamedlemmer skrives til fil.
 *
 *  @param   ut  - Filen det skrives ut til
 */
void Merke::skrivTilFil(fstream & ut)  {
    ut << setw(6) << nummer                      //  Frimerkets nummer.
       << setw(6) << paalydendeVerdi             //  Merkets PÅLYDENDE verdi.
       << setw(6) << katalogVerdi                //  Merkets KATALOG-verdi.
       << setw(6) << ((harMerket) ? 1 : 0)       //  Har merket eller ei.
       << setw(6) << antallBytte;                //  Antall byttemerker.
}
