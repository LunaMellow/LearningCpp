/**
 *   Programeksempel nr 15 - Demo av noen av funksjonene i string-klassen.
 *
 *   Se også:  EKS_02.CPP
 * 
 *   @file     EKS_15.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
using namespace std;


/**
 *  Hovedprogrammet:
 */
int main()  {
//                             1         2         3         4         5       
//                   0123456789012345678901234567890123456789012345678901
    string tekst1 = "3x B'er: Barabaresco, Barolo, Brunello di Montalcino";
    string tekst2 = "Arsenal Chelsea Liverpool ManU ManC Tottenham";
    string tekst3;
    int n;

    cout << '-' << tekst1 << "-\n-" << tekst2 << "-\n-" << tekst3 << "-\n\n";

    tekst3 = tekst2.substr(26, 9);     //  Setter lik subteksten "ManU ManC".
    tekst2.swap(tekst3);               //  Bytter om de to tekstene.
    cout << '-' << tekst2 << "-\n-" << tekst3 << "-\n\n";

    tekst1.append(5, '!');             //  Legger til bakerst 5x '!'.
    tekst3.erase(26, 10);              //  Fjerner subteksten "ManU ManC ".
    cout << '-' << tekst1 << "-\n-" << tekst2 << "-\n-" << tekst3 << "-\n\n";

    tekst3.insert(8, tekst2);          //  Smetter inn "ManU ManC" fra pos 8.
    tekst3.insert(17, 3, ' ');         //  Smetter inn 3x ' ' før "Chelsea".
    cout << '-' << tekst3 << "-\n\n";

    tekst3.replace(8, 11, 3, '.');     //  Erstatter "ManU ManC  " med "...". 
    cout << '-' << tekst3 << "-\n\n";

    tekst3.replace(8, 11, tekst2);     //  Erstatter "... Chelsea"
    cout << '-' << tekst3 << "-\n\n";  //    med "ManU ManC".

    n = tekst3.find(tekst2);           //  Finner tekster i annen tekst:
    cout << "'tekst2' starter i posisjon " << n << " i 'tekst3'\n\n";

    n = tekst1.find("bar");
    cout << "Teksten 'bar' starter i posisjon " << n << " i 'tekst1'\n\n";

    while ((n = tekst1.find(' ')) >= 0)  //  Erstatter ALLE ' ' med '-':
        tekst1[n] = '-';

    cout << '-' << tekst1 << "-\n\n";

    cout << "N:  " << n << "\n\n";   //  n = -1  når ikke flere funn.

    n = tekst1.find_first_of("aeiouy");
    cout << "1.vokal befinner deg i posisjon " << n << " i 'tekst1'\n\n";

    return 0;
}

// ***************************************************************************
// **    NB    NB    NB    NB    NB    NB    NB    NB    NB    NB    NB     **
// **    MANGE flere andre funksjoner og varianter av de ovenfor finnes!    **
// **                Se linken: "Ressurser/mer stoff"                       **
// ***************************************************************************