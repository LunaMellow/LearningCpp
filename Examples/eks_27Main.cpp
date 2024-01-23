/**
 *   Programeksempel nr 27 - Større programeksempel.
 *
 *   Eksemplet viser et enkelt og lite multifilsprogram,
 *   der flere filer includer andre filer.
 *   H-filer kan inkludere andre H-filer.
 *   CPP-filer kan inkludere H-filer, MEN ALDRI ANDRE CPP-filer !!!
 *
 *   Programmet:
 *     - inneholder ETT SELVLAGET container-objekt ('Personbase')
 *       med en <vector> av 'Person'-structer inni
 *     - har en 'main' som tilbyr brukeren å legge inn ny personer
 *       i 'Personbase', samt å skrive ut HELE dens innhold
 *
 *   @file     EKS_27MAIN.CPP
 *   @author   Frode Haug, NTNU
 */


// ***************************************************************************
// NB:  Koden i alle disse syv filene EKS_27...... er bevisst stort sett
//      strippet for kommentarer etter Doxygen-standarden. Dette er gjort for
//      lettere å se og lese hovedpoenget med dette multifilsprogrammet.
//      Dessuten er det brukt 'struct' - for å forenkle og forkorte koden.
// ***************************************************************************


#include <iostream>
#include "EKS_27CLASS.H"           //  'Personbase'
#include "EKS_27FUNC.H"            //  Funksjonen 'Ny'
#include "LesData3.h"              //  Verktøykasse for lesing av diverse data
                                   //  NB:  LesData3.h - nr.3 !!!
using namespace std;


Personbase* gPersoner;             ///<  Datastrukturen med ALLE personene.


/**
 *  Hovedprogrammet:
 */
int main() {
    char kommando;

    gPersoner = new Personbase;

    kommando = lesChar("\n\n\nKommando [ N(y), D(isplay), Q(uit) ]");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'N':  ny();                  break;
          case 'D':  gPersoner->display();  break;
        }
        kommando = lesChar("\n\nKommando [ N(y), D(isplay), Q(uit) ]");
    }

    delete gPersoner;

    cout << "\n\n";

    return 0;
}
