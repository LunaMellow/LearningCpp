/**
 *   Løsningsforslag til kontinuasjonseksamen i OOProg, aug 2021, oppgave 1C.
 *
 *   @file     EX_S21_1C.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
using namespace std;


/**
 *  Hovedprogrammet:
 */
int main()  {                     //  Hovedprogram med return av 'int'.
   int i, nr;                     //   Løkkevariabel og indeks.

   string text = "mor";           //  Initialiserer til teksten "mor".
   string tekst(10, '-');         //  Initialiserer til 10 stk '-'.
                                  //  Skriver REELL lengde ('length' og
   cout << tekst.length() << ' ' << tekst.size()  //  'size' er det samme), og
        << ' ' << tekst.capacity() << '\n';       //  nåværende avsatte plass.
                                  //  De to første endrer brukeren,
                                  //    det siste justeres automatisk.

   tekst += text + "far" + '!';   //  Legger til/skjøter på med tekster/tegn.

   cout << tekst[2] << tekst[4]   //  Skriver ulike enkelttegn, både vha.'[]'
        << tekst.at(12) << tekst.at(15) << '\n';  //  og den mer sikre 'at()'.

   text = tekst.substr(10, 6);    //  'text' blir en deltekst av 'tekst'.

   tekst.erase(0, 10);            //  Fjerner de 10x første tegnene i 'tekst'.

   tekst.insert(3, text);         //  Smetter inn 'text' fra posisjon nr.3

   tekst.append(3, '.');          //  Legger til "..." bakerst i 'tekst'.

   nr = tekst.find(text);         //  Finner (om mulig) posisjonen som 'text'
                                  //    har/starter på inni 'tekst'.
                                  //    Returnerer -1 om ikke funnet.

   if (text <= tekst.substr(3, 6))  // 'text' er lexiografisk mindre eller lik
      cout << "Ja\n";               //    en viss sub-/deltekst av 'tekst'.

                        cout << "\nNr:  " << nr << "\nText:  -" << text << '-'
                             << "\nTekst:  -" << tekst << "-\n";

   for (i = 1;  i < 22;  i+=2)         // Smetter inn ' ' (blank) på annenhver
      tekst.insert(i, " ");            //   plass mellom ALLE bokstavene.

   while ((nr = tekst.find(' ')) >= 0) //  Erstatter ALLE ' ' med '_':
        tekst.replace(nr, 1, "_");

   nr = tekst.find_first_not_of("mor_"); // Finner (om mulig) posisjonen
                                         //   for første tegn som IKKE
                                         //   er 'm', 'o', 'r' eller '_'.
                                         //   Returnerer -1 om ikke funnet.
                        cout << "\nNr:  " << nr << "\nText:  -" << text << '-'
                             << "\nTekst:  -" << tekst << "-\n";

   return 0;                         //  Return av "errorkode '0'".
}


