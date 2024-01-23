/**
 *   Programeksempel nr 19 - Objekter fra/til fil.
 *
 *   Eksemplet viser/vektlegger hvordan objekter kan skrives til og 
 *   leses fra fil (b�de vha. spesifikke funksjoner og vha. constructor).
 *   Dessuten vises hvordan:
 *        - sjekke om en fil er funnet/�pnet
 *        - finne/konstatere filens slutt
 *        - sende med filobjekter som parameter til funksjoner
 *
 *   @file     EKS_19.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <vector>                  //  vector
using namespace std;


/**
 *  PersonA (med ansattnr, postnr, telefonnr, navn, gateadresse og poststed).
 */
class PersonA {
  private:
      int    ansattNr,
             postNr,
             tlfNr;
      string navn,
             gateAdr,
             postSted;

  public:
      PersonA(int nr)  {  ansattNr = nr;  }   //  Initierer 'ansattNr'.

      void lesFraFil(ifstream & inn) {        //  Leser objektets data/
          getline(inn, navn);                 //    posten fra fil:
          getline(inn, gateAdr);
          inn >> postNr;   inn.ignore();
          getline(inn, postSted);          //  NB  NB  NB  NB  NB  NB  NB:
          inn >> tlfNr;    inn.ignore();   //  Mac-/Linux-brukere m� antagelig
      }                                    //    bruke/si:  ignore(2) ifm. 
                                           //    forkasting av '\n'  !!!!!

      void skrivData() {                      //  Skriver ALT til skjerm:
        cout << "\tNr: " << ansattNr << ": " << navn << ",  " << tlfNr
             << "\n\t\t" << gateAdr << ", "<< postNr <<' '<< postSted << '\n';
      }
};


/**
 *  PersonB (med ansattnr, postnr, telefonnr, navn, gateadresse og poststed).
 */
class PersonB {
  private:
    int    ansattNr,
           postNr,
           tlfNr;
    string navn,
           gateAdr,
           postSted;

  public:
      PersonB(ifstream & inn, int nr) {     //  Initierer ('ansattNr') og
          ansattNr = nr;                    //    leser ALT annet fra fil:
          getline(inn, navn);
          getline(inn, gateAdr);
          inn >> postNr;   inn.ignore();
          getline(inn, postSted);
          inn >> tlfNr;    inn.ignore();
      }

      void skrivTilFil(ofstream & ut) {     //  Skriver ALT til fil:
          ut << ansattNr << ' ' << navn << '\n' << gateAdr << '\n'
             << postNr << ' ' << postSted << '\n' << tlfNr << '\n';
      }
};


vector <PersonA*>  gPersonerA;    ///<  Datastruktur med PersonA-objekter.
vector <PersonB*>  gPersonerB;    ///<  Datastruktur med PersonB-objekter.


/**
 *  Hovedprogrammet:
 */
int main()  {
    ifstream innfilA;             //  Filobjekt for INNLESNING.
    innfilA.open("eks_19.dta");   //  Tilknytter aktuell fil � lese fra.
    PersonA*  nyPersonA;          //  Hjelpepeker til nytt objekt.
    int aNr;                      //  1.felt i hver post (ansattnummer).

    if (innfilA) {                //  Filer en funnet/mulig � �pne:
       while (innfilA >> aNr) {   //  (KUN) ved '>>' ER det mulig � teste
                                  //    filslutt p� denne m�ten.
                                  //    (Vi vil prim�rt bruke det nedenfor,
                                  //    og som vi l�rte/brukte i GrProg.) 
         innfilA.ignore();        //  Forkaster ' ' F�R navnet!
         nyPersonA = new PersonA(aNr);    //  Ny person med hittil leste data. 
         nyPersonA->lesFraFil(innfilA);   //  Leser resten av dataene selv.
         gPersonerA.push_back(nyPersonA); //  Legger inn i datastrukturen.
       }

       innfilA.close();              //  Lukker filen manuelt.

                                     //  Skriver ALT det innleste til skjerm:
       for (int i = 0; i < gPersonerA.size(); i++)
           gPersonerA[i]->skrivData();

    } else
      cout << "\n\tFinner ikke filen 'EKS_19.DTA'!\n\n";

    cout << "\n\n";

// ***************************************************************************
// **    Det samme, p� en LITT annen m�te (som vi nok vil bruke mest):      **
// ***************************************************************************

    ifstream innfilB("eks_19.dta");  //  Definerer og �pner i EN operasjon.
    int aaNr;                        //  Ansattnummer.

    if (innfilB) {                   //  Filer en funnet/mulig � �pne:
        innfilB >> aaNr;             //  Pr�ver � lese STARTEN p� NESTE post:
        while (!innfilB.eof()) {     //  Enn� ikke n�dd filens slutt:
            innfilB.ignore();        //  Forkaster ' ' F�R navnet!
                            //  Lager, leser og legger inn i EN operasjon!!! :
            gPersonerB.push_back(new PersonB(innfilB, aaNr));
            innfilB >> aaNr;         //  Pr�ver � lese STARTEN p� NESTE post:
        }

        innfilB.close();                 //  Lukker filen manuelt.


        ofstream utfilB("eks_19.dt2");   //  Filobjekt for UTSKRIFT.

        for (int i = 0; i < gPersonerB.size(); i++)
            gPersonerB[i]->skrivTilFil(utfilB);  // Alle skriver seg selv til fil.

        utfilB.close();                  //  Lukker filen manuelt.
    }
    else
        cout << "\n\tFinner ikke filen 'EKS_19.DTA'!\n\n";
        
    return 0;
}

// ***************************************************************************
// **
// **  Istedet for ifstream innfil(".....")   og  ofstream utfil(".....")
// **  KAN det (til n�d) ogs� brukes:  fstream fil(".....", ios::in)
// **                          eller:  fstream fil(".....", ios::out)
// **
// **  Eller B�DE innlesning og utskrift SAMTIDIG (mer i EKS_20.CPP):
// **                        fstream fil(".....", ios::in | ios::out)
// **
// **  Flere parametre i Table 13-1  (bl.a.  ios::app  - LEGGE TIL BAKERST!!!)
// **
// ***************************************************************************
// **
// **  KAN ogs� skrive til fil vha. MANIPULATORER:  Table 13-2
// **
// **  Mer om FEILH�NDTERING ved filbruk:  Table 13-3 og 13-4
// **
// ***************************************************************************