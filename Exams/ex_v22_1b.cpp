/**
 *   Løsning til eksamen i OOProg (i C++), mai 2022, oppgave 1B.
 *
 *   @file     EX_V22_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
#include <list>
using namespace std;


int main() {
    vector <char> tegn1(4);
    vector <char> tegn2 { 'A', 'N', 'E', 'T', 'O', 'R', 'E' };
    vector <char> tegn3(8, '-');
    vector <char> tegn4(tegn2);

    tegn1 = tegn3;
    for (const auto & val : tegn1) cout << ' ' << val;   cout << " : ";
    for (const auto & val : tegn4) cout << ' ' << val;   cout << '\n';

    auto it = tegn2.begin();
    for (  ;  *it != 'O';  it++)
        cout << ' ' << *it;
    cout << ' ' << tegn2[3] << ' ' << tegn2[tegn2.size()-1]   << '\n';

    tegn2.erase(it, tegn2.end());
    tegn2.pop_back();       tegn2.pop_back();
    tegn2.push_back('N');   tegn2.push_back('E');
    for (const auto & val : tegn2) cout << ' ' << val;   cout << '\n';


    list <int> tall(3, 7);
    tall.push_front(2);   tall.push_front(4);
    tall.push_back(1);    tall.push_back(3);
    for (const auto & val : tall) cout << ' ' << val;
    cout << " - " << tall.front() << ' ' << tall.back()       << '\n';

    tall.reverse();       tall.remove(7);
    for (auto it = tall.rbegin();  it != tall.rend();  it++)
        cout << ' ' << *it;                              cout << '\n';

    return 0;
}



//  Utskrift:  - - - - - - - - :  A N E T O R E
//             A N E T T E
//             A N N E
//             4 2 7 7 7 1 3 - 4 3
//             4 2 1 3
