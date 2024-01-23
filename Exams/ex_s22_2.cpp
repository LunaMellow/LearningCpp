/**
 *   Løsningsforslag til kontinuasjonseksamen i OOProg (i C++), aug 2022, oppg 2.
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
    void skrivTilFil(ofstream & ut)  const;   //  EXTRA
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
    void skrivTilFil(ofstream & ut)   const;  //  EXTRA
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
void skrivTilFil();                           //  EXTRA
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

  skrivTilFil();                                  //  EXTRA

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
  getline(inn, adresse);
  inn >> telefon >> antStjerner >> antallPlasser >> antallBesok;
  inn.ignore();
}


/**
 *  Oppgave 2D - Inn ALLE egne datamedlemmer.
 */
void Restaurant::lesData()  {
  cout << "\tAdresse: ";    getline(cin, adresse);
  telefon       = lesInt("\tTelefon", 10000000, 99999999);
  antStjerner   = lesInt("\tAntall Michelin-stjerner", 0, 3);
  antallPlasser = lesInt("\tAntall bordplasser", 5, 120);
  antallBesok = 0;
}


/**
 *  Oppgave 2E - Skriver ALLE data ut på skjermen om restauranten.
 */
void Restaurant::skrivData() const  {
    cout << adresse << ",  tlf: " << telefon << "\n\t\t\t"
         << "M-stjerner: " << antStjerner
         << "   Ant.plasser: " << antallPlasser
         << "   Ant.besøk: " << antallBesok << '\n';
}


/**
 *  EXTRA - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Restaurant::skrivTilFil(ofstream & ut)  const  {
  ut << adresse << '\n' << telefon << ' ' << antStjerner << ' '
     << antallPlasser << ' ' << antallBesok << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2H -  Leser inn ALLE egne data fra fil.
 *
 *  @param   inn  -  Filobjektet det leses inn data fra
 *  @see     Restaurant::Restaurant(...)
 */
By::By(ifstream & inn)  {
  int antallRestauranter;
  string nvn;                                       //  Restaurants navn.

  getline(inn, navn);                               //  Byens navn.
  getline(inn, land);
  inn >> antallRestauranter;  inn.ignore();

  for (int i = 1;  i <= antallRestauranter;  i++) { //  Leser/legger inn ALLE
    getline(inn, nvn);                              //    byens restauranter:
    restaurantene[nvn] = new Restaurant(inn);
  }
}


/**
 *  Oppgave 2I -  Sletter alle eksisterende/allokerte restauranter.
 */
By::~By()  {
  Restaurant* it = nullptr;
  while (!restaurantene.empty())  {
    it = (restaurantene.begin())->second;     //  PEKER til FØRSTE restaurant.
    delete it;                                //  Sletter den TILPEKTE.
    restaurantene.erase(restaurantene.begin()); // Sletter PARET key og PEKER.
  }
//  Alternativt for de tre siste linjene ovenfor:
//    auto it = restaurantene.begin();
//    delete (it->second);                    //  Sletter den TILPEKTE.
//    restaurantene.erase(it);                //  Sletter PARET key og PEKER.
}


/**
 *  Oppgave 2D -Legger inn (om mulig) en ny restaurant i byen.
 *
 *  @see   Restaurant::Restaurant()
 *  @see   Restaurant::lesData()
 */
void By::leggInnNyRestaurant()  {
  Restaurant* nyRestaurant = nullptr;
  string nvn;                                      //  Restaurants navn.

  cout << "\tRestaurantnavn: ";   getline(cin, nvn);
  if (restaurantene.find(nvn) == restaurantene.end())  {  //  Finnes IKKE:
     nyRestaurant = new Restaurant();              //  Oppretter en ny.
     nyRestaurant->lesData();                      //  Leser selv egne data.
     restaurantene[nvn] = nyRestaurant;            //  Legger inn i mapen.
  } else
    cout << "\n\tFinnes en restaurant med dette navnet i byen allerede!\n\n";
}


/**
 *  Oppgave 2C - Leser KUN inn hvilket land byen ligger i.
 */
void By::lesData()  {
  cout << "\tLand: ";   getline(cin, land);
}


/**
 *  Oppgave 2E - Skriver ALT om ALLE restaurantene i byen.
 *
 *  @see   Restaurant::skrivData()
 */
void By::skrivAlt() const  {
  cout << "\n\t" << navn << ", " << land << "  med restaurantene:\n";
  for (const auto & val : restaurantene) {
    cout << "\t\t" << val.first << ", ";     //  Skriver:  - restaurantnavn
      (val.second)->skrivData();             //            - resten av dataene
  }
}


/**
 *  Oppgave 2B - Skriver alle byens HOVEDdata.
 */
void By::skrivData()  const  {
  cout << '\t' << navn << ", " << land << "  med "
       << restaurantene.size() << " restauranter:\n";
  for (const auto & val : restaurantene)
      cout << "\t\t- " << val.first << '\n';  // Skriver KUN restaurantnavnet.
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
  cout << '\t' << navn << ":\n";
  for (const auto & val : restaurantene)  {             // Har MINST 'antallS'
      if ((val.second)->hentAntStjerner() >= antallS) { //   stjerner:
        cout << "\t\t" << val.first << ", ";  //  Skriver: - restaurantnavn
        (val.second)->skrivData();            //           - resten av dataene
      }
  }
}


/**
 *  Oppgave 2G - Skriver (om mulig) alle restauranter med et gitt (del)navn.
 *
 *  @param    nvn  -  Aktuelt (del)navn på restaurant
 *  @see      Restaurant::skrivData(...)
 */
void By::skrivData(const string nvn)  const  {
  int antall = 0;                                    //  Nullstiller antallet.

  cout << '\t' << navn << ":\n";
  for (const auto & val : restaurantene)  {              //  Restaurantnavnet
      if ((val.first).find(nvn) < (val.first).length()) { // INNEHOLDER 'nvn':
        antall++;                             //  Teller opp antallet.
        cout << "\t\t" << val.first << ", ";  //  Skriver: - restaurantnavn
        (val.second)->skrivData();            //           - resten av dataene
      }
  }
  cout << "\t\tAntall restauranter med navnetreff: " << antall << "\n\n";
}


/**
 *  EXTRA - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 *  @see     Restaurant::skrivTilFil(...)
 */
void By::skrivTilFil(ofstream & ut)  const {
  ut << navn << '\n' << land << '\n' << restaurantene.size() << '\n';
  for (const auto & val : restaurantene)  {
      ut << val.first << '\n';                //  Skriver: - restaurantnavn
      (val.second)->skrivTilFil(ut);          //           - resten av dataene
  }
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
  for (unsigned int i = 0;  i < gByene.size();  i++)
      if (gByene[i]->hentID() == nvn) return i;    //  Bynavnet funnet.
  return -1;                                       //  Ikke funnet.
}


/**
 *  Oppgave 2H - Leser ALLE byene og restaurantene inn fra fil.
 *
 *  @see   By::By(...)
 *  @see   By::hentID()
 */
void lesFraFil()  {
  ifstream innfil("EX_S22_RESTAURANTER.DTA");
  int  antallByer;                             //  Antall byer på filen.

  if (innfil) {                                //  Filen finnes:
      cout << "\n\n\tLeser fra filen 'EX_S22_RESTAURANTER.DTA'......\n\n";

      innfil >> antallByer;   innfil.ignore(); //  Leser lokal variabel.

      for (int i = 1;  i <= antallByer;  i++)  //  Leser og legger inn ALLE
          gByene.push_back(new By(innfil));    //    byene og restauranter.

                                               //  Sorterer byene alfabetisk:
      sort(gByene.begin(), gByene.end(), [] (const By* b1, const By*b2)
          {  return (b1->hentID() < b2->hentID());  });

      innfil.close();                          //  Lukker filen manuelt.
  } else                                       //  Filen finnes IKKE:
      cout << "\n\n\tFant ikke filen 'EX_S22_RESTAURANTER.DTA'!\n\n";
}


/**
 *  Oppgave 2C - Legger inn (om mulig) en ny by.
 *
 *  @see  By::By(...)
 *  @see  By::lesData()
 */
void nyBy()  {
  By* nyBy;
  string navn;

  cout << "\n\tNytt bynavn:  ";    getline(cin, navn);

  if (finnBy(navn) < 0)  {           //  Likenavnet by IKKE funnet:
     nyBy = new By(navn);            //  Lager et nytt By-objekt.
     nyBy->lesData();                //  Leser selv inn alle sine data.
     gByene.push_back(nyBy);         //  Legges bare usortert inn bakerst.
  } else
    cout << "\n\tByen finnes fra før!\n\n";
}


/**
 *  Oppgave 2D - Legger inn (om mulig) ny restaurant i en eksisterende by.
 *
 *  @see   finnBy(...)
 *  @see   By::leggInnNyRestaurant()
 */
void nyRestaurant()  {
  string navn;
  int byIndeks;

  cout << "\n\tNy restaurant i byen:  ";    getline(cin, navn);
  if ((byIndeks = finnBy(navn))  >= 0)         //  Byen funnet/eksisterer.
     gByene[byIndeks]->leggInnNyRestaurant();  //  Legger inn ny restaurant.
  else
     cout << "\n\tIngen by med dette navnet!\n\n";
}


/**
 *  Oppgave 2B - Skriver ALLE byenes hoveddata.
 *
 *  @see   By::skrivData()
 */
void skrivAlle()  {
  for (const auto & val : gByene)
      val->skrivData();
}


/**
 *  Oppgave 2E - Skriver (om mulig) ALT om ALLE restaurant i en gitt by.
 *
 *  @see   finnBy(...)
 *  @see   By::skrivAlt()
 */
void skrivAltIEnBy()  {
  string navn;
  int byIndeks;

  cout << "\n\tSkrive ALT om byen:  ";    getline(cin, navn);
  if ((byIndeks = finnBy(navn))  >= 0)    //  Byen funnet/eksisterer.
     gByene[byIndeks]->skrivAlt();        //  Skriver ALLE byens restauranter.
  else
     cout << "\n\tIngen by med dette navnet!\n\n";
}


/**
 *  Oppgave 2F - Skriver ALLE restauranter i ALLE byer
 *               med et visst antall MINIMUM Michelin-stjerner.
 *
 *  @see   By::skrivData(...)
 */
void skrivMedStjerner()  {
  int antallStjerner;

  antallStjerner = lesInt("\n\tMINIMUM antall stjerner på restaurantene",
                           0, MAXSTJERNER);
  cout << '\n';
  for (const auto & val : gByene)       //  Skriver ALLE restauranter med
      val->skrivData(antallStjerner);   //   MINST dette antall stjerner.
}


/**
 *  Oppgave 2G - Skriver ALLE restauranter i ALLE byer med et gitt (del)navn.
 *
 *  @see   By::skrivData(...)
 */
void skrivNavngitte()  {
  string navn;

  cout << "\t(Del av) restaurantnavn: ";    getline(cin, navn);  cout << '\n';
  for (const auto & val : gByene)       //  Skriver ALLE restauranter med et
      val->skrivData(navn);             //   navn INNEHOLDENDE 'navn'.
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   A  - skriver Alle byene og navnene på Alle restaurantene i dem\n"
       << "   B  - ny By\n"
       << "   R  - ny Restaurant (i en gitt by)\n"
       << "   E  - skriv alt om alle restaurantene En gitt by\n"
       << "   S  - skriv alle restauranter med et minimum antall Stjerner\n"
       << "   N  - skriv alle restauranter med en gitt tekst i Navnet\n"
       << "   Q  - Quit / avslutt\n";
}


/**
 *  EXTRA - Skriver ALLE byene og restaurantene ut til fil.
 *
 *  @see   By::skrivTilFil(...)
 */
void skrivTilFil()  {
  ofstream utfil("EX_S22_RESTAURANTER.DT2");

  cout << "\n\tSkriver alle byene til filen 'EX_S22_RESTAURANTER.DT2' ....\n";
                                           //  Skriver antall byer i vectoren:
  utfil << gByene.size() << '\n';

  for (const auto & val : gByene)          //  Hver by skriver seg selv:
      val->skrivTilFil(utfil);

  utfil.close();                           //  Lukker filen manuelt.
}


/**
 *  Oppgave 2I - Sletter HELE datastrukturen fra memory.
 *
 *  @see   By::~By()
 */
void slettAlt()  {
  for (const auto & val : gByene)          //  Sletter ALLE by-objektene:
      delete val;
  gByene.clear();                          //  Sletter PEKERNE til byene.
}
