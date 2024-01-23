/**
 *   Skjelett for kontinuasjonseksamen i OOProg (i C++), august 2022, oppgave 2.
 *
 *   Programmet holder orden på ulike restauranter i ulike byer.
 *
 *   Programmet:
 *      - legger inn en ny UNIK by
 *      - legger inn en ny UNIK restaurant i en gitt by
 *      - skriver:  - navnene på ALLE restaurantene i ALLE byene
 *                  - ALLE data om ALLE restaurantene i EN by
 *                  - ALLE restaurantene med et gitt MINIMUM av stjerner
 *                  - ALLE restaurantene med en gitt (del)navn i navnet sitt
 *      - leser (og skriver) HELE datastrukturen fra fil
 *      - sletter/fjerner alle allokerte data fra hukommelsen/memory
 *
 *   @file     EX_S22_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>              //  cout, cin
#include <fstream>               //  ifstream, ofstream
#include <iomanip>               //  setw
#include <string>
#include <vector>
#include <map>
#include <algorithm>             //  sort
#include "LesData2.h"            //  Verktøykasse for lesing av diverse data
using namespace std;


const int MAXSTJERNER = 3;       ///<  Maksimum antall Michelin-stjerner.


/**
 *  Restaurant (med navn ('first' i map'en), adresse, telefon og
 *              antall av: Michelin-stjerner, bord-/sitteplasser og besøk).
 */
class Restaurant  {
  private:                       //  navn = 'first' ifm. map'en.
    string  adresse;             //  Bl.a. IKKE med: hjemmeside,  mail-adresse
    int     telefon, antStjerner,
            antallPlasser, antallBesok;
  public:
    Restaurant()  { telefon = antStjerner = antallPlasser = antallBesok = 0; }
    Restaurant(ifstream & inn);               //  Oppgave 2H
    int  hentAntStjerner()  const  {  return antStjerner;  }
    void lesData();                           //  Oppgave 2D
    void skrivData()  const;                  //  Oppgave 2E
};


/**
 *  By (med navn, land og (Michelin-)restaurantene i byen).
 */
class By  {
  private:
    string navn, land;
    map <string, Restaurant*> restaurantene;
  public:
    By(const string nvn)  { navn = nvn;  }
    By(ifstream & inn);                       //  Oppgave 2H
    ~By();                                    //  Oppgave 2I
    string hentID()   const  {  return navn;  }
    void leggInnNyRestaurant();               //  Oppgave 2D
    void lesData();                           //  Oppgave 2C
    void skrivAlt()   const;                  //  Oppgave 2E
    void skrivData()  const;                  //  Oppgave 2B
    void skrivData(const int antallS) const;  //  Oppgave 2F
    void skrivData(const string nvn)  const;  //  Oppgave 2G
};


int  finnBy(const string nvn);                //  Oppgave 2A
void lesFraFil();                             //  Oppgave 2H
void nyBy();                                  //  Oppgave 2C
void nyRestaurant();                          //  Oppgave 2D
void skrivAlle();                             //  Oppgave 2B
void skrivAltIEnBy();                         //  Oppgave 2E
void skrivMedStjerner();                      //  Oppgave 2F
void skrivNavngitte();                        //  Oppgave 2G
void skrivMeny();
void slettAlt();                              //  Oppgave 2I


vector <By*> gByene;              ///<  HELE datastrukturen med ALLE byene.


/**
 *  Hovedprogrammet:
 */
int main() {
  char valg;

  lesFraFil();                                    //  Oppgave 2H

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'A': skrivAlle();             break;  //  Oppgave 2B
       case 'B': nyBy();                  break;  //  Oppgave 2C
       case 'R': nyRestaurant();          break;  //  Oppgave 2D
       case 'E': skrivAltIEnBy();         break;  //  Oppgave 2E
       case 'S': skrivMedStjerner();      break;  //  Oppgave 2F
       case 'N': skrivNavngitte();        break;  //  Oppgave 2G
       default:  skrivMeny();             break;
     }
     valg = lesChar("\nKommando");
  }

//  skrivTilFil();                                //  EXTRA

  slettAlt();                                     //  Oppgave 2I

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2H -  Leser inn ALLE egne data fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn data fra
 */
Restaurant::Restaurant(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Inn ALLE egne datamedlemmer.
 */
void Restaurant::lesData()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver ALLE data ut på skjermen om restauranten.
 */
void Restaurant::skrivData() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2H -  Leser inn ALLE egne data fra fil.
 *
 *  @param   inn  -  Filobjektet det leses inn data fra
 *  @see     Restaurant::Restaurant(...)
 */
By::By(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2I -  Sletter alle eksisterende/allokerte restauranter.
 */
By::~By()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D -Legger inn (om mulig) en ny restaurant i byen.
 *
 *  @see   Restaurant::Restaurant()
 *  @see   Restaurant::lesData()
 */
void By::leggInnNyRestaurant()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2C - Leser KUN inn hvilket land byen ligger i.
 */
void By::lesData()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver ALT om ALLE restaurantene i byen.
 *
 *  @see   Restaurant::skrivData()
 */
void By::skrivAlt() const  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver alle byens HOVEDdata.
 */
void By::skrivData()  const  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver (om mulig) alle restauranter med
 *               et MINIMUM av Michelin-stjerner.
 *
 *  @param    antallS  -  Minimum antall stjerner i restaurantene
 *  @see      Restaurant::hentAntStjerner()
 *  @see      Restaurant::skrivData(...)
 */
void By::skrivData(const int antallS) const  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2G - Skriver (om mulig) alle restauranter med et gitt (del)navn.
 *
 *  @param    nvn  -  Aktuelt (del)navn på restaurant
 *  @see      Restaurant::skrivData(...)
 */
void By::skrivData(const string nvn)  const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2A - Leter etter gitt bynavn og returnerer om mulig dets indeks.
 *
 *  @param    nvn  -  Aktuelt bynavn å finne/lete etter.
 *  @return   Indeksen for 'nvn' i 'gByene', evt. -1 (minus en) om intet funn.
 *  @see      By::hentID()
 */
int finnBy(const string nvn)  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2H - Leser ALLE byene og restaurantene inn fra fil.
 *
 *  @see   By::By(...)
 *  @see   By::hentID()
 */
void lesFraFil()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2C - Legger inn (om mulig) en ny by.
 *
 *  @see  By::By(...)
 *  @see  By::lesData()
 */
void nyBy()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Legger inn (om mulig) ny restaurant i en eksisterende by.
 *
 *  @see   finnBy(...)
 *  @see   By::leggInnNyRestaurant()
 */
void nyRestaurant()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver ALLE byenes hoveddata.
 *
 *  @see   By::skrivData()
 */
void skrivAlle()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver (om mulig) ALT om ALLE restaurant i en gitt by.
 *
 *  @see   finnBy(...)
 *  @see   By::skrivAlt()
 */
void skrivAltIEnBy()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ALLE restauranter i ALLE byer
 *               med et visst antall MINIMUM Michelin-stjerner.
 *
 *  @see   By::skrivData(...)
 */
void skrivMedStjerner()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2G - Skriver ALLE restauranter i ALLE byer med et gitt (del)navn.
 *
 *  @see   By::skrivData(...)
 */
void skrivNavngitte()  {

    //   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   A  - skriver Alle byene og navnene på Alle restaurantene i hver\n"
       << "   B  - ny By\n"
       << "   R  - ny Restaurant (i en gitt by)\n"
       << "   E  - skriv alt om alle restaurantene En gitt by\n"
       << "   S  - skriv alle restauranter med et minimum antall Stjerner\n"
       << "   N  - skriv alle restauranter med en gitt tekst i Navnet\n"
       << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2I - Sletter HELE datastrukturen fra memory.
 *
 *  @see   By::~By()
 */
void slettAlt()  {

    //   LAG INNMATEN
}
