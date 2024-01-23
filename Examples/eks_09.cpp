 /**
 *   Programeksempel nr 9 - Større programeksempel.
 *
 *   Eksemplet er KUN EN REN OMSKRIVING av EKS_39.c fra GrProg (PROG1001)
 *   som brukte struct og over til BRUK AV CLASS/OBJEKTER.
 *
 *   De mest viktige endringene er:
 *     - struct          -->   class
 *     - char-array      -->   string
 *     - Andre arrayer   -->   vector
 *     - malloc / free   -->   new / delete
 *     - const'er er helt tatt vekk
 *     - Globale variable er halvert
 *     - Funksjoner startende med vin.../produsent... er:
 *               - omnavnet til Vin::... /  Produsent::...
 *               - stort sett blitt parameterløse
 *               - flyttet inn i klassene
 *               - fått minimalt endret sitt logiske innhold
 *     - Noen flere små funksjoner og constructor i begge klassene
 *     - ALT ifm. til/fra fil er tatt vekk, da ennå ikke gjennomgått i emnet
 *
 *   @file     EKS_09.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Produsent (med navn, gate-/stedsadresse, mailadresse og telefon).
 */
class Produsent  {
  private:
    string navn,
           adr,
           mail;
    int    tlf;
  public:
      Produsent()  {  navn = adr = mail = "";   tlf = 0;  }
      bool harNavn(const string nvn) const {  return (navn == nvn);  }
      void lesData(const string nvn);
      void skrivData() const;
};


/**
 *  Vin (med navn, årgangene, antall av hver årgang og produsentnr/-indeks).
 */
class Vin  {
  private:
    string navn;
    vector <int>  aargang,
                  antall;
    int    produsentNr;
  public:
      Vin()  {  navn = "";  produsentNr = -1;  }
      bool harProdNr(const int nr)  const  {  return (produsentNr == nr);  }
      void endre();
      void lesData(const int nr);
      void skrivData() const;
};


void endreVin();
int  finnProdusent(const string nvn);
void frigiAllokertMemory();
void nyProdusent();
void nyVin();
void skrivAlleProdusenter();
void skrivMeny();
void skrivVinerFraProdusent();


vector <Produsent*> gProdusentene;           ///<  Produsent-oversikten.
vector <Vin*>       gVinene;                 ///<  Vin-oversikten.


/**
 *  Hovedprogrammet:
 */
int main ()  {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q')  {
        switch (kommando)  {
          case 'S': skrivAlleProdusenter();    break;
          case 'A': skrivVinerFraProdusent();  break;
          case 'P': nyProdusent();             break;
          case 'V': nyVin();                   break;
          case 'E': endreVin();                break;
          default:  skrivMeny();               break;
        }
        kommando = lesChar("\nKommando");
    }

    frigiAllokertMemory();

    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Kopierer inn og leser ALLE objektets datamedlemmer.
 *
 *  @param   nvn  - Allerede innlest navn (som unnalagres)
 */
void Produsent::lesData(const string nvn) {
    navn = nvn;
    cout << "\tAdresse:  ";   getline(cin, adr);
    cout << "\tMail:     ";   getline(cin, mail);
    tlf  = lesInt("\tTlf.nr", 10000000, 99999999);
}


/**
 *  ALLE objektets datamedlemmer skrives ut på skjermen.
 */
void Produsent::skrivData() const  {
  cout << '\t' << navn << ", " << tlf << ", " << mail
       << "\n\t\t" << adr << '\n';
}


/**
 *  Legger til (om mulig) ny årgang og/eller endrer antallet av en vin.
 */
void Vin::endre() {
  int nr = -1,                                   //  Årgangens indeks.
      aar,                                       //  Aktuelt årgang
      ant;                                       //    og antall.

  cin >> aar >> ant;                             //  Leser årgang og antall.
  cin.ignore();                                  //  Leser '\n'.

  if (aar >= 1900 && aar <= 2019) {              //  Årgang er i OK intervall:
     for (int i = 0;  i < aargang.size();  i++)  //  Finnes årgang allerede?
         if (aargang[i] == aar) {  nr = i;  break;  }  //  Funn!

     if (nr != -1) {                             //  Årgangen finnes:
        if (ant > 0 || -ant <= antall[nr]) {     //  Får nye eller nok igjen:
           antall[nr] += ant;                    //  Oppdaterer antall igjen.
           cout << "\n\tAntall på lager av årgang "        //  Skriver nytt
                << aar << ":  " << antall[nr] << "\n\n";   //    antall.
        } else                                 //  Prøver å fjerner for mange:
           cout << "\n\tHar kun " << antall[nr] << " stk. på lager!\n\n";
     } else {                                  //  Årgangen er ny:
        if (ant >= 0) {                        //  Positivt antall flasker:
           aargang.push_back(aar);             //  Legger inn nye årgang og
           antall.push_back(ant);              //    antall i vectorene.
           cout << "\n\tAntall på lager av årgang "          //  Skriver nytt
                << aar << ":  " << antall[antall.size()-1]   //    antall.
                << "\n\n";
        } else                            //  Umulig med negativt nytt antall:
           cout << "\n\tUmulig med negativt antall av en ny årgang!\n\n";
     }
  } else                                  //  Årgang utenfor intervall:
     cout << "\n\tÅrstall utenfor aktuelt intervall: 1900-2019.\n\n";
}


/**
 *  Kopierer inn og leser datamedlemmer.
 *
 *  @param   nr  - Allerede innlest produsentnummer (som unnalagres)
 */
void Vin::lesData(const int nr) {
    produsentNr = nr;            //  Lagrer unna allerede innlest produsentnr.
    cout << "\tVinnavn:  ";   getline(cin, navn);  //  Leser vinnavnet.
}


/**
 *  ALLE datamedlemmer skrives ut på skjermen.
 */
void Vin::skrivData()  const  {
    cout << '\t' << navn << ",  #årganger: " << aargang.size() << "\n\t\t";
    for (int i = 0;  i < aargang.size();  i++)  // Alle årgangene og antall:
        cout << "   " <<   aargang[i] << " (" << antall[i] << ')';
    cout << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Endrer en vin (ny årgang og/eller nytt antall).
 *
 *  @see  Vin::endre(...)
 */
void endreVin()  {
  int nr;                                  //  Ønsket vinnummer å endre på.

  cin >> nr;                               //  Leser vinens nummer.

  if (nr >= 1  &&  nr <= gVinene.size())   //  Nummer i aktuelt intervall:
     gVinene[nr-1]->endre();               //  Ny årgang og/eller nytt antall.
  else                                     //  Uaktuelt vinnummer skrevet:
     cout << "\n\tNummer utenfor aktuelt intervall: 1-"
          << gVinene.size() << ".\n\n";
}


/**
 *  Prøver å finne indeksen i 'gProdusentene' for en navngitt produsent.
 *
 *  @param   nvn  - Søkt produsents navn
 *  @return  Indeksen for produsenten, evt. -1 om ikke ble funnet
 *  @see     Produsent::harNavn(...)
 */
int  finnProdusent(const string nvn)  {
    for (int i = 0;  i < gProdusentene.size();  i++)
        if (gProdusentene[i]->harNavn(nvn))  return i;   //  Funn/match!

    return -1;                           //  Ikke funnet noen med dette 'nvn'.
}


/**
 *  Frigir ALL allokert memory under run-time.
 */
void frigiAllokertMemory()  {
   int i;
                                            //  Går gjennom ALLE produsentene:
   for (i = 0; i < gProdusentene.size(); i++)
       delete gProdusentene[i];             //  Alle OBJEKTENE slettes.
   gProdusentene.clear();                   //  Alle PEKERNE slettes.

                                            //  Går gjennom ALLE vinene:
   for (const auto & val : gVinene)  //  ALTERNATIVT:  Range-Based-For-løkke.
       delete val;                          //  Alle OBJEKTENE slettes.
   gVinene.clear();                         //  Alle PEKERNE slettes.

}


/**
 *  Legger (om mulig) inn en ny produsent.
 *
 *  @see  finnProdusent(...)
 *  @see  Produsent::lesData(...)
 */
void nyProdusent()  {
    Produsent* nyProdusent;                     //  Nytt Produsent-objekt.
    string navn;                                //  Ny produsents navn.

  cout << "\tNavn:     ";  getline(cin, navn); // Leser ny(?) produsents navn.
  if (finnProdusent(navn) == -1) {    //  Ingen med dette navnet allerede:
      nyProdusent = new Produsent;    //  Allokerer plass til en ny produsent:
      nyProdusent->lesData(navn);     //  Leser selv sine data.
      gProdusentene.push_back(nyProdusent);   //  Legger inn i datastrukturen.
      cout << "\n\tNy produsent er nr. " << gProdusentene.size() << "\n\n";
  }  else                             //  Produsenten finnes:
      cout << "\n\tFinnes en produsent med dette navnet allerede!\n\n";
}


/**
 *  Legger (om produsent finnes) inn en ny vin.
 *
 *  @see  finnProdusent(...)
 *  @see  Vin::lesData(...)
 */
void nyVin()  {
  Vin* nyVinObj;                               //  Nytt Vin-objekt.
  string navn;                                 //  Produsentens navn.
  int nr;                                      //  Produsentens indeks.

  cout << "\tProdusentnavn: ";  getline(cin, navn); // Leser produsents navn.
  if ((nr = finnProdusent(navn)) != -1)  {     //  Produsenten finnes:
      nyVinObj = new Vin;             //  Allokerer plass til en ny vin:
      nyVinObj->lesData(nr);          //  Leser selv sine data.
      gVinene.push_back(nyVinObj);    //  Legger inn i datastrukturen.
      cout << "\n\tNy vin er nr. " << gVinene.size() << "\n\n";
  } else
      cout << "\n\tFinnes ingen produsent med dette navnet!\n\n";
}


/**
 *  Skriver ALLE produsentene.
 *
 *  @see  Produsent::skrivData(...)
 */
void skrivAlleProdusenter()  {
    for (int i = 0;  i < gProdusentene.size();  i++)  {  //  For hver produsent:
        cout << '\t' << setw(3) << i+1 << ':';           //  Skriver indeks og
        gProdusentene[i]->skrivData();                   //    ALLE data.
    }
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
   cout << "\nFølgende kommandoer er tilgjengelig:\n"
        << "\tS - Skriv alle produsenter\n"
        << "\tA - skriv Alle viner fra en gitt produsent\n"
        << "\tP - ny Produsent\n"
        << "\tV - ny Vin\n"
        << "\tE <nr>  <(nytt) år>  <ant.flasker inn(+)/ut(-)>\n\t      "
        << "- Endre vin ( (ny) årgang og/eller antall (selge/etterfylle) )\n"
        << "\tQ - Quit / avslutt\n";
}


/**
 *  Skriver ALLE viner fra EN produsent.
 *
 *  @see  finnProdusent(...)
 *  @see  Vin::harProdNr(...)
 *  @see  Vin::skrivData(...)
 */
void skrivVinerFraProdusent()  {
   string navn;                                   //  Produsentens navn.
   int nr;                                        //  Produsentens indeks.
                                                  //  Leser produsentens navn:
   cout << "\tVin fra produsent:  ";  getline(cin, navn);
   if ((nr = finnProdusent(navn)) != -1) {        //  Produsenten finnes:

      for (int i = 0;  i < gVinene.size();  i++)  //  For hver vin:
          if (gVinene[i]->harProdNr(nr))  {       //  Aktuell produsent?
             cout << '\t' << setw(3) << i+1 << ':'; //  Skriver:  - indeks/nr
             gVinene[i]->skrivData();             //              - data
          }
  } else                                          //  Produsenten finnes ikke:
    cout << "\n\tFinnes ingen produsent med dette navnet!\n\n";
}
