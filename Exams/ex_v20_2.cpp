/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2020, oppgave 2.
 *
 *   Programmet holder orden på ulike husstander, antall personer i hver
 *   og antall karantenedager disse personene har ifm. en epedemi/pandemi.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Husstand'-objekter.
 *        Det KAN forekomme duplikate ID'er ('dagSlutt') i listen,
 *        men INGEN 'Husstand' skal ha kontaktperson med samme navn.
 *      - skriver ALLE data om ALLE husstander ut på skjermen
 *      - lar brukeren legge inn EN ny husstand (med alle sine data)
 *      - lar brukeren endre karantenetiden for EN husstand
 *      - lar brukeren slette (hele) husstanden for en NAVNGITT person
 *      - skriver statistikk for/oversikt over alle husstandene/karantenene
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V20_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <list>                    //  list
#include <algorithm>               //  for_each, count_if, find_if
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
void skrivTilFil();                   //  EXTRA
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

    skrivTilFil();                                   //  EXTRA

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
    inn >> dagSlutt >> antallDager >> antallPersoner >> mobilNr;   //  4x int.
    inn.ignore();                                   //  Forkaster '\n'.
    getline(inn, navn);    getline(inn, adresse);   //  Leser navn og adresse.
}


/**
 *  Oppgave 2C - Endrer karantenetiden for hele husstanden.
 *
 *  @see   skrivData()
 */
void Husstand::endreData()  {
    int dagStart    = dagSlutt - antallDager,     //  Beregner karantenestart.
        dagerHittil = gDagnummerIAret - dagStart; //  Karantenedager hittil.

    cout << '\t';  skrivData();                   //  Skriver nåværende data.

    cout << "\n\tHusstanden har vært i karantene i "       //  Skriver diverse
         << dagerHittil << " dager hittil (siden dag nr."  //   karantenedata:
         << dagStart << ") og har egentlig "
         << dagSlutt - gDagnummerIAret << " dager igjen.\n\n";
                                              //  Leser og regner ut ny
    dagSlutt = gDagnummerIAret                //    karanteneslutt:
           + lesInt("\tNytt antall dager igjen", 1, MAXKARANTENE-dagerHittil);
    antallDager = dagSlutt - dagStart;        //  Beregner nye karantenedager.
                                              //  Skriver nye data:
    cout << "\n\tNye karantenedata er:\n\t  ";  skrivData();
}


/**
 *  Oppgave 2B - Leser inn ALLE egne data fra tastaturet.
 */
void Husstand::lesData()  {
    antallDager    = lesInt("\tDager i karantene    ",
                               MINKARANTENE, MAXKARANTENE);
    dagSlutt       = gDagnummerIAret + antallDager;    //  Beregner slutt/ID.
    antallPersoner = lesInt("\tPersoner i husstanden", 1, MAXIHUSSTAND);
    cout << "\tNavn kontaktperson:      ";  getline(cin, navn);
    mobilNr        = lesInt("\tMobilnummer          ", 10000000, 99999999);
    cout << "\tAdresse (gate og sted):  ";  getline(cin, adresse);
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void Husstand::skrivData() const  {
    cout << dagSlutt << ".dagen har " << antallPersoner
         << " person(er) hatt karantene i " << antallDager << " dager.\n\t\t"
         << navn << ",   tlf: " << mobilNr << "\n\t\t" << adresse << '\n';
}


/**
 *  Oppgave 2D - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void Husstand::skrivTilFil(ofstream & ut) const  {
    ut << dagSlutt << ' ' << antallDager << ' ' << antallPersoner
       << ' ' << mobilNr << '\n' << navn << '\n' << adresse << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2C - Endrer (om mulig) en nummerangitt husstand
 *               sine antall karantenedager.
 *
 *  @see  Husstand::endreData()
 */
void endreHusstand()  {
    if (!gHusstander.empty()) {             //  Husstander finnes:
       int i = 1,                           //  Teller for nummeret i listen.
           nr = lesInt("\tEndre karantene for husstand nr (0=ingen/angre)",
                                 0, gHusstander.size());
       if (nr > 0) {                        //  0 (null) er IKKE skrevet:
           auto it = gHusstander.begin();   //  Initierer til listestart.

           while (i++ < nr) it++;           //  Blar frem til nummer 'nr'.

           (*it)->endreData();              //  Endrer dens karantenedager.
                                            //  Huske å sortere igjen:
           gHusstander.sort( [] (const Husstand* h1, const Husstand* h2)
                                {  return (h1->hentID() < h2->hentID());  });
       } else                               //  0 (null) ble skrevet/valgt:
         cout << "\n\tOK - ingen husstand endres karantenetid.\n";
    } else                                  //  Tomt for husstander:
      cout << "\n\tUmulig å endre noen, da tomt for husstander!\n";
}


/**
 *  Oppgave 2D - Fjerner ALLE husstander hvis karantene utgår I DAG.
 *
 *  @see   Husstand::hentID()
 *  @see   Husstand::skrivTilFil(...)
 */
void fjernHusstander()  {                       // APPENDER BAKERST på filen:
    ofstream utfil("EX_V20_KARANTENEFERDIG.DTA", ios::app);
    int antallH = 0;                            //  Antall husstander.

    auto it = gHusstander.begin();              //  Initierer til listestart.
                                                //  Sålenge ikke tomt, og
                                                //    matcher dagens nummer:
    while (it != gHusstander.end()  &&  (*it)->hentID() == gDagnummerIAret) {
        antallH++;                              //  Antall-ut-av-karantene++
        (*it)->skrivTilFil(utfil);              //  Skriver husstand til fil.
        delete *it;                             //  SLETTER 1.HUSSTANDEN !
        it++;                                   //  Hopper til neste i listen!
        gHusstander.pop_front();                //  Sletter 1.PEKEREN !
    }

//  Alternativt ved å bruke 'gHusstander.front()':
//       MÅ da huske at om listen skulle bli tom, så er 'front()'
//       udefinert (ukjent handling/oppførsel). Derfor er while-løkka slik.
//
//    Husstand* hs;                           //  Peker til FØRSTE husstanden.
//                                            //  Ikke tomt, kan da peke til
//                                            //    den første, og finne ut
//                                            //    om har ID lik aktuell dag:
//    while (!gHusstander.empty()  &&  (hs = gHusstander.front())
//                                 &&  hs->hentID() == gDagnummerIAret) {
//        antallH++;                          //  Antall-ut-av-karantene økes
//        hs->skrivTilFil(utfil);             //  Skriver husstand til fil.
//        delete hs;                          //  Sletter selve husstanden.
//        gHusstander.pop_front();            //  Sletter 1.PEKEREN !
//    }

//  **************************************************************************
//  **  NB:  Kan IKKE bare enkelt bruke 'gHusstander.remove_if(...)'.       **
//  **     Da også skal skrive til fil, og slette SELVE husstanden, men     **
//  **     FØR dette skal det sjekkes for dens ID vs. 'gDagnummerIAret' og  **
//  **     det skal også returneres om selve PEKEREN i listen skal slettes/ **
//  **     fjernes. Hvilket, i denne rekkefølgen, blir VELDIG tuklete.      **
//  **************************************************************************

    utfil.close();                              //  Lukker filen manuelt.

    if (antallH)                                //  Noen er fjernet:
       cout << '\n' << antallH << " husstand(er) er i dag ute av karantene"
            << ", og er skrevet bakerst på 'EX_V20_KARANTENEFERDIG.DTA'.\n\n";

}


/**
 *  Oppgave 2G - Leser ALLE husstandene i karantene inn fra fil.
 *
 *  @see   Husstand::Husstand(...)
 *  @see   Husstand::hentID()
 */
void lesFraFil()  {
    ifstream innfil("EX_V20_HUSSTANDER.DTA");
    int antallHusstander;                     // Antall husstander på filen.

    if (innfil) {                             //  Filen finnes:
        cout << "\n\n\tLeser fra filen 'EX_V20_HUSSTANDER.DTA'......\n\n";
                                              //  Leser global/lokal variabel:
        innfil >> gDagnummerIAret >> antallHusstander;   innfil.ignore();
                                              //  Leser ALLE husstandene:
        for (int i = 1; i <= antallHusstander; i++)
            gHusstander.push_back(new Husstand(innfil)); // Ny legges bakerst.
                                              //  Sorterer på ID/'dagSlutt':
        gHusstander.sort( [] (const Husstand* h1, const Husstand* h2)
                             {  return (h1->hentID() < h2->hentID());  });

        innfil.close();                       //  Lukker filen manuelt.
    } else                                    //  Filen finnes IKKE:
        cout << "\n\n\tFant ikke filen 'EX_V20_HUSSTANDER.DTA'!\n\n";
}


/**
 *  Oppgave 2B - Legger inn en ny husstand i karantene.
 *
 *  @see   Husstand::lesData()
 *  @see   Husstand::hentID()
 */
void nyHusstand()  {
    Husstand* nyHusstand = new Husstand;        //  Oppretter en ny husstand.

    nyHusstand->lesData();                      //  Leser selv inn sine data.

    gHusstander.push_back(nyHusstand);          //  Legger inn bakerst.
                                                //  Sorterer på ID/'dagSlutt':
    gHusstander.sort( [] (const Husstand* h1, const Husstand* h2)
                         {  return (h1->hentID() < h2->hentID());  });
}


/**
 *  Oppgave 2A - Går gjennom og skriver HELE 'gHusstander' sitt innhold.
 *
 *  @see  Husstander::skrivData()
 */
void skrivAlleHusstander()  {
  int nr = 0;                               //  'nr' er nummeret i listen.
  cout << "\n\tI dag er det den " << gDagnummerIAret << ".dagen i året.\n\n";

  for (const auto & val : gHusstander) {    //  Går gjennom ALLE husstandene:
      cout << '\t' << ++nr << ":  ";        //  Skriver listenummeret/'indeks'
      val->skrivData();                     //    og ALLE dataene:
  }

//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//     for_each(gHusstander.begin(), gHusstander.end(),
//             [&nr] (const auto & val)
//                 {  cout << '\t' << ++nr << ":  ";  val->skrivData();  }  );

  cout << "\n\tAntall husstander: " << gHusstander.size() << '\n';
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
 *  EXTRA - Skriver ALLE husstandene i karantene ut til fil.
 *
 *  @see   Husstand::skrivTilFil(...)
 */
void skrivTilFil()  {
    ofstream utfil("EX_V20_HUSSTANDER.DT2");

    cout << "\n\tSkriver alle husstander i karantene til "
         << "'EX_V20_HUSSTANDER.DT2' .....\n";
                                              //  Skriver global variabel og
                                              //    antallet i listen:
                                              //  HUSKE Å ØKE TIL NESTE DAG!
    utfil << ++gDagnummerIAret << '\n' << gHusstander.size() << '\n';

    for (const auto & val : gHusstander)      //  Hver husstand skriver selv:
        val->skrivTilFil(utfil);

    utfil.close();                            //  Lukker filen manuelt.
}


/**
 *  Oppgave 2F - Sletter (om mulig) en navngitt kontaktpersons sin husstand.
 *
 *  @see   Husstand::hentNavn()
 *  @see   Husstand::skrivData()
 */
void slettPersonsHusstand()  {
    string navn;                                 //  Aktuell kontaktperson.
    if (!gHusstander.empty()) {                  //  Husstander finnes:
        cout << "\tNavn på kontakt hvis husstand skal slettes/fjernes:  ";
        getline(cin, navn);                      //  Finner husstanden?
        auto it = find_if(gHusstander.begin(), gHusstander.end(),
                          [navn] (const auto & val)
                                 {  return (val->hentNavn() == navn); } );
        if (it != gHusstander.end()) {           //  Funnet:
            cout << "\n\tSletter husstanden:\n\t";
            (*it)->skrivData();                  //  Skriver dens data.
           delete *it;                           //  SLETTER HUSSTANDEN !
           gHusstander.erase(it);                //  Sletter PEKEREN til den !
        } else
          cout << "\n\tIngen kontakt for husstand med dette navnet!\n";
    } else                                           //  Tomt for husstander:
      cout << "\n\tUmulig å slette noen navngitt, da tomt for husstander!\n";
}


/**
 *  Oppgave 2E - Skriver statistikk over:
 *                1) Antall husstander ute av karantene om X (1-21) dager
 *                2) Antall personer/husstander med Y (1-21) dagers karantene.
 *
 *  @see   Husstand::hentID()
 *  @see   Husstand::hentDager()
 *  @see   Husstand::hentAntall()
 */
void statistikk()  {
    int antallH = 0,                       //  Antall husstander.
        antallP = 0,                       //  Antall personer.
        dagNr = 0;                         //  Dagnummer for karanteneslutt.
    cout << "\n\tAntall husstander ute av karantene om X dager:\n";
    for (int i = 1; i <= MAXKARANTENE; i++) { //  Fremtidige karanteneslutter:
        dagNr = gDagnummerIAret + i;       //  Beregner aktuell sluttdato.
                                           //  Antall i listen med denne dato:
        antallH = count_if(gHusstander.begin(), gHusstander.end(),
                           [dagNr] (const auto & val)
                                   { return (val->hentID() == dagNr); } );
        if (antallH)                       //  'antallH' > 0:
            cout << "\t\t" << i << " (dag nr." << dagNr << "):  "
                 << antallH << '\n';
    }                                      //  MÅ faktisk starte på '1', da en
                                           //    helt nyinnlagt, KAN ha fått
                                           //    endret til bare +1 dag:
    cout << "\n\tAntall personer/husstander med Y dagers karantene:\n";
    for (int i = 1; i <= MAXKARANTENE; i++) {
        antallH = antallP = 0;             //  MÅ huske å nullstille disse 2x!
                                           //  Teller opp antall husstander og
                                           //    personer som har 'i'
                                           //    karantenedager igjen:
        for_each(gHusstander.begin(), gHusstander.end(),
                 [i, &antallH, &antallP] (const auto & val)
                     { if (val->hentDager() == i)
                          { antallH++;  antallP += val->hentAntall(); } } );
        if (antallH)                       //  'antallH' > 0:
           cout << "\t\t" << i << " dagers karantene:  " << antallP
                << " person(er) i " << antallH << " husstand(er).\n";
    }
}
