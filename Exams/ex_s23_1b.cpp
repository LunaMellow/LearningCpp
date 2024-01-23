/**
 *   Løsning til kontinuasjonseksamen i OOProg (i C++), august 2023, oppgave 1B.
 *
 *   @file     EX_S23_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


int main() {
    vector <string> tekst1 { "Eple", "Banan", "Appelsin", "Sitron", "Mango" };
    vector <string> tekst2;

    tekst2.push_back("Gulrot");  tekst2.push_back("Brokkoli");
    tekst2.push_back("Salat");   tekst2.push_back("Potet");
    sort(tekst2.begin(), tekst2.end());

    for (const auto & val : tekst2) cout << val << "  ";         cout << '\n';

    auto it = tekst1.begin();  it++;  it++;
    auto it2 = it;
    for (  ;  it != tekst1.end();  it++)  cout << *it << "  ";   cout << '\n';

    it2++;
    tekst1.erase(it2, tekst1.end());
    tekst1.pop_back();    tekst1.push_back("Kiwi");
    for (const auto & val : tekst1) cout << val << "  ";         cout << '\n';


    list <char> tegn { 'A', 'R', 'S', 'E', 'N', 'A', 'L' };
    tegn.sort();   tegn.reverse();
    for (auto it3 = tegn.rbegin();  it3 != tegn.rend();  it3++)
        cout << *it3 << ' ';                                     cout << '\n';

    tegn.reverse();  tegn.remove('A');
    auto it4 = tegn.begin();  it4++;  it4++;
    tegn.erase(it4);
    cout << tegn.front() << ' ' << tegn.back() << ' ' << tegn.size() << ' ';
    it4 = tegn.begin();
    while (it4 != tegn.end())  cout << *it4++ << ' ' ;           cout << '\n';

    return 0;
}




//  Utskrift:  Brokkoli  Gulrot  Potet  Salat
//             Appelsin  Sitron  Mango
//             Eple  Banan  Kiwi
//             A A E L N R S
//             E S 4 E L R S
