/**
 *   Løsningsforslag til oppgave nr 4.
 *
 *   Finner den største/høyeste/seneste av fire Tid-structer.
 *
 *   @file    OPPG_04.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>          //  cout
using namespace std;


/**
 *   Tid (med time, minutt og sekund).
 */
struct Tid {
  int time,
      minutt,
      sekund;
};


Tid storst(const Tid tid1, const Tid tid2);


/**
 *  Hovedprogrammet:
 */
int main ()  {
    Tid tid1 = { 13, 52, 17},       //  Definerer og initierer 4x structer:
        tid2 = {  7, 56, 38},
        tid3 = { 21, 16, 42},
        tid4 = { 19,  2, 49},
        svar;

    svar = storst(tid1, tid2);      //  Finner den største av nr.1 og 2.
    svar = storst(svar, tid3);      //  Er nr.3 enda større/senere?
    svar = storst(svar, tid4);      //  Er nr.4 større/senere enn dette igjen?
                                    //  Skriver den største funnet/beregnet:
    cout << "\nSeneste/største/høyeste tidspunkt er:   " 
         << svar.time << ':' << svar.minutt << ':' << svar.sekund << "\n\n\n";

    return 0;
}


/**
 *  Finner og returnerer den største av to Tid-structer.
 *
 *  @param     tid1  - Den 1.Tid-structen
 *  @param     tid2  - Den 2.Tid-structen
 *  @return    Den structen som er størst (er seneste/høyeste tidspunkt)
 */
Tid storst(const Tid tid1, const Tid tid2) {  //  #sekunder siden midnatt:
    int tot1 = (tid1.time * 3600) + (tid1.minutt * 60) + tid1.sekund,
        tot2 = (tid2.time * 3600) + (tid2.minutt * 60) + tid2.sekund;
    return ((tot1 >= tot2) ? tid1 : tid2);    //  Returnerer største struct.
}