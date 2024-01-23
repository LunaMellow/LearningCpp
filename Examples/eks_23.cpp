/**
 *   Programeksempel nr 23 - STL:  Iteratorer - introduksjon/enkel bruk.
 *
 *   Eksemplet viser flere ulike m�ter � g� gjennom en int-vector p�:
 *   B�de ved bruk av vanlig indeksering, kortform og vha. en iterator.
 *   Dessuten forklares ogs� forskjellene p�:
 *        'auto val',  'auto & val'  og  'const auto & val'.
 *
 *   @file     EKS_23.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <vector>                  //  vector
//  #include <iterator>            //  Overfl�dig/un�dvendig?
using namespace std;


/**
 *  Hovedprogrammet:
 */
int main()  {

    vector <int> tall { 1, 2, 4, 8, 16, 32, 64, 128, 256 };

    cout << "\n\n1.utskrift:  ";          //  Tradisjonell m�te:
    for (int i = 0; i < tall.size(); i++)
        cout << "  " << tall[i];

    cout << "\n\n2.utskrift:  ";          //  Vha. vectors funksjonen 'at':
    for (int i = 0; i < tall.size(); i++)
        cout << "  " << tall.at(i);

    cout << "\n\n3.utskrift:  ";          //  Nyere kortform (jfr.EKS_04.CPP):
    for (int val : tall)
        cout << "  " << val;

// ---------------------------------------------------------------------------

    cout << "\n\n4.utskrift:  ";          //  Kortform, med bruk av 'auto',
    for (auto val : tall)                 //    som automatisk blir/finner
        cout << "  " << val;              //    aktuell datatype.
                                    //  'val' INNEHOLDER KOPI AV ELEMENTET !!!

    cout << "\n\n5.utskrift:  ";          //  Kortform, med bruk av 'auto',
    for (auto & val : tall)               //    som automatisk blir/finner
        cout << "  " << val;              //    aktuell datatype.
                                    //  'val' REFERERER TIL ELEMENTET, OG
                                    //    GJ�R AT ORIGINALEN KAN ENDRES !!!

    cout << "\n\n6.utskrift:  ";          //  Kortform, med bruk av 'auto',
    for (const auto & val : tall)         //    som automatisk blir/finner
        cout << "  " << val;              //    aktuell datatype.
                                    //  'val' REFERERER TIL ELEMENTET, MEN
                                    //     DET KAN IKKE ENDRES !!!
                                    //     (S�rlig hensiktsmessig for � spare
                                    //     tid og plass for datamaskinen.)
                                    //     Den mest brukte skriveformen, ved
                                    //     gjennomgang av vanlig vector ???


// *************************   VHA. ITERATOR:   *************************

    cout << "\n\n7.utskrift:  ";          //  Formell skrivem�te/bruk:
    for (vector <int> :: iterator it = tall.begin();  it != tall.end();  it++)
        cout << "  " << *it;              //  'it' er en peker til 'int'en !!!
                                          //  KAN evt. bruke '<', MEN:
                                          //  NB:  IKKE '<=' !!!

    cout << "\n\n8.utskrift:  ";          //  Kortform, med bruk av 'auto':
    for (auto it = tall.begin();  it != tall.end();  it++)
        cout << "  " << *it;              //  'it' ER ALLEREDE EN PEKER til
                                          //  elementet, derfor lite poeng
                                          //  i � evt. bruke 'auto & it' !!!

    cout << "\n\n9.utskrift:  ";          //  Kortform, med bruk av 'while':
    auto it2 = tall.begin();
    while (it2 != tall.end())
        cout << "  " << *it2++;


    cout << "\n\nF�rste og siste element er :  ";
    cout << tall.front() << "  " << tall.back() << "\n\n";

// NB:  NB:   'begin/end'  er IKKE det samme som 'front/back' !!!

    return 0;
}
