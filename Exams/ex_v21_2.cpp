/**
 *   Løsningsforslag til eksamen i OOProg (i C++), juni 2021, oppgave 2.
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
 *      - Begge subklassene inneholder flere datamedlemmer enn påkrevd.
 *   (Når overflødige linjer (blanke), ekstra datamedlemmer (utover to stk),
 *    og linjer med kun '}' er ignorert, så er påkrevet kode på ca.80 linjer.)
 *
 *
 *   @file     EX_V21_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "LesData2.h"
using namespace std;

                                           //  Mye lik "Medisiner/Pasienter"
class Produsenter {                        //    i EKS_28.CPP:
  private:
    vector <string> navn;

  public:
    int finn(const string nvn)  {
        for (unsigned int i = 0;  i < navn.size();  i++)
            if (navn[i] == nvn) return (i+1);

        navn.push_back(nvn);
        return navn.size();
    }

    string hentNavn(const unsigned int i) const  {
        if (i > 0  &&  i <= navn.size())
           return (navn[i-1]);
        else
           cout << "\n\tIndeks for pasientnavn utenfor lovlig intervall 1-"
                << navn.size() << " !\n";
        return "";
    }
};


//****************************************************************************
//****************************************************************************
//****************************************************************************


Produsenter gProdusenter;


class Lys  {
  private:
     int produsentNr,
         antall;

  public:
     void endreAnt()  {
       cout << "\n\tNåværende antall:  "  <<  antall << '\n';
       antall +=  lesInt("\t\tØke(+) / minske(-) med", -antall, 100);
       cout << "\n\tNytt antall:       "  <<  antall << '\n';
     }

     virtual void lesData()  {
       string navn;
       cout << "\tProdusentnavn:  ";   getline(cin, navn);
       produsentNr = gProdusenter.finn(navn);
       antall = lesInt("\tAntall av lyset", 0, 100);
     }

     virtual void skrivTilFil(ofstream & ut) const  {
       ut << produsentNr << ' ' << antall;
     }

     virtual void skrivData() const;             //  FERDIGLAGET lengre nede.
};


class Lyspaere : public Lys  {
  private:
    bool  tynnSokkel,
          LED,
          klartGlass;
    int   watt;

  public:
     virtual void lesData()  {
       Lys::lesData();
       tynnSokkel = (lesChar("\tTynn sokkel (J/n)") != 'N');
       LED        = (lesChar("\tLED-pære    (J/n)") != 'N');
       klartGlass = (lesChar("\tKlart glass (J/n)") != 'N');
       watt       =  lesInt("\tAntall watt", 15, 120);
     }

     virtual void skrivTilFil(ofstream & ut) const  {
       ut << "P ";
       Lys::skrivTilFil(ut);
       ut << ((tynnSokkel) ? " +": " -")   << ((LED) ? " +": " -")
          << ((klartGlass) ? " + ": " - ") << watt << '\n';
     }

     virtual void skrivData() const;             //  FERDIGLAGET lengre nede.
};


class Stearinlys : public Lys  {
  private:
     int    lengde,
            tykkelse,
            brenneTid;
     string farge, form;

  public:
     virtual void lesData()  {
       Lys::lesData();
       lengde    = lesInt("\tLengde    (i cm) ", 2, 40);
       tykkelse  = lesInt("\tTykkelse  (i cm) ", 2, 20);
       brenneTid = lesInt("\tBrennetid (i timer)", 4, 200);
       cout << "\tFarge:  ";   getline(cin, farge);
       cout << "\tForm:   ";   getline(cin, form);
     }

     virtual void skrivTilFil(ofstream & ut) const  {
       ut << "S ";
       Lys::skrivTilFil(ut);
       ut << ' ' << lengde << ' ' << tykkelse << ' ' << brenneTid
          << ' ' << farge << '\n' << form << '\n';
     }

     virtual void skrivData() const;             //  FERDIGLAGET lengre nede.
};


vector <Lys*>  gLysene;


void endreAntall()  {
  gLysene[lesInt("\tEndre for lys nr", 1, gLysene.size()) - 1]->endreAnt();
}


void nyttLys()  {
  Lys* nyLys;
  char lysType;

  do  {
     lysType = lesChar("\tLystype (P(ære), S(tearin)");
  } while (lysType != 'P' &&  lysType != 'S');

  if (lysType == 'P')  nyLys = new Lyspaere;
  else                 nyLys = new Stearinlys;

  nyLys->lesData();

  gLysene.push_back(nyLys);

  cout << "\n\tNytt lys er lagt inn som nr." << gLysene.size() << '\n';
}


void skrivAlleLys()  {
  int nr = 0;
  if (!gLysene.empty())
     for (const auto & val : gLysene)  {
         cout << '\t' << setw(3) << ++nr << ":  ";
         val->skrivData();
     }
  else
     cout << "\n\tIngen lys er registrert foreløpig!\n\n";
}


void skrivTilFil()  {
  ofstream utfil("EX_V21_2_LYS.DTA");

  cout << "\n\tSkriver alle lys til 'EX_V21_2_LYS.DTA' .....\n";

  utfil << gLysene.size() << '\n';
  for (const auto & val : gLysene)
      val->skrivTilFil(utfil);

  utfil.close();
}


//****************************************************************************
//****************************************************************************
//****************************************************************************

void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tS - Skriv ALLE lysene\n"
         << "\tN - Nytt lys\n"
         << "\tE - Endre antall av et lys\n"
         << "\tQ - Quit / avslutt\n\n";
}


int main()  {
    char valg;

    skrivMeny();
    valg = lesChar("\n\nKommando");

    while (valg != 'Q') {
        switch (valg) {
          case 'S': skrivAlleLys();      break;
          case 'N': nyttLys();           break;
          case 'E': endreAntall();       break;
          default:  skrivMeny();         break;
        }
        valg = lesChar("\n\nKommando");
    }

    skrivTilFil();

    cout << "\n\n";

   return 0;
}


void Lys::skrivData() const  {
  cout << gProdusenter.hentNavn(produsentNr)
       << ",  antall: " << antall << '\n';
}


void Lyspaere::skrivData() const  {
  cout << "Lyspære fra    ";
  Lys::skrivData();
  cout << "\t\t" << (tynnSokkel ? "Tynn" : "Tykk") << " sokkel,  "
       << (LED ? "LED" : "vanlig") << ",  " << (klartGlass ? "klart" : "matt")
       << " glass,  " << watt << " watt\n";
}

void Stearinlys::skrivData() const  {
  cout << "Stearinlys fra ";
  Lys::skrivData();
  cout << "\t\tLengde: " << lengde << " cm,   tykkelse: " << tykkelse
       << " cm,   ca. brennetid: " << brenneTid << " timer,   farge: "
       << farge << ",   form: " << form << '\n';
}
