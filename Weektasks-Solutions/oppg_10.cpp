/**
 *   Løsningsforslag til oppgave nr 10.
 *
 *   Program som gjør og fungerer EKSAKT likt med EKS_06.cpp, bare at det
 *   brukes 'class' istedet for 'struct'. Kommandoen '2' er fjernet.
 *
 *   @file    OPPG_10.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Bok (med tittel, forfatter, antall sider og om lest eller ei).
 */
class Bok  {
  private:
    string tittel,
           forfatter;
    int    antallSider;
    bool   lest;
  public:
      Bok()  {  tittel = forfatter = "";   antallSider = 0;   lest = false;  }
      void lesData();
      void lestBoken();
      void skrivData() const;
};


void fjernBok();
void lestBok();
void nyBok();
void skrivAlleBoker();
void skrivBok();
void skrivMeny();
void slettAlt();


vector <Bok*> gBokene;        ///<  Alle bøkene i oversikten/datastrukturen.
                              //   NB:  Trenger nå ikke lengre 'gAntallBoker',
                              //        da gBokene.size() er dette antallet.

/**
 *  Hovedprogrammet:
 */
int main() {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'N': nyBok();            break;
          case 'S': skrivBok();         break;
          case 'D': skrivAlleBoker();   break;
          case 'L': lestBok();          break;
          case 'F': fjernBok();         break;
          default:  skrivMeny();        break;
        }
        kommando = lesChar("\nKommando");
    }

    slettAlt();

    return 0;
}


/**
 *  Leser inn og fyller ALLE boken sine datamedlemmer.
 */
void Bok::lesData()  {
    cout << "\tTittel:     ";       getline(cin, tittel);
    cout << "\tForfatter:  ";       getline(cin, forfatter);
    antallSider = lesInt("\tAntall sider", 1, 2000);
    lest = false;
}


/**
 *  Setter boken som lest.
 */
void Bok::lestBoken()  {
    cout << "\n\tBoken er markert/satt som 'Lest'.\n";
    lest = true;
}


/**
 *  Skriver ALLE datamedlemmene i boken.
 */
void Bok::skrivData() const  {
   cout << "\t\t\"" << tittel << "\" av " << forfatter << ",  " << antallSider
        << " sider - " << ((!lest) ? "IKKE " : "") << "lest\n";
}


/**
 *  Ønsket boknummer slettes, og bakerste flyttes til den slettedes plass.
 */
void fjernBok()  {
  if (!gBokene.empty())  {                         //  Bøker er registrert:
     int nr = lesInt("\tFjerne bok nr", 1, gBokene.size());  //  Ønsket nr.
     delete gBokene[nr - 1];                     //  Sletter aktuell bok!
     gBokene[nr-1] = gBokene[gBokene.size()-1];  //  Bakerste flyttes frem.
     gBokene.pop_back();                         //  Siste PEKER slettes også!
  } else
      cout << "\n\tUmulig å fjerne, da ingen bøker registrert!\n";
}


/**
 *  Ønsket boknummer markeres som lest.
 *
 *  @see   Bok::lestBoken()
 */
void lestBok() {
  if (!gBokene.empty())             //  Bøker er registrert:
      gBokene[lesInt("\tLest bok nr", 1, gBokene.size())-1]->lestBoken();
  else
      cout << "\n\tUmulig å sette bok som lest, da ingen bøker registrert!\n";
}


/**
 *  Ny bok legges inn i datastrukturen (vectoren 'gBokene').
 *
 *  @see   Bok::lesData()
 */
void nyBok() {
    Bok* nyBok = new Bok;         //  Oppretter et nytt Bok-objekt.
    cout << "\nNy bok:\n";
    nyBok->lesData();             //  Alle dens data leses inn.
    gBokene.push_back(nyBok);     //  Legges bakerst i vectoren.
    cout << "\n\tNy bok innlagt har nr." << gBokene.size() << '\n';
}


/**
 *  Overloaded funksjon som skriver alle bøkene vha. PEKER.
 *
 *  @see   Bok::skrivData()
 */
void skrivAlleBoker() {
    for (int i = 0; i < gBokene.size(); i++) {
        cout << "\tBok nr." << setw(2) << i + 1 << ":\n";
        gBokene[i]->skrivData();
    }
}


/**
 *  Skriver alt en ETT ønsket boknummer.
 *
 *  @see   Bok::skrivData()
 */
void skrivBok() {
  if (!gBokene.empty())             //  Bøker er registrert:
      gBokene[lesInt("\tSe bok nr", 1, gBokene.size())-1]->skrivData();
  else
      cout << "\n\tUmulig å skrive EN gitt bok, da ingen bøker registrert!\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny bok\n"
         << "\tS - Skriv EN gitt bok\n"
         << "\tD - Display ALLE bøker\n"
         << "\tL - Lest en bok\n"
         << "\tF - Fjern en gitt bok\n"
         << "\tQ - Quit / avslutt\n";
}


/**
 *  Sletter/fjerner ALLE tilpekte Bok-objekter, og alle pekerne i vectoren.
 */
void slettAlt() {
    for (int i = 0; i < gBokene.size(); i++) // Sletter ALLE bøkene/objektene:
        delete gBokene[i];
    gBokene.clear();                      //  Fjerner ALLE PEKERNE i vectoren.

    cout << "\n\nvectoren er tom - antallet er: " << gBokene.size() << "\n\n";
}
