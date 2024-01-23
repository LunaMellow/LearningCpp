/**
 *   Programeksempel nr 2 - Introduserende om STRING-klassen.
 *
 *   Eksemplet introduserer string istedet for char-array som tekst.
 *   Noen av de mest grunnleggende mekanismene brukes/innf�res.
 *
 *   @file     EKS_02.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  STRING-KLASSEN
using namespace std;


//****************************************************************************
//****************************************************************************
//**              NB:    NB:    NB:    NB:    NB:    NB:                    **
//** FOR TEKSTER BRUKES HERETTER PRIM�RT STRING-KLASSEN, OG IKKE CHAR-ARRAY **
//**                                                                        **
//****************************************************************************
//****************************************************************************


/**
 *  Hovedprogrammet:
 */
int main()  {
    char   tekst[] = "Dette er tekst";
    string tekst1  = "Dette er tekst nr.1";   //  Kan definere og initiere
    string tekst2("Dette er tekst nr.2");     //    stringer p� flere
    string tekst3(tekst);                     //    ulike m�ter:
    string tekst4(tekst1);                    //  Og enda flere
    string tekst5(10, '!');                   //    m�ter/muligheter finnes...

                                              //  Utskrift av stringene:
    cout << tekst << '\n' << tekst1 << '\n' << tekst2 << '\n'
         << tekst3 << '\n' << tekst4 << '\n' << tekst5 << "\n\n";

                                              //  Enkel tilordning:
    tekst3 = "Dette er en annen og lengre tekst, og det er problemfritt!";
    tekst4 = tekst5;

    cout << tekst3 << '\n' << tekst4 << "\n\n";

                                     //  Innlesning av ETT ord/sammenhengende
    cout << "Skriv ETT ord:  ";      //     tekst (inneholdende ikke-blanke):
    cin >> tekst2;
    cout << tekst2 << "\n\n";
    cin.ignore();                    //  Forkaster avsluttende '\n':
                                     //  "Sikkert nok":  cin.ignore(200, '\n')

                                     //  Innlesning av lengre tekst
    cout << "Skriv FLERE ord:  ";    //     (inneholdende blanke):
    getline(cin, tekst5);            //  NB - NB - NB:  'cin' inni !!!
    cout << tekst5 << "\n\n";

                                     //  Kan sammenligne tekster:
    if (tekst4 == tekst5)      cout << "'tekst4' er lik 'tekst5'";
    else if (tekst4 < tekst5)  cout << "'tekst4' er mindre enn 'tekst5'";
    else                       cout << "'tekst4' er st�rre enn 'tekst5'";
    cout << "\n\n";                  //  KAN bruke ALLE:  <  <=  >  <=  ==  !=

                                     //  Kan ogs� sammenligne med
                                     //    tekst-konstanter og char-array:
    if (tekst3 == "Storhamar")  cout << "Tekst er lik 'Storhamar'\n\n";
    if (tekst1 != tekst)        cout << "Tekster er ulik\n\n";

                                     //  Skj�te sammen tekster p� ulike m�ter:
    tekst5 = tekst1 + " PLUSS " + tekst2 + " OG ENDA " + tekst4 + 'X';
    cout << tekst5 << "\n\n";

    tekst4 += "........";
    tekst4 += tekst5;
    cout << tekst4 << "\n\n";

                                   //  To m�ter � f� tak i tekstens lengde p�:
    cout << "'tekst5' sin lengde: " << tekst5.size()   << '\n'
         << "'tekst5' sin lengde: " << tekst5.length() << "\n\n";


//  NB:  En 'string' blir (dynamisk) s� lang den bare trenger � v�re !!!
//       Dvs. vi trenger (stort sett) ikke � bekymre oss for dens lengde!


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**  PLUSS MANGE TI-TALLS FUNKSJONER FOR � OPERERE P� TEKSTENS INNHOLD!!   **
//**          (se under linken "Ressurser" og "string-klassen")             **
//**          Mer om 'alt' dette senere/etterhvert/underveis .....          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

    return 0;
}
