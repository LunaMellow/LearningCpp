/**
 *   Løsningsforslag til eksamen i OOProg (i C++), juni 2021, oppgave 3.
 *
 *   @file     EX_V21_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "LesData2.h"
using namespace std;


// EXTRA:
/**
 *  Skriver HELE en listes innhold.
 *
 *  @param   liste - list-container av datatypen 'string'
 */
void skrivListe(const list <string> & liste) {
    for (const auto & val : liste)
        cout << val << "  " ;
    cout << '\n';
}


// 2:
/**
 *  Initierer en liste med 10 UNIKE navn/stringer/tekster (IKKE alfabetisk).
 *
 *  @param   liste - list-container av 'string' (OPPDATERER ORIGINALEN!)
 */
void initierMedNavn(list <string> & nvn)  {
 nvn.push_back("Anette"); nvn.push_back("Simon");    nvn.push_back("Ingrid");
 nvn.push_back("Harald"); nvn.push_back("Kristian");
 nvn.push_front("Tore");  nvn.push_front("Andreas"); nvn.push_front("Marita");
 nvn.push_front("Helene"); nvn.push_front("Sigrid");
}


/**
 *  Hovedprogrammet:
 */
int main()  {
   int kNr = lesInt("To siste sifre i kandidatnummeret", 0, 99); //  |
   bool partall1 = (((kNr / 10) % 2) == 0),                      //  | EXTRA
        partall2 = ((kNr % 2) == 0);                             //  |

   int antall = 0;

// 1:
   list <string> navn;
// (2:)
   initierMedNavn(navn);


// ************************************************************************
// ************   A)  PARTALL (nest siste) - PARTALL (siste)   ************
// ************************************************************************

   if (partall1  &&  partall2)  {

// 3:
      for (const auto & val : navn)
          cout << val << "  ";             cout << '\n';
// 4:
      for_each(navn.begin(), navn.end(),
              [&antall] (const auto & val) {  antall++;  }  );
      cout << "\nAntall i listen:  " << antall << '\n';
// 5:
      cout << "\nFørste verdien/elementet:  " << navn.front() << '\n';
// 6:
      auto it = navn.end();  it--;
      cout << "\nSiste verdien/elementet:  " << *it << '\n';
// 7:
      if (!is_sorted(navn.begin(), navn.end()))
         cout << "\nLista er IKKE sortert!\n";
// 8:
      it = min_element(navn.begin(), navn.end());
      cout << "\nMinste elementet:  " << *it << '\n';
// 9:
      it = navn.end();  it--;  it--;
      navn.erase(it);                cout << "\nSlettet den andre bakfra:  ";
                                     skrivListe(navn);
// 10:
      it = navn.begin();  it++;  it++;
      navn.insert(it, "Charlotte");  cout << "\nSatt inn ny tredje FORFRA:  ";
                                     skrivListe(navn);
// 11:
      it = find_if(navn.begin(), navn.end(),
                   [] (const auto & val)  {  return(val[0] == 'A');  }  );
      cout << "\n1.navn startende på 'A':  " << *it << '\n';
// 12:
      navn.reverse();                cout << "\nReverserer lista:  ";
                                     skrivListe(navn);
// 13:
      navn.sort();                   cout << "\nSortert liste:  ";
                                     skrivListe(navn);
// 14:
      it = upper_bound(navn.begin(), navn.end(), "Ingrid");
                                     cout << "\nFørste navn > 'Ingrid':  "
                                          << *it << '\n';
// 15:
      it = lower_bound(navn.begin(), navn.end(), "Yngve");
      if (it == navn.end())  cout << "\nIngen navn >= 'Yngve'!\n";
   }


// ************************************************************************
// ************   B)  ODDETALL (nest siste) - PARTALL (siste)   ***********
// ************************************************************************

   else if (!partall1  &&  partall2)  {

// 3:
      for_each(navn.begin(), navn.end(),
           [] (const auto & val) {  cout << val << "  ";  }  );  cout << '\n';
// 4:
      for (const auto & val : navn)  antall++;
      cout << "\nAntall i listen:  " << antall << '\n';
// 5:
      auto it = navn.begin();
      cout << "\nFørste verdien/elementet:  " << *it << '\n';
// 6:
      cout << "\nSiste verdien/elementet:  " << navn.back() << '\n';
// 7:
      if (is_sorted(navn.begin(), navn.end()))
         cout << "\nLista er sortert!\n";
// 8:
      it = max_element(navn.begin(), navn.end());
      cout << "\nStørste elementet:  " << *it << '\n';
// 9:
      it = navn.begin();  it++;
      navn.erase(it);                cout << "\nSlettet den andre forfra:  ";
                                     skrivListe(navn);
// 10:
      it = navn.end();  it--;  it--;
      navn.insert(it, "Christian");  cout << "\nSatt inn ny tredje BAKFRA:  ";
                                     skrivListe(navn);
// 11:
      antall = count_if(navn.begin(), navn.end(),
                       [] (const auto & val)  {  return(val[0] == 'A');  }  );
      cout << "\nAntall navn startende på 'A':  " << antall << '\n';
// 12:
      reverse(navn.begin(), navn.end()); cout<< "\nReverserer lista igjen:  ";
                                         skrivListe(navn);
// 13:
      navn.sort();                   cout << "\nSortert liste:  ";
                                     skrivListe(navn);
// 14:
      it = lower_bound(navn.begin(),  navn.end(), "Ingrid");
                                     cout << "\nFørste navn >= 'Ingrid':  "
                                          << *it << '\n';
// 15:
      it = upper_bound(navn.begin(),  navn.end(), "Yngve");
      if (it == navn.end())  cout << "\nIngen navn > 'Yngve'!\n";
   }


// ************************************************************************
// ************   C)  ODDETALL (nest siste) - ODDETALL (siste)   **********
// ************************************************************************

   else if (!partall1  &&  !partall2)  {

// 3:
      for (const auto & val : navn)
          cout << val << "  ";             cout << '\n';
// 4:
      for_each(navn.begin(), navn.end(),
              [&antall] (const auto & val) {  antall++;  }  );
      cout << "\nAntall i listen:  " << antall << '\n';
// 5:
      auto it = navn.begin();
      cout << "\nFørste verdien/elementet:  " << *it << '\n';
// 6:
      cout << "\nSiste verdien/elementet:  " << navn.back() << '\n';
// 7:
      if (!is_sorted(navn.begin(), navn.end()))
         cout << "\nLista er IKKE sortert!\n";
// 8:
      it = min_element(navn.begin(), navn.end());
      cout << "\nMinste elementet:  " << *it << '\n';
// 9:
      it = navn.begin();  it++;
      navn.erase(it);                cout << "\nSlettet den andre forfra:  ";
                                     skrivListe(navn);
// 10:
      it = navn.end();  it--;  it--;
      navn.insert(it, "Christian");  cout << "\nSatt inn ny tredje BAKFRA:  ";
                                     skrivListe(navn);
// 11:
      it = find_if(navn.begin(), navn.end(),
                   [] (const auto & val)  {  return(val[0] == 'A');  }  );
      cout << "\n1.navn startende på 'A':  " << *it << '\n';
// 12:
      navn.reverse();                cout << "\nReverserer lista:  ";
                                     skrivListe(navn);
// 13:
      navn.sort();                   cout << "\nSortert liste:  ";
                                     skrivListe(navn);
// 14:
      it = lower_bound(navn.begin(),  navn.end(), "Ingrid");
                                     cout << "\nFørste navn >= 'Ingrid':  "
                                          << *it << '\n';
// 15:
      it = upper_bound(navn.begin(),  navn.end(), "Yngve");
      if (it == navn.end())  cout << "\nIngen navn > 'Yngve'!\n";
   }


// ************************************************************************
// ************   D)  PARTALL (nest siste) - ODDETALL (siste)   ***********
// ************************************************************************

   else if (partall1  &&  !partall2)  {

// 3:
      for_each(navn.begin(), navn.end(),
           [] (const auto & val) {  cout << val << "  ";  }  );  cout << '\n';
// 4:
      for (const auto & val : navn)  antall++;
      cout << "\nAntall i listen:  " << antall << '\n';
// 5:
      cout << "\nFørste verdien/elementet:  " << navn.front() << '\n';
// 6:
      auto it = navn.end();  it--;
      cout << "\nSiste verdien/elementet:  " << *it << '\n';
// 7:
      if (is_sorted(navn.begin(), navn.end()))
         cout << "\nLista er sortert!\n";
// 8:
      it = max_element(navn.begin(), navn.end());
      cout << "\nStørste elementet:  " << *it << '\n';
// 9:
      it = navn.end();  it--;  it--;
      navn.erase(it);                cout << "\nSlettet den andre bakfra:  ";
                                     skrivListe(navn);
// 10:
      it = navn.begin();  it++;  it++;
      navn.insert(it, "Charlotte");  cout << "\nSatt inn ny tredje FORFRA:  ";
                                     skrivListe(navn);
// 11:
      antall = count_if(navn.begin(), navn.end(),
                       [] (const auto & val)  {  return(val[0] == 'A');  }  );
      cout << "\nAntall navn startende på 'A':  " << antall << '\n';
// 12:
      reverse(navn.begin(), navn.end()); cout<< "\nReverserer lista igjen:  ";
                                         skrivListe(navn);
// 13:
      navn.sort();                   cout << "\nSortert liste:  ";
                                     skrivListe(navn);
// 14:
      it = upper_bound(navn.begin(), navn.end(), "Ingrid");
                                     cout << "\nFørste navn > 'Ingrid':  "
                                          << *it << '\n';
// 15:
      it = lower_bound(navn.begin(), navn.end(), "Yngve");
      if (it == navn.end())  cout << "\nIngen navn >= 'Yngve'!\n";
   }

   return 0;
}
