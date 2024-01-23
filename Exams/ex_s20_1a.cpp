/**
 *   Løsningsforslag kontinuasjonseksamen i OOProg (i C++), 
 *   august 2020, oppgave 1A.
 *
 *   @file     EX_S20_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <cctype>
#include <string>
using namespace std;


/**
 *  Returnerer antall tegn i en string som er f.o.m et tegn t.o.m. et annet.
 *
 *  @param   s   -  teksten det skal letes etter antall mellom 'c1' og 'c2' i
 *  @param   c1  -  bokstav nr.1 (den minste/første) som angir nedre grense
 *  @param   c1  -  bokstav nr.2 (den største/siste) som angir øvre grense
 *  @return  Totalantallet av bokstaver imellom 'c1' og 'c2' i 's'
 */
int antallImellomToBokstaver(const string s, char c1, char c2) {
    int antall = 0;                    //  Viktig at nullstilles!
    char tegn;                         //  Aktuelt upcaset sammenligningstegn.
                                            
    c1 = toupper(c1);  c2 = toupper(c2);    //  Lager bokstavene om til STORE.
    for (unsigned int i = 0; i < s.length(); i++)  {  //  Traverserer teksten:
        tegn = toupper(s[i]);               //  Aktuell bokstav om til STOR.
        if (tegn > c1  &&  tegn < c2)       //  ER IMELLOM bokstavene:
            antall++;                       //  Teller opp totalantallet.
    }
    return antall;                          //  Returnerer totalantallet.
}


/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    string tekst;
    char tegn1, tegn2;

    cout << "Skriv en tekst: ";
    getline(cin, tekst);
    cout << "To (ikke-blanke) tegn å finne antallet imellom (minste først): ";
    cin >> tegn1 >> tegn2;

    cout << "\n\nTotalt antall tegn alfabetisk imellom disse to tegnene:  " 
         << antallImellomToBokstaver(tekst, tegn1, tegn2) << "\n\n";

    return 0;
}