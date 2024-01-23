/**
 *   Løsning til kontinuasjonseksamen i OOProg (i C++), august 2022, oppgave 1B.
 *
 *   @file     EX_S22_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    vector <int> tall1(2);
    vector <int> tall2 { 2, 4, 8, 16, 32, 64 };
    vector <int> tall3(5, 9);
    vector <int> tall4(tall2);

    tall1 = tall3;
    for (const auto & val : tall1) cout << ' ' << val;   cout << " : ";
    for (const auto & val : tall4) cout << ' ' << val;   cout << '\n';

    cout << tall2[3] << ' ' << tall2.front() << ' '
         << tall2.back() << ' ' << tall2[tall2.size()-2]      << '\n';

    auto it  = find(tall2.begin(),  tall2.end(),  16);
    auto it2 = find(tall4.begin(),  tall4.end(),  16);

    cout << "Verdier er ";
    if (it == tall2.end()  ||  it2 == tall4.end()  ||  *it != *it2)
        cout << "IKKE ";                            cout << "like.\n";


    map <string, string> mengde;
    mengde.insert(pair <string, string>("10A", "Luton"));
    mengde.insert(pair <string, string>("11A", "Tottenham"));
    mengde.insert(pair <string, string>("12A", "Chelsea"));
    mengde.insert(pair <string, string>("13A", "Wolves"));
    mengde["10B"] = "Barnsley";
    mengde["11B"] = "Everton";
    mengde["12B"] = "Watford";
    mengde["13B"] = "Arsenal";

    for (const auto & val : mengde)
        cout << ' ' << val.first;                        cout << '\n';

    for (auto it = mengde.find("12A");  it != mengde.end();  it++)
        cout << ' ' << it->second;                       cout << '\n';


    return 0;
}



//  Utskrift:   9 9 9 9 9 :  2 4 8 16 32 64
//             16 2 64 32
//             Verdier er like.
//              10A 10B 11A 11B 12A 12B 13A 13B
//              Chelsea Watford Wolves Arsenal
