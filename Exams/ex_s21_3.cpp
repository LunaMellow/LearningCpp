/**
 *   Løsningsforslag til kontinuasjonseksamen i OOProg, aug 2021, oppgave 3.
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


/**
 *  Klassen Node (med kun 'nummer', andre datamedlemmer er her uvesentlig).
 */
class Node  {
  private:
    int nummer;
//  Andre datamedlemmer ..... (uvesentlig hva er i dette programmet)
  public:
    Node(int n)          {  nummer = n;  }
    int  hentID() const  {  return nummer;  }
    void skrivData() const { cout << ' ' << nummer; /* Utskrift andre data */}
    void lesData()  {  /*  Leser inn de andre datamedlemmeme  */  }
    void funkA()    {  cout << " funkA";   /*  + annen kode/innmat  */  }
//  + Flere funksjoner .....
};


// EXTRA:
/**
 *  Skriver HELE en listes innhold.
 *
 *  @param   str - ledeteksten
 *  @param   n   - list-container av datatypen 'Node*'
 */
void skrivListe(const string str, const list <Node*> & n) {
  cout << str << ": ";
  for (const auto & val : n)
      val->skrivData();
  cout << '\n';
}


// 2:
/**
 *  Initierer en liste med objekter med ID'er lik 101-110 (ikke sortert).
 *
 *  @param   n - list-container med Node* (OPPDATERER ORIGINALEN!)
 */
void initier(list <Node*> & n)  {
  Node* nyNode;
  for (int i = 101;  i <= 120;  i++)  {
     nyNode = new Node(i);
     nyNode->lesData();
     if (i % 2 == 0)
        n.push_back(nyNode);
     else
        n.push_front(nyNode);
  }
}


/**
 *  Hovedprogrammet:
 */
int main()  {
   int kNr = lesInt("To siste sifre i kandidatnummeret", 0, 99); //  |
   bool partall1 = (((kNr / 10) % 2) == 0),                      //  | EXTRA
        partall2 = ((kNr % 2) == 0);                             //  |

// 1:
   list <Node*> noder;

// (2:)
   initier(noder);


// ************************************************************************
// ************   A)  PARTALL (nest siste) - PARTALL (siste)   ************
// ************************************************************************

   if (partall1  &&  partall2)  {

// 3:
   for (const auto & val : noder)
       val->skrivData();                                        cout << '\n';

// 4:
   for_each(noder.begin(), noder.end(),
           [] (const auto & val) {  val->funkA();  } );         cout << '\n';

// 5:
   if (noder.size() == 0)
      cout << "Listen er tom.\n";
   else
      cout << "Listen inneholder noder.\n";

// 6:
   cout << "Første noden:  ";  (noder.front())->skrivData();    cout << '\n';

// 7:
   cout << "Siste noden:  ";   (*noder.rbegin())->skrivData();  cout << '\n';

// 8:
   cout << "Antall partall: " << count_if(noder.begin(), noder.end(),
      [] (const Node* val) {  return ((val->hentID() % 2) == 0); } ) << '\n';
                                          skrivListe("Foer         ", noder);
// 9:
   cout << "Første heltallelig delelig med 9 er: ";
   auto it = find_if(noder.begin(), noder.end(), [] (const Node* val)
                     {  return ((val->hentID() % 9) == 0); } );
   (*it)->skrivData();   cout << "   - denne fjernes:\n";

// 10:
   delete *it;
   noder.erase(it);                      skrivListe("Etterpaa     ", noder);

// 11:
   noder.sort([] (const Node* v1, const Node* v2)
                 { return(v1->hentID() < v2->hentID());  } );
                                          skrivListe("Sortert      ", noder);
// 12:
   auto it2 = noder.begin();
   it2++; it2++; it2++; it2++;  it2++;   // evt. istedet:   advance(it2, 5);
  rotate(noder.begin(), it2, noder.end()); skrivListe("Rotert 3x bak", noder);

// Alternativt:
   for (int i = 1;  i <= 5;  i++)  {
     auto it = noder.front();
     noder.pop_front();
     noder.push_back(it);
   }                                      skrivListe("Rotert 3x bak", noder);

// 13:
   for (auto & val : noder)
       delete val;
   noder.clear();                          skrivListe("Slettet", noder);
   }

// ************************************************************************
// ************   B)  ODDETALL (nest siste) - PARTALL (siste)   ***********
// ************************************************************************

   else if (!partall1  &&  partall2)  {

// 3:
   for_each(noder.begin(), noder.end(),
           [] (const auto & val) {  val->skrivData();  } );     cout << '\n';

// 4:
   for (const auto & val : noder)
       val->funkA();                                            cout << '\n';

// 5:
   if (noder.size() > 0)
      cout << "Listen inneholder noder.\n";
   else
      cout << "Listen er tom.\n";

// 6:
   cout << "Første noden:  ";  (noder.front())->skrivData();    cout << '\n';

// 7:
   cout << "Siste noden:  ";   (*noder.rbegin())->skrivData();  cout << '\n';

// 8:
   cout << "Antall oddetall: " << count_if(noder.begin(), noder.end(),
      [] (const Node* val) {  return ((val->hentID() % 2) == 1); } ) << '\n';
                                          skrivListe("Foer         ", noder);
// 9:
   cout << "Første heltallelig delelig med 8 er: ";
   auto it = find_if(noder.begin(), noder.end(), [] (const Node* val)
                     {  return ((val->hentID() % 8) == 0); } );
   (*it)->skrivData();   cout << "   - denne fjernes:\n";

// 10:
   delete *it;
   noder.erase(it);                      skrivListe("Etterpaa     ", noder);

// 11:
   noder.sort([] (const Node* v1, const Node* v2)
                 { return(v1->hentID() < v2->hentID());  } );
                                          skrivListe("Sortert      ", noder);
// 12:
   auto it2 = noder.begin();
   it2++; it2++; it2++; it2++;  it2++;   // evt. istedet:   advance(it2, 5);
  rotate(noder.begin(), it2, noder.end()); skrivListe("Rotert 3x bak", noder);

// Alternativt:
   for (int i = 1;  i <= 5;  i++)  {
     auto it = noder.front();
     noder.pop_front();
     noder.push_back(it);
   }                                      skrivListe("Rotert 3x bak", noder);

// 13:
   for (auto & val : noder)
       delete val;
   noder.clear();                          skrivListe("Slettet", noder);
   }

// ************************************************************************
// ************   C)  ODDETALL (nest siste) - ODDETALL (siste)   **********
// ************************************************************************

   else if (!partall1  &&  !partall2)  {

// 3:
   for (const auto & val : noder)
       val->skrivData();                                        cout << '\n';

// 4:
   for_each(noder.begin(), noder.end(),
           [] (const auto & val) {  val->funkA();  } );         cout << '\n';

// 5:
   if (noder.size() > 0)
      cout << "Listen inneholder noder.\n";
   else
      cout << "Listen er tom.\n";

// 6:
   cout << "Første noden:  ";  (*noder.begin())->skrivData();   cout << '\n';

// 7:
   cout << "Siste noden:  ";   (noder.back())->skrivData();     cout << '\n';

// 8:
   cout << "Antall partall: " << count_if(noder.begin(), noder.end(),
      [] (const Node* val) {  return ((val->hentID() % 2) == 0); } ) << '\n';
                                          skrivListe("Foer         ", noder);
// 9:
   cout << "Første heltallelig delelig med 9 er: ";
   auto it = find_if(noder.begin(), noder.end(), [] (const Node* val)
                     {  return ((val->hentID() % 9) == 0); } );
   (*it)->skrivData();   cout << "   - denne fjernes:\n";

// 10:
   delete *it;
   noder.erase(it);                      skrivListe("Etterpaa     ", noder);

// 11:
   noder.sort([] (const Node* v1, const Node* v2)
                 { return(v1->hentID() < v2->hentID());  } );
                                          skrivListe("Sortert      ", noder);
// 12:
   auto it2 = noder.begin();
   it2++; it2++; it2++; it2++;  it2++;   // evt. istedet:   advance(it2, 5);
  rotate(noder.begin(), it2, noder.end()); skrivListe("Rotert 3x bak", noder);

// Alternativt:
   for (int i = 1;  i <= 5;  i++)  {
     auto it = noder.front();
     noder.pop_front();
     noder.push_back(it);
   }                                      skrivListe("Rotert 3x bak", noder);

// 13:
   for (auto & val : noder)
       delete val;
   noder.clear();                          skrivListe("Slettet", noder);
   }

// ************************************************************************
// ************   D)  PARTALL (nest siste) - ODDETALL (siste)   ***********
// ************************************************************************

   else if (partall1  &&  !partall2)  {

// 3:
   for_each(noder.begin(), noder.end(),
           [] (const auto & val) {  val->skrivData();  } );     cout << '\n';

// 4:
   for (const auto & val : noder)
       val->funkA();                                            cout << '\n';

// 5:
   if (noder.size() == 0)
      cout << "Listen er tom.\n";
   else
      cout << "Listen inneholder noder.\n";

// 6:
   cout << "Første noden:  ";  (*noder.begin())->skrivData();   cout << '\n';

// 7:
   cout << "Siste noden:  ";   (noder.back())->skrivData();     cout << '\n';

// 8:
   cout << "Antall oddetall: " << count_if(noder.begin(), noder.end(),
      [] (const Node* val) {  return ((val->hentID() % 2) == 1); } ) << '\n';
                                          skrivListe("Foer         ", noder);
// 9:
   cout << "Første heltallelig delelig med 8 er: ";
   auto it1 = find_if(noder.begin(), noder.end(), [] (const Node* val)
                     {  return ((val->hentID() % 8) == 0); } );
   (*it1)->skrivData();   cout << "   - denne fjernes:\n";

// 10:
   delete *it1;
   noder.erase(it1);                      skrivListe("Etterpaa     ", noder);

// 11:
   noder.sort([] (const Node* v1, const Node* v2)
                 { return(v1->hentID() < v2->hentID());  } );
                                          skrivListe("Sortert      ", noder);
// 12:
   auto it2 = noder.begin();
   it2++; it2++; it2++; it2++;  it2++;   // evt. istedet:   advance(it2, 5);
  rotate(noder.begin(), it2, noder.end()); skrivListe("Rotert 3x bak", noder);

// Alternativt:
   for (int i = 1;  i <= 5;  i++)  {
     auto it = noder.front();
     noder.pop_front();
     noder.push_back(it);
   }                                      skrivListe("Rotert 3x bak", noder);

// 13:
   for (auto & val : noder)
       delete val;
   noder.clear();                          skrivListe("Slettet", noder);
   }

   return 0;
}
