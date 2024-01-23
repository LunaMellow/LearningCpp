/**
 *   Løsningsforslag kontinuasjonseksamen i OOProg (i C++), 
 *   august 2020, oppgave 1C.
 *
 *   @file     EX_S20_1C.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


/**
 *  A (kun med EN int, parameterfylt constructor og utskriftsfunksjon).
 */
class A {
  private:
     int tall;
  public:
      A(int t)          {  tall = t;  }
      void skrivData()  {  cout << ' ' << tall;  }
};


/**
 *  Flytter ALLE elementene (pekerne) FRA en <list> og over TIL en <vector>.
 *
 *  @param   liste   -  listen med pekere som skal tømmes
 *  @param   vektor  -  blir inneholdende alle elementene/pekerne fra listen
 *                   MÅ bruke '&', da begge ORIGINALENE skal oppdateres 
 */
void flyttOver(list <A*> & liste, vector <A*> & vektor) {

    while (!liste.empty())  {                //  Forstatt elementer igjen: 
          vektor.push_back(liste.front());   //  Legger inn i vektoren en kopi 
                                             //    av PEKEREN til 1.elementet.
          liste.pop_front();                 //  Sletter 1.PEKEREN fra listen.
    }                        // Kan IKKE gjøres i EN operasjon, da 'pop_front'
}                            //   IKKE returnerer noe (her: en peker).


/**
 *  Hovedprogrammet (ekstra utover oppgaven, som tester oppgavens funksjon).
 */
int main() {
    list   <A*> listen;
    vector <A*> vektoren;

    listen.push_back(new A(312));  listen.push_back(new A(304));
    listen.push_back(new A(41));   listen.push_back(new A(29));
    listen.push_front(new A(22));  listen.push_front(new A(17));
    listen.push_front(new A(7));   listen.push_front(new A(6));

    cout << "\nFør:   " << listen.size() << ",  " << vektoren.size();
    cout << "\nInnhold 'listen':  ";
    for_each(listen.begin(), listen.end(),
             [] (const auto & val)  {  val->skrivData();  } );

    flyttOver(listen, vektoren);

    cout << "\n\nEtter: " << listen.size() << ",  " << vektoren.size();
    cout << "\nInnhold 'vektoren':  ";
    for_each(vektoren.begin(), vektoren.end(),
             [] (const auto & val)  {  val->skrivData();  } );

    cout << "\n\n";
    return 0;
}