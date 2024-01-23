/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2020, oppgave 1C.
 *
 *   @file     EX_V20_1C.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


/**
 *  ALLE string'ene i en map med key (int) modbar med 3 erstattes med 's'.
 *
 *  @param   m  -  oppdatert map, MÅ bruke '&' for å oppdatere ORIGINALEN
 *  @param   s  -  substitusjonsteksten
 */

void endreVerdier(map <int, string> & m, const string s) {
    auto it = m.begin();              //  Initierer til map-start.
    while (it != m.end()) {           //  Ennå ikke nådd map'ens slutt:
        if (it->first % 3 == 0)       //  Modbar med '3':
            it->second = s;           //  Tilknyttet tekst erstattes med 's'.
        it++;                         //  Går til neste element i map'en.
    }

//  Vha. 'for_each', iterator og lambda-funksjon:
//  for_each(m.begin(), m.end(), 
//         [s] (auto & val) { if (val.first % 3 == 0) { val.second = s; }  });

}



/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    map <int,  string> verdier;

    verdier[6] = "Corona";   verdier[17] = "Corona";   verdier[21] = "Corona";
    verdier[8] = "Corona";   verdier[34] = "Corona";   verdier[18] = "Corona";
    verdier[7] = "Corona";   verdier[1] = "Corona";    verdier[12] = "Corona";
    verdier[27] = "Inspera"; verdier[22] = "Inspera";  verdier[13] = "Inspera";
    verdier[15] = "Inspera"; verdier[24] = "Inspera";  verdier[29] = "Inspera";

    cout << "\n\n'verdier' før: \n";
    for (const auto & val : verdier)
        cout << '\t' << val.first << ":  " << val.second << '\n';

    endreVerdier(verdier, "Banan");

    cout << "\n'verdier' etter: \n";
    for (const auto & val : verdier)
        cout << '\t' << val.first << ":  " << val.second << '\n';

    cout << "\n\n";
    return 0;
}