/**
 *   Løsning til eksamen i OOProg (i C++), mai 2023, oppgave 1B.
 *
 *   @file     EX_V23_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    vector <char> tegn1(6, '*');
    vector <char> tegn2(2);
    vector <char> tegn3 { 'K', 'A', 'R', 'K', 'I', 'N', 'A', 'G', 'R', 'I' };
    vector <char> tegn4(tegn1);

    tegn2 = tegn4;
    for (const auto & val : tegn2) cout << ' ' << val;   cout << " : ";
    for (const auto & val : tegn3) cout << ' ' << val;   cout << '\n';

    cout << tegn3[3] << ' ' << tegn3.back() << ' ' << tegn3.at(5) << ' '
         << tegn2.front() << ' ' << tegn2[tegn2.size()-4]     << '\n';

    tegn2 = tegn3;
    auto it  = find(tegn2.begin(),  tegn2.end(),  'R');
    auto it2 = find(tegn2.rbegin(), tegn2.rend(), 'R');

    it++;  it2++;
    while (*it != *it2) cout << *it++ << ' ';            cout << '\n';


    map <int, string> navn;
    navn[18] = "Johan";
    navn.insert(pair <int, string>(29, "Augstus"));
    navn[7]  = "Simen";
    navn.insert(pair <int, string>(17, "May"));
    navn[16]  = "Andre";
    navn.insert(pair <int, string>(22, "April"));

    for (const auto & val : navn)
        cout << val.second << "  ";                      cout << '\n';

    for (auto it = navn.find(18);  it != navn.end();  it++)
        cout << it->first << ' ';                        cout << '\n';


    return 0;
}




//  Utskrift:   * * * * * * :  K A R K I N A G R I
//             K I N * *
//             K I N A
//             Simen  Andre  May  Johan  April  Augstus
//             18 22 29
