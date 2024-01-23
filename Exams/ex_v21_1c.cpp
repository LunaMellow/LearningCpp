/**
 *   Løsningsforslag til eksamen i OOProg (i C++), juni 2021, oppgave 1C.
 *
 *   @file     EX_V21_1C.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


/**
 *  Klassen By (med navn, antall innbyggere og byens areal (i kvkm).
 */
class By  {
  private:
      string navn;
      int antallInnbyggere;
      float kvadratKilometer;

  public:
      By(const string nvn, const int aI, const float kK) {
        navn = nvn;   antallInnbyggere = aI;  kvadratKilometer = kK;
      }

      string hentID() const  {  return (navn);  }

      void skrivData() const  {
        cout << navn << "  #innbyggere: " << antallInnbyggere
             << ",  " << kvadratKilometer << " kvkm\n";
      }
};


map <string, By*> gByene;                  ///<  Global <map> med byer.


/**
 *  Hovedprogrammet:
 */
int main()  {                            //  Hovedprogram med return av 'int'.
    By* nyBy = nullptr;                  //  By-peker som nullstilles.

    nyBy = new By("Hamar", 31369, 350.94);      //  Lager et nytt By-objekt.
                                                //  Inn i <map> ved å hente
                                                //    byens ID/key:
    gByene.insert(pair <string, By*> (nyBy->hentID(), nyBy));
    nyBy = new By("Lillehammer", 28345, 478.16);  //  Samme som 2x linjer rett
    gByene.insert(pair <string, By*> (nyBy->hentID(), nyBy));  //  ovenfor:

    nyBy = new By("Gjovik", 30560, 672.25);     //  Lager et nytt By-objekt.
    gByene[nyBy->hentID()] = nyBy;              //  Enklere form for 'insert'.
    nyBy = new By("Oslo", 693491, 454.12);      //  Samme som 2x linjer rett
    gByene[nyBy->hentID()] = nyBy;              //    ovenfor.

                                           //  Skriver ALT i <map>:
    for (const auto & val : gByene)        //  Range-based for-løkke.
                                           //  'val' er referanseoverført,
                                           //    men kan IKKE endres (const).
        (val.second)->skrivData();         //  Skriver byens data.
                                           //  ('val.second' er en PEKER!)
    cout << "\n\n";
                                           //  Skriver ALT i <map> BAKLENGS:
    auto it = gByene.rbegin();             //  Iterator til SISTE element.
    while (it != gByene.rend())            //  Ennå ikke nådd det første.
          ((*it++).second)->skrivData();   //  it = peker. Øker denne etterpå.
                                           //  (*it).second er også en peker.
    cout << "\n\n";
                                   //  Skriver DELER av dataene vha. iterator,
                                   //    'for_each(...)' og lambda-funksjon:
    auto it2 = gByene.find("Hamar"); //  Prøver å sette iterator til 'Hamar'.
    if (it2 != gByene.end())  {      //  'Hamar' ble funnet:
                                     //  For hvert element mellom iteratorene:
       for_each(it2, gByene.end(),   //  Skriver fra 'Hamar' og ALLE etterpå:
                                     //     Ved å bruke lambda-funksjon, der
                                     //     'val' blir aktuell iterator:
           [] (const auto & val) { cout << (val.second)->hentID() << '\n'; });
    } else  cout << "\n\tIngen by heter 'Hamar'\n";

   return 0;                         //  Return av "errorkode '0'".
}


/*  <map> blir inneholdende alfabetisk:  Gjovik  Hamar  Lillehammer  Oslo

    1) Først skrives dette (og deres andre data på ett eller annet format)
       ut i ovennevnte rekkefølge (range-based for-løkke)

    2) Deretter skrives de samme 4x ut baklengs (ved bruk av rbegin og rend)

    3) Til slutt skrives:  Hamar  Lillehammer  Oslo   (UTEN sine andre data)
           (da 'for_each' går fra iterator til 'Hamar' og ut resten av <map>)
*/
