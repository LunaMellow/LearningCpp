/**
 *   Løsningsforslag til kontinuasjonseksamen i OOProg, aug 2021, oppgave 2.
 *
 *
 *   NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:  NB:
 *   For å formodentlig øke leseligheten ift. hva det spørres etter
 *   i oppgaveteksten, så er følgende gjort med koden nedenfor:
 *
 *      - Den er helt kommentarløs (både ift. Doxygen og generelt).
 *      - Det oppgaveteksten spør om kommer MELLOM stjernelinjene ('*').
 *        (Ekstra kode (så koden kompilerer/kjører, og kan dermed testes)
 *         kommer altså FØR DE FØRSTE og ETTER DE SISTE stjernelinjene.)
 *      - (Medlems)funksjonenes innmat er primært kodet ifm. deklarasjonen.
 *
 *
 *   @file     EX_S21_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "LesData2.h"
using namespace std;


//****************************************************************************
//****************************************************************************
//****************************************************************************

class Besokende  {
  private:
    int tlfNr, antPersoner;
    string navn, mail;

  public:
    Besokende(int nr)  {  tlfNr = nr;   }

    int hentID()       {  return tlfNr; }

    void lesData()  {
      cout << "\tNavn:  ";  getline(cin, navn);
      cout << "\tMail:  ";  getline(cin, mail);
      antPersoner = lesInt("\tAntall personer", 1, 10);
    }

    void skrivTilFil(ofstream & ut) const  {
      ut << tlfNr << ' ' << antPersoner << ' ' << navn << ", " << mail <<'\n';
    }

    void skrivData() const;
};


class Sted  {
  private:
    string navn;
    map <int, Besokende*> besokende;

  public:
    Sted(string nvn)  {  navn = nvn;  }

    Besokende* finnBesokende() const  {
      int tlf;
      if (!besokende.empty()) {
         tlf = lesInt("\tTlfnr", 10000000, 99999999);
         auto it = besokende.find(tlf);
         if (it != besokende.end())
            return (it->second);
      } else
        cout << "\n\tLageret er tomt!\n";
      return nullptr;
    }


    void nyBesokende() {
      Besokende* nyttBesok;
      int tlf = lesInt("\tTlfnr", 10000000, 99999999);
      if (besokende.find(tlf) == besokende.end())  {
         nyttBesok = new Besokende(tlf);
         nyttBesok->lesData();
         besokende[tlf] = nyttBesok;
      } else
         cout << "\n\tDette telefonnummeret finnes allerede!\n";
    }


    void skrivAlle() const  {
      if (!besokende.empty()) {
         cout << "\n\tFølgende befinner seg på/i " << navn << ":\n";
         for (const auto & val : besokende)
            (val.second)->skrivData();
         cout << "\n\tTotalt: " << besokende.size() << " besøkende/kunder.\n";
      } else
        cout << "\n\tLageret er tomt!\n";
    }


    void slettBesokende() {
      ofstream utfil("ex_s21_BESOK.dta", ios::app);
      int tlf;

      Besokende* besok = finnBesokende();

      if (besok) {
          besok->skrivTilFil(utfil);
          tlf = besok->hentID();
          delete besok;
          besokende.erase(tlf);
          cout << "\n\tBesøkende/kunde er slettet!\n";
      } else
        cout << "\n\tIngen relevant besøkende/kunde funnet!\n";
    }

    void slettAlleResterende();
};


Sted gSted("Atsachas");


//****************************************************************************
//****************************************************************************
//****************************************************************************

void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tA - Skriv ALLE besøkende/kundene på stedet\n"
         << "\tN - Nytt besøk/kunde\n"
         << "\tF - Finn besøk/kunde\n"
         << "\tS - Slett/fjern besøk/kunde\n"
         << "\tQ - Quit / avslutt\n\n";
}


int main()  {
    char valg;
    Besokende* besok;

    skrivMeny();
    valg = lesChar("\n\nKommando");

    while (valg != 'Q') {
        switch (valg) {
          case 'A': gSted.skrivAlle();       break;
          case 'N': gSted.nyBesokende();     break;
          case 'S': gSted.slettBesokende();  break;
          case 'F': besok = gSted.finnBesokende();
                    if (besok) besok->skrivData();
                    else cout << "\n\tBesøkende/kunde ikke funnet!\n";
                                             break;
          default:  skrivMeny();             break;
        }
        valg = lesChar("\n\nKommando");
    }

    gSted.slettAlleResterende();               //  EXTRA

    cout << "\n\n";
    return 0;
}


void Besokende::skrivData() const  {
   cout << "\t\t" << tlfNr << ":  " << antPersoner << " stk  "
        <<  navn << ",  " << mail <<  '\n';
}


void Sted::slettAlleResterende() {             //  EXTRA
  ofstream utfil("ex_s21_BESOK.dta", ios::app);
  while (!besokende.empty())  {
    auto it = besokende.begin();
    (it->second)->skrivTilFil(utfil);
    delete (it->second);
    besokende.erase(it);
  }
  cout << "\n\tALLE resterende besøkende/kunder skrevet til 'BESOK.DTA'.\n";
  cout << "\tTotalt: " << besokende.size() << " besøkende/kunder igjen.\n";
}
