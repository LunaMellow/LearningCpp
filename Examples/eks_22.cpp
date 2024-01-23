/**
 *   Programeksempel nr 22 - STL:  map.
 *
 *   Eksemplet viser 'map' og noen aktuelle funksjoner.
 *
 *   @file     EKS_22.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <string>                  //  string
#include <map>                     //  map
using namespace std;


void skrivMengde(const map <int, string> mengde);


/**
 *  Hovedprogrammet:
 */
int main()  {

    map <int, string> mengde1;            //  Lager mengde med nøkkelen 'int',
                                          //    og tilhørende 'string'-data.

    mengde1.insert(pair <int, string> (5, "Elvira"));     //  Initierer med en
    mengde1.insert(pair <int, string> (3, "Christian"));  //    del data:
    mengde1.insert(pair <int, string> (7, "Gogutten"));
    mengde1.insert(pair <int, string> (2, "Bendik"));
    mengde1.insert(pair <int, string> (1, "Anette"));
    mengde1[4] = "Daniel";                //  Alternativ kortform:
    mengde1[6] = "Frida";
    mengde1[10] = "Jeanette";
    mengde1[8]  = "Håvard";
    mengde1[9]  = "Ingrid";

    cout << "\n'mengde1':\n";                            skrivMengde(mengde1);

    cout << "'mengde1[5]':   " << mengde1[5]  << '\n';
    cout << "'mengde1[9]':   " << mengde1[9]  << '\n';
    cout << "'mengde1[14]':  " << mengde1[14] << "\n\n";  // NB: 14 legges inn
    cout << "'mengde1' med '14':\n";                      //     UTEN data !!!
                                                         skrivMengde(mengde1);
    mengde1.erase(14);
    cout << "'mengde1' uten 14:\n";                      skrivMengde(mengde1);


                           //  Ny mengde - intieres som KOPI av HELE en annen:
    map <int, string> mengde2(mengde1);

    cout << "\n'mengde2' er en KOPI av HELE 'mengde1':\n";
                                                         skrivMengde(mengde2);

    mengde2.erase(9);                     //  Fjerner nøkkel 9
    cout << "Element med nøkkel 9 fjernet fra 'mengde2'.\n";
    if (mengde2.erase(6))                 //    og  6:
        cout << "Element med nøkkel 6 fjernet fra 'mengde2'.\n";

    mengde2.erase(mengde2.begin(), mengde2.find(4));  // '4' MÅ finnes !!!
    cout << "'mengde2' der ALLE nøkler OPP TIL 4 er slettet/fjernet:\n";
                                                         skrivMengde(mengde2);

    auto it = mengde2.find(7);
    if (it != mengde2.end())            //  MÅ sjekke at suksessfullt funn !!!
       cout << "Element 7:   " << it->first << ", " << it->second << "\n\n";

    if (mengde2.empty())
        cout << "'mengde2' er tom!";
    else
        cout << "Antall elementer i 'mengde2':  " << mengde2.size();

    cout << "\n\nBytter de to mengdene:\n";
    mengde1.swap(mengde2);
    cout << "'mengde1':\n";                              skrivMengde(mengde1);
    cout << "'mengde2':\n";                              skrivMengde(mengde2);


    cout << "mengde1.lower_bound(7): ";
    it = mengde1.lower_bound(7);     //  Får peker/iterator til første element
    cout << it->first << ", " << it->second << '\n';     //   >= 7.
    cout << "mengde1.upper_bound(7): ";
    it = mengde1.upper_bound(7);     //  Får peker/iterator til første element
    cout << it->first << ", " << it->second << "\n\n";   //   > 7.


    if (mengde1 == mengde2)              //  KAN også bruke:  !=  <  >  <=  >=
        cout << "Mengdene er like!\n";   //  DETTE GJELDER ALLE CONTAINERNE !!
    else                                 //  (men ofte lite hensiktsmessig(?))
        cout << "Mengdene er ulike!\n";

    cout << "\nKopierer HELE 'mengde2' over til/inni i 'mengde1':\n";
    mengde1 = mengde2;                   //  Gjelder også ALLE containerne !!
                                         //  (men hvor mye brukt i praksis?)
    cout << "'mengde1':\n";                            skrivMengde(mengde1);
    cout << "'mengde2':\n";                            skrivMengde(mengde2);
    if (mengde1 == mengde2)
        cout << "Mengdene er nå like!\n\n";
    else
        cout << "Mengdene er fortsatt ulike!\n\n";


//  + en del andre funksjoner ........

    return 0;
}


/**
 *  Skriver HELE mengdens innhold.
 *
 *  @param   mengde - map-container med int'er (nøkkel) og string (data)
 */
void skrivMengde(const map <int, string> mengde) {
    cout << "\tNøkkel\tData:\n";

    for (const auto & val : mengde)              //  Range-based for-løkke:
                                                 //  NB: 'first'/'second':
        cout << '\t' << val.first << '\t' << val.second << '\n';

//  Alternativt vha. iterator:
//    for (auto it = mengde.begin();  it != mengde.end();  it++)
                                                 //  NB:  'it er en PEKER !!!
//        cout << '\t' << it->first << '\t' << it->second << '\n';

    cout << "\n\n";
}
