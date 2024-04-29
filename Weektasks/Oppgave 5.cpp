
/**     Lecturedata
 *
 *      Program description:
 *          - Go through lecture structs
 *          - Read in the data
 *          - Write out the data
 *
 *      @file Oppgave 5.cpp
 *      @date 23-Jan-24
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

// Includes
#include <iostream>
#include "LesData2.h"

// Namespace
using namespace std;

// Const Declarations
const int STRLEN = 40;               ///< Max.tekstlengde.
const int MAXFORELESNINGER = 1;     ///< Max.antall forelesninger.

// Struct Declarations
struct Forelesning {
    char emne[STRLEN/2],
            foreleser[STRLEN],
            sted[STRLEN/2];
    int timeStart, minuttStart,
            timeSlutt, minuttSlutt;
};

void forelesningLesData(Forelesning* f);
void forelesningSkrivData(const Forelesning* f);

/**
 *      Main Program starts here
 */
int main() {

    Forelesning forelesninger[MAXFORELESNINGER];

    for (int i = 0; i < MAXFORELESNINGER; i++) {
        cout << "\nLeser inn data om forelesning nr. " << i + 1 << "\n";
        forelesningLesData(&forelesninger[i]);
    }
    for (int i = 0; i < MAXFORELESNINGER; i++) {
        cout << "\nData om forelesning nr. " << i + 1 << "\n";
        forelesningSkrivData(&forelesninger[i]);
    }

    return 0;
}

/**
 *  @brief      Funksjon som leser inn data til en Forelesnings struct
 *
 *  @param f    - Peker til forelesningsstruct
 */
void forelesningLesData(Forelesning* f) {

    cout << "\tEmnenavn: ";     cin.getline(f->emne, STRLEN/2);
    cout << "\tForeleser: ";    cin.getline(f->foreleser, STRLEN);
    cout << "\tSted: ";         cin.getline(f->sted, STRLEN/2);

    cout << "\t"; f->timeStart    = lesInt("Time Start", 8, 18);
    cout << "\t"; f->minuttStart  = lesInt("Minutt Start", 0, 59);
    cout << "\t"; f->timeSlutt    = lesInt("Time Slutt", 8, 18);
    cout << "\t"; f->minuttSlutt  = lesInt("Minutt Slutt", 0, 59);
}

/**
 *  @brief      Funksjon som skriver ut data om en Forelesnings struct
 *
 *  @param f    - Peker til forelesningsstruct
 */
void forelesningSkrivData(const Forelesning* f) {
    cout << "\tEmnenavn: "  << f->emne      << "\n"
         << "\tForeleser: " << f->foreleser << "\n"
         << "\tSted: "      << f->sted      << "\n";

    cout << "\n\t" << ((f->timeStart < 10) ? "0" : "") << f->timeStart << " - "
         << ((f->timeSlutt < 10) ? "0" : "") << f->timeSlutt << "\n"

         << "\t" << ((f->minuttStart < 10) ? "0" : "") << f->minuttStart << " - "
         << ((f->minuttSlutt < 10) ? "0" : "") << f->minuttSlutt << "\n";
}