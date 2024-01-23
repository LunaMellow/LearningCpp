 /**
  *   Programeksempel nr 7 - Objekter som parameter (verdi- og 
  *                          referanseoverf�ring) og som returverdi.
  *
  *   @file     EKS_07.CPP      (basert noe p� Program 7-9 og 7-10 i l�reboka)
  *   @author   Frode Haug, NTNU
  */


#include <iostream>
#include <iomanip>
#include <string>
#include "LesData2.h"
using namespace std;


/**
 *  Vare (med nummer, beskrivelse, antallet og prisen).
 */
class Vare {
  private:
    int    nummer;               //  Varenummer.
    string beskrivelse;          //  Varebeskrivelse.
    int    antall;               //  Antall (p� lager).
    float  pris;                 //  Pris.

  public:
    Vare() {                     //  Parameterl�s constructor:
        nummer = antall = pris = 0;
        beskrivelse = "";
    }
                                 //  Paramerfylt constructor:
    Vare(int n, string b, int a, float p) {
        settData(n, b, a, p);
    }
                                 //  Setter ALLE datamedlemmer:
    void settData(int n, string b, int a, float p) {
        nummer = n;     beskrivelse = b;
        antall = a;     pris = p;
    }
                                 //  Returnerer ALLE datamedlemmer
                                 //    vha. referanseoverf�ring:
    void hentData(int & n, string & b, int & a, float & p)  const {
        n = nummer;     b = beskrivelse;
        a = antall;     p = pris;
    }

    void lesData() {             //  Leser ALLE datamedlemmer:
        nummer = lesInt("Nummer", 1, 1000);
        cout << "Beskrivelse:  ";   getline(cin, beskrivelse);
        antall = lesInt("Antall", 0, 10000);
        pris = lesFloat("Pris", 1.0F, 100000.0F);
    }

    void skrivData() const {     //  Skriver ALLE datamedlemmer:
        cout << "\tNr." << nummer << ":  " << beskrivelse
             << "    har " << antall << " stk a kr." << pris << '\n';
    }
};


Vare lesVare();
void lesVare(Vare & v);
void visVare(const Vare v);
//  void visData(const Vare & v);  KAN faktisk skrive den siste slik ogs�!!!!!
                                   //  Dermed er det ikke mulig � endre p� 'v'
                                   //  (som jo heller ikke er meningen). Men,
                                   //  pga referanseoverf�ring ('&') tas det
                                   //  IKKE kopi, og en del tid/arbeid/memory
                                   //  spares av/for maskinen!!!
                                   //  Denne kodem�ten er IKKE uvanlig.

/**       
 *  Hovedprogrammet:
 */
int main()  {
    Vare vare1,             //  4x parameterl�se constructorer kj�res/brukes:
         vare2,
         vare3,
         vare4,             //  1x parameterfylt constructor kj�res/brukes:
         vare5(5, "Epler", 5555, 5.50F);


                            //  Setter data p� 4x andre ulike m�ter
                            //    (de 2x f�rste er de mest vanlige � bruke,
                            //     pluss at leser seg selv fra fil):
    vare1.settData(1, "Appelsiner", 1111, 1.10F);  //  Sender som parametre.

    cout << "\nVare nr.2:\n";
    vare2.lesData();        //  Leser selv sine data.

    cout << "\nVare nr.3:\n";
    vare3 = lesVare();      //  NB: Ikke det mest vanlige, men selvsagt mulig.

    cout << "\nVare nr.4:\n";
    lesVare(vare4);         //  NB: Ei heller mest vanlig, men selvsagt mulig.


    cout << fixed << showpoint << setprecision(2) << "\n\n";

    vare1.skrivData();      //  ALLE objektene skriver selv sine data:
    vare2.skrivData();
    vare3.skrivData();
    vare4.skrivData();
    vare5.skrivData();
    cout << "\n\n";

    visVare(vare1);         //  NB: Ikke det mest vanlige, men selvsagt mulig:
    visVare(vare2);
    visVare(vare3);
    visVare(vare4);
    visVare(vare5);
    cout << "\n\n";

    return 0;
}


/**
 *  Leser inn alle data til en 'Vare' og returnerer denne.
 *
 *  @return   En 'Vare' fylt med sine datamedlemmer
 *  @see      Vare::settData(...)
 */
Vare lesVare()  {
    Vare   nyVare;                              //  Lager et lokalt objekt.
    string beskr;                               //  Og diverse variable som
    int    nr, ant;                             //    fylles etterhvert:
    float  pr;

    nr  = lesInt("Nummer", 1, 1000);         
    cout << "Beskrivelse:  ";   getline(cin, beskr);
    ant = lesInt("Antall", 0, 10000);
    pr  = lesFloat("Pris", 1.0F, 100000.0F);

    nyVare.settData(nr, beskr, ant, pr);        //  Setter objektets data.

    return nyVare;                              //  Returnerer fylt objekt.
}


/**
 *  Fyller en medsendte 'vare' med data.
 *
 *  @param   v  - varen som f�r fylt sine data (referanseoverf�ring)
 *  @see     Vare::lesData()
 */
void lesVare(Vare & v)  {
    v.lesData();                                //  Leser selv sine data. 
//  v = lesVare();          //  Alternativ m�te.
}


/**
 *  Skriver alle en vares data p� skjermen, ved � hente disse med ref.overf�r.
 *
 *  @param   v  - Varen som alle data hentes for, og skrives ut om
 *  @see     Vare::hentData(...)  evt.  Vare::skrivData()
 */
void visVare(const Vare v)  {
  int    nr, ant;                              //  Lokale variable som skal
  string beskr;                                //    fylles med 'v' sine data:
  float  pr;

  v.hentData(nr, beskr, ant, pr);              //  Henter dataene vha.
                                               //    referanseoverf�ring.
  cout << "\tNr." << nr << ":  " << beskr      //  Skriver alt:
       << "    har " << ant << " stk a kr." << pr << '\n';

// HELE innmaten kunne selvsagt bare v�rt erstattet med:   v.skrivData();
}