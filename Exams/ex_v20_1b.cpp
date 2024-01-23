/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2020, oppgave 1B.
 *
 *   @file     EX_V20_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
using namespace std;


/**
 *  Elementene med oddetalls indeks gangens med 3. Deres totalsum returneres.
 *
 *  @param   v  -  oppdatert vector, MÅ bruke '&' for å oppdatere ORIGINALEN
 *  @return  Summen av alle elementene som har oddetalls indeks
 */
int oppdaterOgSummer(vector <int> & v) {
    int sum = 0;                 //  Viktig at nullstilles!
                                 //  Går gjennom KUN ALLE oddetalls-indeksene:
    for (unsigned int i = 1;  i < v.size();  i += 2) {
        v[i] *= 3;               //  Elementet ganges med 3.
        sum += v[i];             //  Oppsummerer ALLE involverte elementene.
    }

    return sum;                  //  Returnerer totalsummen av elementene.
}


const int  MAX = 20;           ///<    Antall int'er i 'tall'.


/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    vector <int> tall;
    int summen;

    for (int i = 0; i < MAX; i++)
        tall.push_back(i);

    cout << "\n\n'tall' før:   ";
    for (int i = 0; i < MAX; i++)
        cout << ' ' << tall[i];

    summen = oppdaterOgSummer(tall);

    cout << "\n\n'tall' etter: ";
    for (int i = 0; i < MAX; i++)
        cout << ' ' << tall[i];

    cout << "\n\nSummen av oddetall-indeks tallene: " << summen << "\n\n";

    return 0;
}