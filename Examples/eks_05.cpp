/**
 *   Programeksempel nr 5 - Grunnleggende omkring. STL's vector.
 *
 *   Eksemplet viser det mest grunnleggende omkring en av STL's
 *   SEQUENCE CONTAINERs:  VECTOR - dvs. EN-dimensjonal array.
 *   Jfr. 8.12 i læreboka.
 *
 *   @file     EKS_05.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <vector>                  //  FOR Å KUNNE BRUKE:  STLs  vector
#include <string>                  //  string-klassen
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


//****************************************************************************
//****************************************************************************
//**              NB:    NB:    NB:    NB:    NB:    NB:                    **
//**       FOR (EN-DIMENSJONALE) ARRAYER BRUKES HERETTER PRIMÆRT VECTOR     **
//**         (men for char-arrayer, som er tekster, brukes string)          **
//**                                                                        **
//****************************************************************************
//****************************************************************************


/**
 *   Person (med navn og alder).
 */
struct Person {
    string  navn;
    int    alder;                                //  CONSTRUCTOR:  !!!!!
    Person(const string nvn, const int ald)   {  navn = nvn;  alder = ald;  }
};


void skrivVector(vector <int> vect);


/**
 *  Hovedprogrammet:
 */
int main()  {
  int i;
                                 //  Noen måter å lage/definere vectorer på:
    vector <int> tall;                 //  (Foreløpig) tom vector.
    vector <int> tall2(100);           //  Initielt 100-lang int-vector.
                                       //  NB:  '(..)' og IKKE '[...]'
    vector <int> tall3 { 3, 7, 11 };   //  3-lang vector m/initielle verdier.
                                       //  NB:  IKKE '=' før '{'
    vector <int> tall4(20, 7);         //  20-lang vector med 7-tall.
    vector <int> tall5(tall3);         //  vector som er kopi av en annen.
    vector <char> bokstaver(10, 'X');  //  char-vector med 10 stk 'X'er.
    vector <string> navn(10);          //  vector med 10 tomme stringer.


//  STOOOOR fordel med vector:   Størrelse/lengde kan bare økes når
//                               det trengs (til det "uendelige") !!!

// ***************************************************************************

                                     //  Når element nr.i finnes, så brukes en
                                     //    vector akkurat som en array !!!

    cout << "'tall3': ";             //  Skriver ut de fleste av vectorenes
    for (i = 0; i < 3; i++)          //    innhold - på litt ulike måter:
        cout << ' ' << tall3[i];
    cout << "\n\n";

    cout << "'tall5': ";             //  Kopiert vector ('tall5'):
    for (i = 0; i < 3; i++)
        cout << ' ' << tall5[i];
    cout << "\n\n";

    cout << "'tall3': ";             //  Vha. 'size':
    for (i = 0; i < tall3.size(); i++)
        cout << ' ' << tall3[i];
    cout << "\n\n";

    cout << "'tall4': ";             //  Vha. Range-Based:
    for (int val : tall4)
        cout << ' ' << val;
    cout << "\n\n";

    cout << "'tall': ";              //  'tall' er tom:
    for (i = 0; i < tall.size(); i++)
        cout << ' ' << tall[i];
    cout << "\n\n";

    cout << "'tall2':\n";            //  'tall2' er nullstilt(!):
    for (i = 0; i < tall2.size(); i++)
        cout << ' ' << tall2[i];
    cout << "\n\n";

    cout << "'navn':\n";             //  Vha. Range-Based:
    for (string val : navn)
        cout << "\t---." << val << ".---\n";
    cout << "\n\n";

    cout << "'tall3[5]' - som ikke finnes1: "; //  Selv holde orden på at
    cout << tall3[5] << "\n\n";                //    holder seg inni vectoren.
//  cout << "'tall3[5]' - som ikke finnes2: "; //  Kastes en "exeption", og
//  cout << tall3.at(5) << "\n\n";             //    programmet stopper.


// ***************************************************************************

    navn[0] = "Per, ";               //  Setter NOEN av stringene:
    navn[1] = "Pål og ";
    navn[2] = "Espen Askeladd";

    cout << "'navn' igjen:\n";       //  Skriver stringene nå:
    for (i = 0; i < navn.size(); i++)
        cout << "\t---." << navn[i] << ".---\n";
    cout << "\n\n";


    cout << "Skriv 5 tall:\n";       //  Leser fem verdier inni 'tall2':
    for (i = 0; i < 5; i++)
        tall2[i] = lesInt("\tTall", 0, 1000);

    cout << "\n'tall2':\n";          //  Skriver HELE 'tall2':
    for (i = 0; i < tall2.size(); i++)
        cout << ' ' << tall2[i];
    cout << "\n\n";                  //  Det er VI som må holde orden på
                                     //    hvor mye som er brukt av en
                                     //    vector med definert størrelse!

// ***************************************************************************
                                     //  Derfor ofte ønskelig med tom vector
                                     //    som blir tilført nye elementer:
    int verdi;
    cout << "Skriv 5 tall:\n";       //  Leser fem verdier inni 'tall':
    for (i = 0; i < 5; i++) {
        verdi = lesInt("\tTall", 0, 1000);
        tall.push_back(verdi);       //  'tall' er jo initielt TOM. Derfor MÅ
    }                                //    nye elementer ADDES til BAKERST !!!
                                     //  Mao:  tall[i] = verdi;  fungerer ikke
                                     //        om element nr.i IKKE finnes !!!

    cout << "\n'tall':\n";           //  Skriver det som nå er i 'tall':
    for (i = 0; i < tall.size(); i++)
        cout << ' ' << tall[i];
    cout << "\n\n";

    tall.pop_back();                 //  Tar vekk de to BAKERSTE elementene
    tall.pop_back();                 //    i vectoren 'tall' !!!

    cout << "\n'tall':\n";           //  Skriver det som nå er igjen i 'tall':
    for (i = 0; i < tall.size(); i++)
        cout << ' ' << tall[i];
    cout << "\n\n";


// ***************************************************************************

    tall.clear();

    cout << "\n'tall' sin lengde etter å ha blitt \"cleared\":  "
        << tall.size() << "\n\n";

    if (tall.empty())  cout << "'tall' er altså HELT tom!\n\n";

    cout << "\n'tall2' har pr. nå plass til  "
         << tall2.capacity() << " elementer.\n\n";


// ***************************************************************************
// ******************  vector og (pekere til) structer:  *********************
// ***************************************************************************

    Person  pers = { "Inger Haugen", 26 };
    Person* pers2;                          //  Hjelpepeker for opprettelse av
                                            //    nylagde Person-structer.
    vector <Person> personer;               //  vector med struct-VARIABLE.

    personer.push_back(pers);               //  Legger inn eksisterende.
    pers2 = new Person("Anne Hauge", 25);   //  Legger inn KOPI av 2x nylagde:
    personer.push_back(*pers2);
    delete pers2;  pers2 = nullptr;
    pers2 = new Person("Marit Haugstad", 28);
    personer.push_back(*pers2);
    delete pers2;  pers2 = nullptr;

    cout << "Antall elementer i 'personer': " << personer.size() << "\n\n";

    cout << "'personer' sitt innhold:\n";   //  Skriver vectorens innhold:
    for (i = 0; i < personer.size(); i++)
        cout << '\t' << personer[i].navn << ", " << personer[i].alder << '\n';
    cout << "\n\n";


// ***************************************************************************

    vector <Person*> personer2;             //  vector med PEKERE til structer.

    for (i = 1; i <= 4; i++)                //  Legger inn 4x NYOPPRETTEDE:
        personer2.push_back(new Person("Haugianer", 18 + i));

    pers2 = new Person("Haugianere", 33);   //  Lager enda en struct.
    personer2.push_back(pers2);             //  Legger inn PEKER til nr.5.

    cout << "Antall elementer TILPEKT i 'personer2': "   //  Skriver antallet:
         << personer2.size() << "\n\n";

    cout << "'personer2' sitt innhold:\n";  //  Skriver vectorens innhold:
    for (i = 0; i < personer2.size(); i++)
      cout <<'\t' << personer2[i]->navn <<", " << personer2[i]->alder << '\n';
    cout << "\n\n";


// ***************************************************************************
// **     NB NB NB:  VI SKAL PRIMÆRT BRUKE DENNE SISTE MÅTEN/METODEN !!!    **
// **                                                                       **
// **                MEN, HUSK da at i vectoren ligger det PEKERE.          **
// **                Altså MÅ BÅDE DET TILPEKTE OG PEKEREN (i vectoren)     **
// **                SLETTES når noe skal fjernes fra vectoren !!!!!!!!!    **
// **                         (se oppg.8, EKS_06.CPP og HER:)               **
// ***************************************************************************

    for (i = 0; i < personer2.size(); i++)       //  Sletter alle de TILPEKTE:
        delete  personer2[i];

    personer2.clear();                           //  Sletter selve PEKERNE.
    cout << "Antall elementer TILPEKT i 'personer2': "   //  Tom vector:
         << personer2.size() << "\n\n";


// ***************************************************************************
// *****************  vector som parameter til funksjon:  ********************
// ***************************************************************************

    skrivVector(tall);
    skrivVector(tall2);
    skrivVector(tall3);
    skrivVector(tall4);
    skrivVector(tall5);

    return 0;
}


/**
 *  Skriver ut på skjermen hele den medsendte vectorens innhold.
 *
 *  @param   vect  - int-vector som blir skrevet ut
 */
void skrivVector(vector <int> vect) {
    cout << "Medsendt vector-parameters innhold:\n";
    for (int i = 0; i < vect.size(); i++)
        cout << ' ' << vect[i];
    cout << "\n\n";
}


//****************************************************************************
//**  KAN også bl.a: - Kopiere hele vectorer  (f.eks: tall2 = tall3)        **
//**                 - Sammenligne lengde OG innhold (<  <=  >  >=  ==  !=) **
//**                 - Få tak verdien til første/siste element              **
//**                 - Øker en vectors størrelse med N elementer            **
//**                 - Snu vectorens innhold baklengs                       **
//**                 - Bytte om to vectorers innhold                        **
//**                 - Få tak i PEKER til første og siste element           **
//**                 - Sette inn/fjerne element på en angitt plass/indeks   **
//**                                                                        **
//**  Se Table 8-3 i læreboka og under linken "Ressurser" og "vector"       **
//**                                                                        **
//**  Til en del operasjoner brukes ITERATOR (mer i kap.16-18 i læreboka)   **
//**                                                                        **
//****************************************************************************
