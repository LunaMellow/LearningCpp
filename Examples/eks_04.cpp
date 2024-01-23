/**
 *   Programeksempel nr 4 - Range-Based for-løkke (variant fra og med C++11).
 *
 *   Eksemplet viser bruken av varianten Range-Based for-løkke
 *   i en del sammenhenger (jfr. 8.5 i læreboka).
 *
 *   @file     EKS_04.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string-klassen
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Hovedprogrammet:
 */
int main()  {
    int i;                         //  Løkkevariabel.

    int  tall[10] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23 };

    cout << "Arrayens innhold 1: ";       //  Hittil:
    for (i = 0; i < 10; i++)
        cout << ' ' << tall[i];
    cout << "\n\n";


    cout << "Arrayens innhold 2: ";       //  Variant (nytt i/med C++11):
                      //  'val' = KOPI av verdien HENTET UT av arrayen 'tall':
    for (int val : tall)                  //  Utskrift:
        cout << ' ' << val;
    cout << "\n\n";

    cout << "Leser inn nye 10 tall/verdier:\n";
    for (int & val : tall)                //  Innlesning (NB: '&'!), jobber
        val = lesInt("\tTall", 0, 100);   //    da med ORIGINALEN (IKKE kopi)!

    cout << "\nArrayens innhold 3: ";
    for (int val : tall)
        cout << ' ' << val;
    cout << "\n\n";


// ***************************************************************************

    string tekst = "Bananer, epler og druer - er helt greit det.";

    cout << "Tekst 1:\n\t";            //  Skriver ett og ett tegn i stringen:
    for (i = 0; i < tekst.length(); i++)
        cout << tekst[i];
    cout << "\n\n";

    cout << "Tekst2:\n\t";
    for (char val : tekst)             //  Samme resultat - men annen metode:
        cout << val;
    cout << "\n\n";


// ***************************************************************************

    string ukedager[] = { "Mandag", "Tirsdag", "Onsdag", "Torsdag",
                          "Fredag", "Lørdag",  "Søndag" };

    cout << "Ukedagene:\n";
    for (string val : ukedager)
        cout << '\t' << val << '\n';
    cout << "\n\n";


// ***************************************************************************
// ALTSÅ:  for ( <type, evt.'auto'>  <val = uthentet verdi>  :  <array> )  {
//                  <Bruker bl.a. 'val'>
//         }
//
//  Vi vil bruke begge disse måtene videre i koden - alt etter situasjonen.
//
// ***************************************************************************

    return 0;
}
