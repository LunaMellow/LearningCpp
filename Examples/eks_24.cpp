/**
 *   Programeksempel nr 24 - STL:  Iteratorer - bruk ifm ulike containere.
 *
 *   Eksemplet viser primært bruk av iteratorer ifm. vector, list og map.
 *
 *   @file     EKS_24.CPP
 *   @author   Frode Haug, NTNU
 */

//  VS -,  CB +

#include <iostream>                //  cout
#include <string>                  //  string
#include <vector>                  //  vector
#include <list>                    //  list
#include <map>                     //  map
using namespace std;


void skrivListe(const list <string> & liste);
void skrivMengde(const map <string, string> & mengde);


/**
 *  Hovedprogrammet:
 */
int main()  {

// ***************************************************************************
// **   Iteratorer kan brukes til å aksessere enkeltelementer eller å gå    **
// **   gjennom flere (alle) elementer i en container. De er tilgjengelige  **
// **   ifm. mange ulike typer containere. Men, ifm. de fem vi fokuserer    **
// **   på, så er følgende å bemerke:                                       **
// **      - stack  og  queue:  utilgjengelig/irrelevant                    **
// **      - vector:  kan ofte like gjerne aksesseres via indeks ( [ ] )    **
// **                 Iteratorer brukes ifm. f.eks. 'insert' og 'erase'     **
// **      - list og map:  skal vi bruke iterator til mest (se nedenfor)    **
// **    ( - string:  iteratorer også tilgjengelig!  Men, stort sett nok    **
// **                 av andre funksjoner som gjør det meste ønskelige.)    **
// ***************************************************************************


// *******************************   VECTOR:   *******************************

    vector <int> tall;            //  Lager container:

    for (int i = 0; i <= 10; i++)  // Initierer 'tall' med: 1, 4, 7, 10, 13...
        tall.push_back((i*3)+1);

    cout << "\n\n'tall' vha. vanlig for-løkke og indeksering:  ";
    for (int i = 0; i <= 10; i++)
        cout << ' ' << tall[i];

    cout << "\n\n'tall' vha. Range Based for:  ";
    for (const auto & val : tall)  //  'const' og '&' - "sparer tid og plass".
        cout << ' ' << val;


    vector <int> :: iterator tallIt;  // "Omstendelig" initiering av iterator:
    cout << "\n\n'tall' vha. iterator, versjon 1:  ";
    for (tallIt = tall.begin();  tallIt != tall.end();  tallIt++)
        cout << ' ' << *tallIt;

    cout << "\n\n'tall' vha. iterator, versjon 2:  ";  // Kortere vha. 'auto':
    for (auto tallIt2 = tall.begin();  tallIt2 != tall.end();  tallIt2++)
        cout << ' ' << *tallIt2;

    cout << "\n\n'tall' vha. iterator, versjon 3:  ";  //  Alternativt:
    for (auto tallIt2 = begin(tall);  tallIt2 != end(tall);  tallIt2++)
        cout << ' ' << *tallIt2;


// ---------------------------------------------------------------------------

    tallIt = tall.begin() + 3;       //  iterator/peker til element nr.4 (10).
    tallIt = tall.insert(tallIt, 77);    //  SETTER INN 77 FORAN ITERATOREN !!
                                         //    OG 'tallIt' PEKER NÅ TIL 77 !
                                         //    (som er det nye 4.elementet)
    cout << "\n\n'tall' vha. iterator, når smettet inn 77:  ";
    for (auto tallIt2 = tall.begin();  tallIt2 != tall.end();  tallIt2++)
        cout << ' ' << *tallIt2;
    tall.insert(tallIt, 3, 99);      //  3x av verdien 99 FORAN iteratoren !
    cout << "\n\n'tall' vha. iterator, når smettet inn 3x 99:  ";
    for (auto tallIt2 = tall.begin();  tallIt2 != tall.end();  tallIt2++)
        cout << ' ' << *tallIt2;

    tallIt = tall.begin() + 8;      //  iterator/peker til element nr.9 (13).
    tall.erase(tallIt);             //  Sletter ETT aktuelt element (13).
    cout << "\n\n'tall' vha. iterator, når slettet 13:  ";
    for (auto tallIt2 = begin(tall);  tallIt2 != end(tall);  tallIt2++)
        cout << ' ' << *tallIt2;

    tallIt = tall.begin() + 6;      //  iterator/peker til element nr.7 (77).
              //   Alternativt:    tallIt = tall.begin();  advance(tallIt, 6);
    tall.erase(tallIt, tall.end()); //  SLETTER ALT MELLOM ITERATORENE !
    cout << "\n\n'tall' vha. iterator, når slettet ALT f.o.m 77:  ";
    for (auto tallIt2 = begin(tall);  tallIt2 != end(tall);  tallIt2++)
        cout << ' ' << *tallIt2;


    cout << "\n\n";


// ********************************   LIST:   ********************************

    list <string> tekster;                     //  Lager container.

    tekster.push_back("Kari");                 //  Initierer ved å legge til
    tekster.push_back("Ola");                  //    både bakerst og forrest:
    tekster.push_back("Lars");
    tekster.push_back("Per");
    tekster.push_front("Mari");
    tekster.push_front("Anne");
    tekster.push_front("Inger");
    tekster.push_front("Berit");

    cout << "\n\n'tekster' initielt:\n";               skrivListe(tekster);

    cout << "\n\n'tekster' etter SORTERING:\n";    //  Sorterer listen:
    tekster.sort();                                    skrivListe(tekster);

                                               //  iterator til 3.element:
    auto tekstIt =  tekster.begin();  tekstIt++;  tekstIt++;
                      //  NB:  Kan ifm. list IKKE bruke [] eller xxx.begin()+N
    cout << "\n\n3.element er:  " << *tekstIt;

                  //  Ellers er bruken av 'insert' og 'erase' likt med vector:
    tekstIt = tekster.erase(tekstIt);
    cout << "\n\n3.elementet er fjernet/slettet:\n";   skrivListe(tekster);

                   //  Iterator referer fortsatt til det 3.elementet ("Kari").
                   //  Setter så inn 3x "Marte":
    tekster.insert(tekstIt, 3, "Marte");
    cout << "\n\nEtter innsmett av 3x 'Marte':\n";     skrivListe(tekster);

    cout << "\n\n'tekster' BAKLENGS:\n";      //  TRAVERSERER LISTEN BAKLENGS:
    for (auto it = tekster.rbegin();  it != tekster.rend();  it++)
        cout << '\t' << *it << '\n';

    tekster.erase(tekster.begin(), tekster.end());  // Sletter HELE listen.
    //  Evt. ENDA enklere:      tekster.clear();

    cout << "\n\nEtter sletting av HELE listen:\n";    skrivListe(tekster);

    cout << "\n\n";


// ********************************   MAP:   ********************************

    map <string, string> mengde;

    mengde.insert(pair <string, string>("AA", "Arsenal"));   //  Initierer med
    mengde.insert(pair <string, string>("FF", "Fulham"));    //  en del data,
    mengde.insert(pair <string, string>("GG", "Gillingham")); // på to ulike
    mengde.insert(pair <string, string>("DD", "Derby"));     //  måter:
    mengde["BB"] = "Burnley";
    mengde["EE"] = "Everton";              // NB:  Indekseringen!  :-)
    mengde["HH"] = "Hull";
    mengde["CC"] = "Charlton";

    cout << "\n\n'mengde' initielt:\n";               skrivMengde(mengde);

    cout << "\n\nSkiver 'FF'-'HH' (end):\n";
    auto mapIt = mengde.find("FF");       //  NB: <list> har IKKE 'find'.
                                          //      Må da evt. bruke 'find(_if)'
                                          //      i <algorithm>.

    for ( ;  mapIt != mengde.end();  mapIt++)
        cout << '\t' << mapIt->first << ", " << mapIt->second << '\n';


    mapIt = mengde.find("KK");     //  Finnes ikke!  "Udefinert" iterator.
//    cout << '\t' << mapIt->first << ", " << mapIt->second << '\n';


    mengde.insert({"II", "Ipswich"});  // Et par av måtene å sette inn på:
    mengde["JJ"] = "Junajted";
    cout << "\n\nEtter innsetting av 'Ipswich' og 'Junajted':\n";
                                                      skrivMengde(mengde);

    mengde.erase("BB");                //  Sletter ETT angitt element.

    mapIt = mengde.find("DD");         //  Initierer iteratorer:
    auto mapIt2 = mengde.find("GG");

    mengde.erase(mapIt, mapIt2);       //  Sletter F.O.M og OPPTIL !!!
    cout << "\n\nEtter sletting av 'DD'-'FF':\n";   skrivMengde(mengde);


    return 0;
}


/**
 *  Skriver HELE en listes innhold.
 *
 *  @param   liste - list-container av datatypen 'string'
 */
void skrivListe(const list <string> & liste) {
    for (const auto & val : liste)
        cout << '\t' << val << '\n';
}


/**
 *  Skriver HELE en mengdens innhold.
 *
 *  @param   mengde - map-container med datatypene 'string' og 'string'
 */
void skrivMengde(const map <string, string> & mengde) {
    for (const auto & val : mengde)
        cout << '\t' << val.first << ", " << val.second << '\n';
}
