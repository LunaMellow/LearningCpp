/**
 *   Programeksempel nr 3 - Pekere, arrayer (mye repetisjon)
 *                          og memoryallokering (nytt).
 *
 *   Eksemplet repeterer en del stoff om pekere, inkl. relasjon til array,
 *   og viser hvordan memoryallokering foregår i C++.
 *
 *   @file     EKS_03.CPP
 *   @author   Frode Haug, NTNU
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <cstring>                 //  BRUKES AV OSS FOR SISTE GANG !!!!!!!!!!
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *   Person (med navn og alder).
 */
struct Person {
    string  navn;
    int     alder;
};


/**
 *  Hovedprogrammet:
 */
int main()  {

// ********************  PRIMÆRT REPETISJON:  ********************

    int   tall = 312;
    int*  iPeker = nullptr;       //  KAN bruke NULL (eller faktisk 0 (null)),
    char* cPeker = nullptr;       //    men i C++ bruker vi 'nullptr'.
    Person* persPeker = nullptr;

    iPeker = &tall;               //  'iPeker' peker dit 'tall' er/ligger.
                                  //    Dvs. inneholder ADRESSEN til 'tall'.
    cout << "Tall er:     " << tall << '\n'         // Skriver 'tall' og
         << "\tVia peker:  " << *iPeker << "\n\n";  //   VERDIEN til 'iPeker'.

    *iPeker = 41;                 //  VERDIEN til 'ipeker' blir 41.
                                  //  Dvs. 'tall' blir også 41.
    cout << "Tall er:     " << tall << '\n'         // Skriver 'tall' og
         << "\tVia peker:  " << *iPeker << "\n\n";  //   VERDIEN til 'iPeker'.

    if (cPeker)  cout << "'cPeker' peker til noe reelt.";  //  != nullptr ?
    else         cout << "'cPeker' peker til 'nullptr'.";  //  == nullptr !
    cout << "\n\n";


//  PEKERE OG ARRAY:

    int  i;                        //  Løkkevariabel.
    int  tallene[30];              //  Fast array
    int* iPeker2;                  //  Hjelpepeker.

    iPeker = tallene;              //  ARRAYNAVN ER ADRESSEN TIL DENS START.

    for (i = 0; i < 10; i++)
        *(iPeker + i) = 10 + i;    //  Fyller indeks 0-9 med verdiene 10-19:

    for (; i < 20; i++)            //  'i' er nå allerede 10 !!!
        iPeker[i] = 20 + i;        //  Fyller indeks 10-19 med verdiene 30-39:

    iPeker2 = iPeker + 20;         //  'iPeker2' peker på element nr.20.
    for (i = 0; i < 10; i++)
        *iPeker2++ = 50 + i;       //  Fyller indeks 20-29 med verdiene 50-59:

    for (i = 0; i < 30; i++)       //  Skriver hele 'tallene' sitt innhold:
        cout << ' ' << tallene[i];
    cout << "\n\n";


// *************************************************************
// *************************  HITTIL:  *************************
// *************************************************************

    cPeker    = (char*) malloc(100 * sizeof(char));           //  Char-arrray.
    persPeker = (struct Person*) malloc(sizeof(struct Person)); //  Struct.
    free(cPeker);                          //  Frigir de 2x allokerte
    free(persPeker);                       //    memory-områdene.


// *************************************************************
// *********************  ALLTID HERETTER:  *********************
// **                 Glem 'malloc' og 'free' !!!              **
// **    Nå er det KUN 'new' og 'delete' som gjelder !!!!!!    **
// **************************************************************
// *************************************************************

    iPeker    = new int[100];      //  Allokerer memoryplass til
    cPeker    = new char[60];      //    2x arrayer og
    persPeker = new Person;        //    en struct:

    strcpy(cPeker, "Jammen, 'string' skal jo brukes heretter!!");

    cout << "Personnavn:  ";
    getline(cin, persPeker->navn);
    persPeker->alder = lesInt("Alder", 0, 120);

    cout << "\nTeksten er:   " << cPeker;
    cout << "\nPersonen er:  " << persPeker->navn
         << ", " << persPeker->alder << "\n\n";

    delete [] cPeker;              //  Frigir ARRAYEN 'cPeker'.
    delete persPeker;              //  Frigir structen.
    cPeker = nullptr;              //  God vane å ha
    persPeker = nullptr;           //    (om de fortsatt kan/skal brukes).

                          //  KAN også allokere brukerønsket memory-størrelse:
    int lengde = lesInt("Ønsket tekstlengde", 20, 80);
    cPeker = new char[lengde];                  //  Allokerer.

    strcpy(cPeker, "Storhamar & Arsenal");      //  Fyller.
    cout << "Tekst:  " << cPeker << "\n\n";     //  Skriver.

    delete [] cPeker;                           //  Frigir.
    cPeker = nullptr;                           //  Nullstiller.


//  Huske dette også! (ikke brukt engang siden den ble allokert):
    delete [] iPeker;                           //  Frigir arrayen 'iPeker'.
    iPeker = nullptr;                           //  Nullstiller.


//  Og dermed:  Snipp, snapp, snute:
//              Ut med char-array - nå er det string som gjelder !!!

    return 0;
}
