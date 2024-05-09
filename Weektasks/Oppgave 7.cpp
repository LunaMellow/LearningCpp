
/**     Tid og tekst
 *
 *      Programbeskrivelse:
 *          - Les inn tekster og tider
 *          - Skriv ut tekstene og tidene
 *
 *      @file Oppgave 7.cpp
 *      @date 29-Apr-2024
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

#include <iostream>
#include "LesData2.h"
using namespace std;

const int MAXMENGDE = 3;    // Max tillat tekster/klokkeslett

/**
 *  Klokkeslett (med time, minutt, sekund)
 */
struct Klokkeslett {
    int time,
        minutt,
        sekund;
};

void les(string & s);
void les(Klokkeslett & klokkeslett);
void skriv(const Klokkeslett klokkeslett);

/**
 *  Hovedprogrammet:
 */
int main() {

    string          tekster[MAXMENGDE];
    Klokkeslett     tider[MAXMENGDE];

    for (int i = 0; i < MAXMENGDE; i++) {
        cout << "\nLes inn tekst nr. " << i + 1 << "\n";
        les(tekster[i]);
    }

    for (int i = 0; i < MAXMENGDE; i++) {
        cout << "\nLes inn klokkeslett nr. " << i + 1 << "\n";
        les(tider[i]);
    }

    for (int i = 0; i < MAXMENGDE; i++) {
        cout << "\nTekst nr. " << i + 1 << "\n";
        cout << tekster[i] << "\n";
    }

    for (int i = 0; i < MAXMENGDE; i++) {
        cout << "\nKlokkeslett nr. " << i + 1 << "\n";
        skriv(tider[i]);
    }

    return 0;
}

/**
 *  @brief      Funksjon som leser inn tekster
 *  @param s    Referanseoverført string som fylles med tekst
 */
void les(string & s) {
    do {
        getline(cin, s);
    } while (s.length() == 0);
}

/**
 *  @brief              Funksjon som leser inn klokkeslett til en struct
 *  @param klokkeslett  Referanseoverført struct som fylles med tider
 */
void les(Klokkeslett & klokkeslett) {
    klokkeslett.time    = lesInt("Time: ", 0, 23);
    klokkeslett.minutt  = lesInt("Minutt: ", 0, 59);
    klokkeslett.sekund  = lesInt("Sekund: ", 0, 59);
}

/**
 *  @brief              Funksjon som skriver ut dataene til en klokkeslett struct
 *  @param klokkeslett  Structen som leses fra
 */
void skriv(const Klokkeslett klokkeslett) {
    cout << ((klokkeslett.time < 10) ? "0" : "") << klokkeslett.time << ":"
         << ((klokkeslett.minutt < 10) ? "0" : "") << klokkeslett.minutt << ":"
         << ((klokkeslett.sekund < 10) ? "0" : "") << klokkeslett.sekund << "\n";
}
