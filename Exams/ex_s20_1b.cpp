/**
 *   Løsningsforslag kontinuasjonseksamen i OOProg (i C++), 
 *   august 2020, oppgave 1B.
 *
 *   @file     EX_S20_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
using namespace std;


/**
 *  Elementene med partalls indeks blir lik det forrige (oddetalls) elementet.
 *
 *  @param   v  -  oppdatert vector, MÅ bruke '&' for å oppdatere ORIGINALEN
 */
void dupliserAnnenhvertElement(vector <int> & v)  {
                                 //  Går gjennom KUN ALLE partalls-indeksene:
    for (unsigned int i = 2;  i < v.size();  i += 2)
        v[i] = v[i-1];           //  Elementet blir lik det forrige.
}


const int  MAX = 20;           ///<    Antall int'er i 'tall'.


/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    vector <int> tall;

    for (int i = 0; i < MAX; i++)
        tall.push_back(i*2);

    cout << "\n\n'tall' før:   ";
    for (int i = 0; i < MAX; i++)
        cout << ' ' << tall[i];

    dupliserAnnenhvertElement(tall);

    cout << "\n\n'tall' etter: ";
    for (int i = 0; i < MAX; i++)
        cout << ' ' << tall[i];

    cout << "\n\n";
    return 0;
}