
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
#include <vector>
#include <cctype>   // Toupper
#include "LesData2.h"
using namespace std;

/**
 *  Kamp (med hjemme- og bortenavn med deres respektive skårede mål)
 */
struct Kamp {
    string hjemmeNavn,
           borteNavn;
    int    hjemmeMaal,
           borteMaal;
};

void kampLesData(Kamp & kamp);
void kampSkrivData(const Kamp* kamp);

vector <Kamp*> gKampene;

/**
 *  Hovedprogrammet:
 */
int main() {

    Kamp* nyKamp;

    do {
        nyKamp = new Kamp;
        kampLesData(*nyKamp);
        gKampene.push_back(nyKamp);
    } while (lesChar("\nVil du legge til flere kamper? (J/N)") != 'N');

    system("pause");
    return 0;
}

void kampLesData(Kamp & kamp) {

}

void kampSkrivData(const Kamp* kamp) {

}
