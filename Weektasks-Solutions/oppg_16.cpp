/**
 *   Løsningsforslag til oppgave nr 16.
 *
 *   Program som leser inn fra og skriver ut til fil 
 *   ulike subklasser (som har samme baseklasse).
 *   Filinnlesningen foregår via constructorene.
 *   Filutskriften foregår via virtuelle funksjoner ('skrivTilFil').
 *
 *   @file    OPPG_16.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setprecision
#include <string>                  //  string
#include <vector>                  //  vector
using namespace std;


/**
 *  Publikasjon (med tittel/navn og pris pr.eksemplar).
 */
class Publikasjon  {
  private:
    string  tittel;
    float   pris;

  public:
    Publikasjon(ifstream & inn)  {
        inn >> pris;  
        inn.ignore();                  //  Forkaster ' ' (blank) etter 'pris'.
        getline(inn, tittel);
    }

    virtual void skrivTilFil(ofstream & ut)  {
        ut << fixed << setprecision(2);       //  ALLTID med to desimaler.
        ut << pris << ' ' << tittel << '\n';
    }
};


/**
 *  Bok (med forfatter og sideantall - subklasse av 'Publikasjon').
 */
class Bok : public Publikasjon  {
  private:
    string forfatter;
    int    antallSider;

  public:
    Bok(ifstream & inn) : Publikasjon(inn)  {
        inn >> antallSider;
        inn.ignore();           //  Forkaster ' ' (blank) etter 'antallSider'.
        getline(inn, forfatter);

    }

    virtual void skrivTilFil(ofstream & ut)  {
        ut << 'B' << ' ';                //  Skriver objekttypen.
        Publikasjon::skrivTilFil(ut);    //  Baseklasse skriver ALT sitt eget.
        ut << antallSider << ' ' << forfatter << '\n';
    }
};


/**
 *  Magasin (med årstall og volum/utgivelse - subklasse av 'Publikasjon').
 */
class Magasin : public Publikasjon  {
  private:
    int  aar,
         volum;

  public:
    Magasin(ifstream & inn) : Publikasjon(inn)  {
        inn >> aar >> volum;   
        inn.ignore();         //  Forkaster avsluttende '\n' etter tallene.
    }

    virtual void skrivTilFil(ofstream & ut)  {
        ut << 'M' << ' ';                //  Skriver objekttypen.
        Publikasjon::skrivTilFil(ut);    //  Baseklasse skriver ALT sitt eget.
        ut << aar << ' ' << volum << '\n';
    }
};


vector <Publikasjon*>  gPublikasjoner; ///<  Datastrukturen med publikasjoner.


/**
 *  Hovedprogrammet:
 */
int main ()  {
    ifstream  innfil("oppg_16.dta");    //  Fil å lese INN fra.
    ofstream  utfil("oppg_16.dt2");     //  fil å skrive UT til.
    char objektType;                    //  'B' eller 'M' fra fil.

    if (innfil) {                       //  Filen finnes/mulig å åpne:
        cout << "\nLeser dataene fra 'OPPG_16.DTA'\n";
        innfil >> objektType;           //  Leser (om mulig) 1.felt ('B'/'M').
        while (!innfil.eof()) {         //  Ennå ikke filslutt:
            innfil.ignore();            //  Forkaster ' ' etter 'B'/'M'.
            switch (objektType) {
              case 'B': gPublikasjoner.push_back(new Bok(innfil));      break;
              case 'M': gPublikasjoner.push_back(new Magasin(innfil));  break;
              default:  cout << "\n\tUlovlig type objekt på filen: '"
                             << objektType << "'\n\n";                  break;
            }
            innfil >> objektType;       //  Leser (om mulig) 1.felt ('B'/'M').
        }
        
        innfil.close();                 //  Lukker innlesningsfilen.

                                        //  Skriver ALT til fil:
        cout << "\nSkriver dataene til 'OPPG_16.DT2'\n\n\n";
        for (int i = 0; i < gPublikasjoner.size(); i++)
            gPublikasjoner[i]->skrivTilFil(utfil);


    } else
      cout << "\n\tFant ikke filen 'OPPG_16.DTA'!\n\n";

    utfil.close();                      //  Utskriftsfilen lukkes uansett.

    return 0;
}