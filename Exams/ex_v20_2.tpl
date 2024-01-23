/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2020, oppgave 2.
 *
 *   Programmet holder orden på ulike husstander, antall personer i hver
 *   og antall karantenedager disse personene har ifm. en epedemi/pandemi.
 *
 *   Programmet: 
 *      - inneholder EN <list> med pekere til 'Husstand'-objekter.
 *        Det KAN forekomme duplikate ID'er ('dagSlutt') i listen, 
 *        men INGEN 'Husstand' skal ha kontaktperson med samme navn.
 *      - skriver at ALLE data om ALLE husstander på skjermen
 *      - lar brukeren legge inn EN ny husstand (med alle sine data)
 *      - lar brukeren endre karantenetiden for EN husstand 
 *      - lar brukeren slette (hele) husstanden for en NAVNGITT person
 *      - skriver statistikk for/oversikt over alle husstandene/karantenene
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V20_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <list>                    //  list
#include <algorithm>               //  Du får sikkert bruk for noen av disse.
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int MINKARANTENE =  5;       ///<  Min. antall karantenedager.
const int MAXKARANTENE = 21;       ///<  Max. antall karantenedager.
const int MAXIHUSSTAND = 10;       ///<  Max. antall personer i EN husstand.


/**
 *  Husstand (med hvilke absolutt dagnummer i året karantenen er slutt 
 *       (= ID, listen er sortert på dette), antall dager i karantene, antall
 *       personer i husstanden, mobilnummer/navn/adresse til kontaktpersonen).
 */
class Husstand  {
  private:
    int    dagSlutt,               //  = ID – er sortert på dette.
           antallDager,
           antallPersoner,
           mobilNr;
    string navn,
           adresse;

  public:
    Husstand()  { dagSlutt = antallDager = antallPersoner = mobilNr = 0; }
    Husstand(ifstream & inn);                                   //  Oppgave 2G
    void   endreData();                                         //  Oppgave 2C
    int    hentAntall() const  {  return antallPersoner;  }
    int    hentDager()  const  {  return antallDager;     }
    int    hentID()     const  {  return dagSlutt;        }
    string hentNavn()   const  {  return navn;            }
    void   lesData();                                           //  Oppgave 2B
    void   skrivData() const;                                   //  Oppgave 2A
    void   skrivTilFil(ofstream & ut) const;                    //  Oppgave 2D
};


void endreHusstand();                 //  Oppgave 2C
void fjernHusstander();               //  Oppgave 2D
void lesFraFil();                     //  Oppgave 2G
void nyHusstand();                    //  Oppgave 2B
void skrivAlleHusstander();           //  Oppgave 2A
void skrivMeny();
void slettPersonsHusstand();          //  Oppgave 2F
void statistikk();                    //  Oppgave 2E


int  gDagnummerIAret;                 ///<  Absolutt dagnummer i året (1-344).
                                      //      (344 + MAXKARANTENE = 365)
list <Husstand*> gHusstander;         ///<  ALLE husstandene i karantene.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesFraFil();                                     //  Oppgave 2G

    fjernHusstander();                               //  Oppgave 2D

    cout << "\nI dag er det den " << gDagnummerIAret << ".dagen i året.\n\n";

    skrivMeny();
    valg = lesChar("\n\nKommando");

    while (valg != 'Q') {
        switch (valg) {
          case 'A': skrivAlleHusstander();   break;  //  Oppgave 2A
          case 'N': nyHusstand();            break;  //  Oppgave 2B
          case 'E': endreHusstand();         break;  //  Oppgave 2C
          case 'S': statistikk();            break;  //  Oppgave 2E
          case 'P': slettPersonsHusstand();  break;  //  Oppgave 2F
          default:  skrivMeny();             break;
        }
        valg = lesChar("\n\nKommando");
    }

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 */
Husstand::Husstand(ifstream & inn)  {

    //   LAG INNMATEN
}

 
/**
 *  Oppgave 2C - Endrer karantenetiden for hele husstanden.
 */
void Husstand::endreData()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Leser inn ALLE egne data fra tastaturet. 
 */
void Husstand::lesData()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void Husstand::skrivData() const  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Husstand::skrivTilFil(ofstream & ut) const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2C - Endrer (om mulig) en nummerangitt husstand 
 *               sine antall karantenedager.
 */
void endreHusstand()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Fjerner ALLE husstander hvis karantene utgår I DAG.
 */
void fjernHusstander()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2G - Leser ALLE husstandene i karantene inn fra fil.
 */
void lesFraFil()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Legger inn en ny husstand i karantene.
 */
void nyHusstand()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2A - Går gjennom og skriver HELE 'gHusstander' sitt innhold.
 */
void skrivAlleHusstander()  {

    //   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "   A  - skriv Alle husstander\n"
         << "   N  - Ny husstand i karantene\n"
         << "   E  - Endre karantenedagene for en husstand\n"
         << "   S  - Statistikk om alle husstander i karantene\n"
         << "   P  - slett en navngitt Persons husstand\n"
         << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2F - Sletter (om mulig) en navngitt kontaktpersons sin husstand.
 */
void slettPersonsHusstand()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver statistikk over:
 *                1) Antall husstander ute av karantene om X (1-21) dager
 *                2) Antall personer/husstander med Y (1-21) dagers karantene.
 */
void statistikk()  {

    //   LAG INNMATEN
}