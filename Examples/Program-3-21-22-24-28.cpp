/**
 *   Programmet leser enkelttegn, enkeltord og hele setninger,
 *   samt viser hvordan ett eller flere tegn (ofte '\n') kan forkastes.
 *
 *   Poeng:    Lesing av enkelttegn (blanke, '\t' og '\n' ignoreres)
 *             Lesing av enkelttegn (blanke, '\t' og '\n' ignoreres IKKE)
 *             Forkasting av neste tegn ('\n')
 *             Innlesning av ETT ORD (inneholdende kun ikke-blanke tegn)
 *             Innlesning av en HEL setning (inneholdende blanke tegn)
 *
 *   @file     PROGRAM-3-21-22-24-28.CPP
 *   @author   Frode Haug, NTNU
 */

#include <iostream>
using namespace std;

const int STRLEN = 80;            ///<  Max.tekstlengde


/**
 *   Hovedprogrammet:
 */
int main()  {
    char tegn, tegn2;
    char tekst[STRLEN]; 
                                  //  Enkelttegn (' ','\t' og '\n' ignoreres):
    cout << "Skriv ett tegn:  ";
    cin >> tegn;                  //  Jfr:   scanf(" %c", &tegn) - med ' ' !
    cout << "\tInnlest tegn:  -" << tegn << "-\n\n";

                                  //  Enkelttegn (ALT leses!):
    cout << "Skriv ett tegn til:  ";
    tegn = cin.get();             //  = igjenliggende '\n'!
    cin.get(tegn2);               //  = innskrevet tegn
    cin.get();                    //  = avsluttende '\n'

    cout << "'tegn':  -" << tegn << "- 'tegn2:  -" << tegn2 << "-\n\n";
                                  //  Jfr:    scanf("%c", &tegn) - UTEN ' ' !
                                  //      og  getchar() 

    cout << "Skriv enda ett tegn:  ";
    cin >> tegn;
    cin.ignore();              //  KAN også bruke dette istedet for cin.get()
    cout << "\tInnlest tegn:  -" << tegn << "-\n\n";

//  Mer generelt:  Forkaster max N tegn, om ikke '\n' kommer før det:
//       cin.ignore(N, '\n');      


// MEN:  I vår kode vil det primært bli brukt kun  cin.ignore() / cin.get()
//       for å forkaste det neste tegnet, som ofte er en igjenliggende '\n'.


    cout << "Skriv ETT ord:  ";
    cin >> tekst;                 //  Jfr.  scanf("%s", tekst)
    cin.ignore();                 //  Forkaster igjenliggende '\n'
    cout << "Ett ord:  -" << tekst << "-\n\n";

    cout << "Skriv en HEL setning (med flere ord):  ";
    cin.getline(tekst, STRLEN);   //  Jfr.  gets(tekst)
                                  //  NB:  '\n' leses også! 
                                  //       Men blir IKKE en del av teksten!
    cout << "Setning:  -" << tekst << "-\n\n";


/*   Oppsummert:
      - cin >> ...       - leser første IKKE-blanke tall, tegn, enkeltord
      - cin.getline(...) - leser setning, inkludert avsluttende '\n'
      - cin.ignore / cin.get() - forkaster neste tegn (igjenliggende '\n')
*/

    return 0;
}