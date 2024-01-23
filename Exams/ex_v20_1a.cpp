/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2020, oppgave 1A.
 *
 *   @file     EX_V20_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
using namespace std;


/**
 *  Returnerer antallet i en string/tekst som er en av to bokstaver.
 *
 *  @param   s   -  teksten det skal letes etter 'c1' og 'c2' i
 *  @param   c1  -  bokstav nr.1 som det skal letes etter i 's'
 *  @param   c2  -  bokstav nr.2 som det skal letes etter i 's'
 *  @return  Totalantallet av 'c1' og 'c2' i 's'
 */
int antallAvToBokstaver(const string s, const char c1, const char c2) {
    int antall = 0;                          //  Viktig at nullstilles!
                                             //  Går gjennom teksten/stringen:
    for (unsigned int i = 0;  i < s.length();  i++)
        if (s[i] == c1 || s[i] == c2)        //  ER en av tegnene:
            antall++;                        //  Teller opp totalantallet.

//  Alternativ ift. for-løkka vha. iterator og <algorithm>:
//    antall  =  count(s.begin(), s.end(), c1));
//    antall +=  count(s.begin(), s.end(), c2));

    return antall;                           //  Returnerer totalantallet.
}


/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    string tekst;
    char tegn1, tegn2;

    cout << "Skriv en tekst: ";
    getline(cin, tekst);
    cout << "To (ikke-blanke) tegn det skal letes etter: ";
    cin >> tegn1 >> tegn2;

    cout << "\n\nTotalt antall av de to tegnene:  " 
         << antallAvToBokstaver(tekst, tegn1, tegn2) << "\n\n";

    return 0;
}