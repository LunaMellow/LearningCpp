/**
 *   Programeksempel nr 25 - STL:  Algoritmer.
 *
 *   Eksemplet viser bruken av NOEN F� UTVALGTE funksjoner p� <algorithm>.
 *
 *   @file     EKS_25.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <string>                  //  string
#include <list>                    //  list
#include <algorithm>               //  algorithm
using namespace std;


void skrivListe(const list <string> & liste);
void gjorNoe(const string & val)    { cout << '\t' << val << "-laget\n"; }
bool fjernNoe(const string & val)   { return (val == "Ipswich"); }


/**
 *  Hovedprogrammet:
 */
int main()  {
    list <string> tekster;
    string s1, s2;

    tekster.push_back("Arsenal");         tekster.push_back("Liverpool");
    tekster.push_back("Chelsea");         tekster.push_back("Tottenham");
    tekster.push_back("ManU");            tekster.push_back("Leeds");
    tekster.push_front("Ipswich");        tekster.push_front("ManC");
    tekster.push_front("Leicester");      tekster.push_front("Fulham");
    tekster.push_front("Stoke");          tekster.push_front("Norwich");
    tekster.push_back("Arsenal");         tekster.push_back("Liverpool");
    tekster.push_front("Stoke");          tekster.push_front("Norwich");
    tekster.push_back("Arsenal");         tekster.push_front("Arsenal");

    cout << "\n\nInitiell liste:\n";         skrivListe(tekster);

    s1 = "Arsenal";   s2 = "Everton";
    cout << "\n\nAntall '" << s1 << "':  "
        << count(tekster.begin(), tekster.end(), s1);         //  COUNT:
    cout << "\n\nAntall '" << s2 << "':  "
        << count(tekster.begin(), tekster.end(), s2);


    auto iter1 = max_element(tekster.begin(), tekster.end()); //  MAX_ELEMENT:
    cout << "\n\nSt�rste element er:  " << *iter1;


    auto iter2 = find(tekster.begin(), tekster.end(), "Ipswich");  //  FIND:

    if (iter2 != tekster.end()) {            //  M� finnes - ellers "s�ppel":
        cout << "\n\nIntervallet '" << *iter2 << "' til F�R '"
             << *iter1 << "' kopiert OVER de aller f�rste i listen:\n";
        copy(iter2, iter1, tekster.begin());     skrivListe(tekster); // COPY:
                                             //  Skriver alts� OVER elementer,
                                             //    INSERTER IKKE !!!
    }

    s2 = "ARSENAL!!!";                                          //  REPLACE:
    cout << "\n\nErstatter alle '" << s1 << "' med '" << s2 << "':\n";
    replace(tekster.begin(), tekster.end(), s1, s2);    skrivListe(tekster);
                                       //  NB:  Kan IKKE bruke tekst-parameter
                                       //         som ".......".

    cout << "\n\nListen er"                                     //  IS_SORTED:
        << (!is_sorted(tekster.begin(), tekster.end()) ? " IKKE" : "")
        << " sortert!";

    cout << "\n\nSortert liste:\n";
    tekster.sort();                                     skrivListe(tekster);

    cout << "\n\nListen er"                                     //  IS_SORTED:
        << (!is_sorted(tekster.begin(), tekster.end()) ? " IKKE" : "")
        << " sortert!";


    cout << "\n\nFunksjon kj�res for hvert element:\n";
    for_each(tekster.begin(), tekster.end(), gjorNoe);          //  FOR_EACH:

    cout << "\n\nFunksjon kj�res for hvert element - vha.lambda-funksjon:\n";
    for_each(tekster.begin(), tekster.end(),          //  lambda-funksjon: !!!
           [] (const auto & val)  { cout << '\t' << val << "-team\n"; } );
                                         //  Verre er ikke basic lambda !  :-)


    cout << "\n\nNummererer vha. lambda-funksjon:";
    int nr = 0;
    for_each(tekster.begin(), tekster.end(),          //  lambda-funksjon: !!!
         [&nr](const auto & val) { cout << "\n\t" << ++nr << ": " << val; } );

    cout << '\n';

    s1 = "Chelsea";   s2 = "Liverpool";
    cout << "\n\nFjerner alle '" << s1 << "' og '" << s2 << "':\n";
//  remove(tekster.begin(), tekster.end(), s1);                 //  REMOVE:
                                          //  NB:  LISTA ER LIKE LANG !!!
                                          //       Da slike funksjoner IKKE
                                          //       kan endre p� dens size
                                          //       (de har jo ikke tilgang!)
    tekster.remove(s1);                   //  Istedet er det da bedre � bruke:

                                          //  ELLER: Bruke tekster.erase(...),
                                          //  og bruke returpeker til ny slutt
                                          //  fra remove(...) som parameter !
    iter1 =  remove(tekster.begin(), tekster.end(), s2);
    tekster.erase(iter1, tekster.end());                  skrivListe(tekster);


    s1 = "Ipswich";   s2 = "ARSENAL!!!";
    cout << "\n\nFjerner alle '" << s1 << "':\n";               //  REMOVE_IF:
//  remove_if(tekster.begin(), tekster.end(), fjerneNoe); skrivListe(tekster);
                                          //  NB:  Fortsatt like lang!
                                          //  Bedre da som sagt � bruke:
    tekster.remove_if(fjernNoe);                          skrivListe(tekster);
                                          //  Eller den andre metoden ovenfor.

                                                      //  lambda-funksjon: !!!
    cout << "\n\nFjerner alle '" << s2 << "' :-(   - vha. lambda-funksjon:\n";
    tekster.remove_if([s2](const auto & val) { return (val == s2); } );
                                                          skrivListe(tekster);

    cout << "\n\n";

    return 0;
}


/**
 *  Skriver HELE en listes innhold.
 *
 *  @param   liste - list-container av datatypen 'string'
 */
void skrivListe(const list <string> & liste) {  // '&' - ingen KOPI av listen.
    for (const auto & val : liste)
        cout << '\t' << val << '\n';
    cout << "\t\t\tAntall i listen:  " << liste.size() << '\n';
}


// ***************************************************************************
// **                                                                       **
// **   LAMBDA-FUNKSJONER (jfr.11.8 i l�reboka):                            **
// **                                                                       **
// **   Generell syntaks (slik VI skal bruke dette):                        **
// **      [ A ] ( B ) {  C  }   p� EN linje, der:                          **
// **                                                                       **
// **   A = evt. parametre fra brukeren/koden, medsendt p� selve            **
// **       DEFINISJONstedet av funksjonen (jfr. koden ovenfor).            **
// **       Syntaksen med '[]' betyr at n� kommer det en lambda-funksjon.   **
// **       ( B ) er en funksjons vanlige parameterliste - UTEN navn foran. **
// **   B = parametre AUTOMATISK medsendt fra selve KALLstedet              **
// **       (n�r funksjonen BRUKES). For V�R del er dette ALLTID EN eller   **
// **       TO parametre. Disse blir AUTOMATISK VERDIER FRA CONTAINEREN.    **
// **   C = selve koden, som sv�rt ofte returnerer en BOOL. G�r koden       **
// **       over flere linjer, M� den da evt. avsluttes med return(..).     **
// **       Dog er retur-verdi uaktuelt/uinteressant ifm. for_each(...).    **
// **                                                                       **
// **                                                                       **
// **   VI skal prim�rt bruke lambda-funksjoner ifm:                        **
// **                                                                       **
// **     1) Sortering av <list>  - jfr. EKS_26.CPP                         **
// **        Typisk lambda-funksjon vil da se ut som (p� EN linje):         **
// **          	personer.sort( [] (const Person * p1, const Person * p2)    **
// **                    {  return (p1->hentID() < p2->hentID());  } );     **
// **           (evt. m� 'const'-bruken tas vekk)                           **
// **                                                                       **
// **     2) <algorithm> sine funksjoner med (jfr. koden ovenfor):          **
// **        for_each,  ..._of,  ..._if,  ..._if_not, ...partition...       **
// **                                                                       **
// ***************************************************************************
