/**
 *   Løsningsforslag til oppgave nr 7.
 *
 *   Program som leser inn stringer og klokkeslett 
 *   vha. overloadede funksjoner og referanseoverføring.
 *
 *   @file    OPPG_07.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int MAXSTK = 3;              ///<  Max.antall av stringer og structer


/**
 *  Tid (med time, minutt og sekund).
 */
struct Klokkeslett {
    int  time,
         minutt,
         sekund;
};


void les(string & s);
void les(Klokkeslett & klokkeslett);
void skriv(const Klokkeslett klokkeslett);


/**
 *  Hovedprogrammet:
 */
int main ()  {
    int i;                                 //  Løkkevariabel.
    string       tekster[MAXSTK];          //  3x stringer/tekster.
    Klokkeslett  klokkesletter[MAXSTK];    //  3x Tid-structer.

    for (i = 0; i < MAXSTK; i++) {         //  Leser inn 3x tekster:
        cout << "\nTekst nr." << i+1 << ":  ";
        les(tekster[i]);
    }

    for (i = 0; i < MAXSTK; i++) {         //  Leser inn 3x klokkeslett:
        cout << "\nKlokkeslett nr." << i+1 << ":\n";
        les(klokkesletter[i]);
    }

    cout << "\n\n";
    for (i = 0; i < MAXSTK; i++)           //  Skriver ut 3x tekster:
        cout << "Tekst nr." << i+1 << " er:  " << tekster[i] << '\n';

    cout << "\n\n";
    for (i = 0; i < MAXSTK; i++) {         //  Skriver ut 3x klokkeslett:
        cout << "Klokkeslett nr." << i + 1 << " er:  ";
        skriv(klokkesletter[i]);
        cout << '\n';
    }

    return 0;
}


/**
 *  Leser inn en tekst (som inneholder MINST ETT tegn).
 *
 *  @param  s  - string som fylles med tekst (referanseoverført)
 */
void les(string & s)  {
    do {
       getline(cin, s);            //  Leser en HEL linje med tekst.
    } while (s.length() == 0);     //  KUN '\n' ble gitt/skrevet inn.
}


/**
 *  Leser inn alle data til en Klokkeslett-struct.
 *
 *  @param  klokkeslett  - som fylles med ALLE data (referanseoverført)
 */
void les(Klokkeslett & klokkeslett)  {
    klokkeslett.time   = lesInt("Time  ", 0, 23);
    klokkeslett.minutt = lesInt("Minutt", 0, 59);
    klokkeslett.sekund = lesInt("Sekund", 0, 59);
}


/**
 *  Skriver ut et Klokkeslett med formatet tt:mm:ss.
 *
 *  @param  klokkeslett  - som får skrevet ut ALLE sine data
 */
void skriv(const Klokkeslett klokkeslett)  {  // Legger evt. på startende '0':
 cout << ((klokkeslett.time   < 10) ? "0" : "") << klokkeslett.time   << ':'
      << ((klokkeslett.minutt < 10) ? "0" : "") << klokkeslett.minutt << ':'
      << ((klokkeslett.sekund < 10) ? "0" : "") << klokkeslett.sekund << '\n';
}