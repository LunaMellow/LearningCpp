/**
 *   Skjelett for til konteeksamen i OOProg (i C++), august 2023, oppgave 2.
 *
 *   Programmet holder orden på ulikt militært personell sine
 *   tatte (ferdighets)merker.
 *
 *   Programmet:
 *      - inneholder:  EN <map> med navn og pekere til 'Personell'-objekter
 *      -              'Personell' som bl.a. inneholder vedkommendes merker
 *      - lar brukeren legge inn:  ET nytt personell (med alle sine data)
 *      -                          ET nytt merke (automatisk) hos et personell
 *      - skriver at ALT personell  eller  ALT om ETT personell
 *      - leser HELE datastrukturen fra fil
 *
 *   @file     EX_S23_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream
#include <string>
#include <vector>
#include <map>
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const float MINPOENG =     1,      ///<  Minimum antall poeng å få.
            MAXPOENG = 10000;      ///<  Maksimum antall poeng å få.
const int   MINTIME  =     0,      ///<  Minimum time brukt. 
            MAXTIME  =    10;      ///<  Maksimum time brukt.


/**
 *  Valor (merkenes ulike valører: Bronse, Sølv eller Gull).
 */
enum Valor {  Bronse,  Solv,  Gull  };


class Merke;                      //  PRE-deklarasjon, da 'Personell' henviser
                                  //    til 'Merke' som defineres lengre nede.


/**
 *  Personell (med fornavn, miltær grad og tjenestested).
 */
class Personell {
  private:                         //  'etternavn' er 'first' i map'en.
    string fornavn,
           grad,                   //  Militær grad.
           sted;                   //  Tjenestested.
    vector <Merke*> merkene;       //  Alle merkene totalt tatt.

   int antallMerker(const string tittel, const Valor valor) const;  // Oppg.2G
   Merke* lagMerke(const char type, const string t, const Valor v); // Oppg.2C
   Valor  lesValor() const;                   //  (Ferdiglaget nedenfor)

  public:
    Personell()  {    }
    Personell(ifstream & inn);                //  Oppgave 2I
    void lesData();                           //  Oppgave 2A
    void nyttMerke();                         //  Oppgave 2E  og  2H
    void skrivHovedData() const;              //  Oppgave 2B
    void skrivAlleData() const;               //  Oppgave 2F
};


/**
 *  Merke (med tittel/beskrivelse, dato tatt og merkets valør).
 */
class Merke {
  private:
    string tittel;                //  Tittel/beskrivelse av merket.
    int    dato;                  //  På formen:  ÅÅMMDD   (år-måned-dag).
    Valor  valor;                 //  Merkets valør:  Bronse, Solv eller Gull.

  public:
    Merke(const string t, const Valor v)  {  tittel = t;  valor = v; }
    Merke(ifstream & inn);                    //  Oppgave 2I
    string hentTittel()  {  return tittel;  }
    Valor  hentValor()   {  return valor;   }
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


/**
 *  PoengMerke (med poengene oppnådd ifm. merketagelsen).
 */
class PoengMerke : public Merke {
  private:
    float  poeng;

  public:
    PoengMerke(const string t, const Valor v) : Merke(t, v)  {  }
    PoengMerke(ifstream & inn);               //  Oppgave 2I
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


/**
 *  TidMerke (tiden brukt ifm. merketagelsen).
 */
class TidMerke : public Merke {
  private:
    int tid;             //  Tid i hele sekunder (= time*3600 + min*60 + sek).

  public:
    TidMerke(const string t, const Valor v) : Merke(t, v)  {  }
    TidMerke(ifstream & inn);                 //  Oppgave 2I
    virtual void lesData();                   //  Oppgave 2E
    virtual void skrivData() const;           //  Oppgave 2F
};


void  lesFraFil();                             //  Oppgave 2I
void  nyttMerke();                             //  Oppgave 2D
void  nyttPersonell();                         //  Oppgave 2A
void  skrivAltOmEttPersonell();                //  Oppgave 2F
void  skrivAltPersonell();                     //  Oppgave 2B
void  skrivMeny();


map <string, Personell*> gPersonellet;     ///<  ALT personell som tar merker.


/**
 *  Hovedprogrammet.
 */
int main() {
  char valg;

  lesFraFil();                                        //  Oppgave 2I

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'P':  nyttPersonell();            break;  //  Oppgave 2A
       case 'A':  skrivAltPersonell();        break;  //  Oppgave 2B
       case 'M':  nyttMerke();                break;  //  Oppgave 2D
       case 'E':  skrivAltOmEttPersonell();   break;  //  Oppgave 2F
       default:   skrivMeny();                break;
     }
     valg = lesChar("\nKommando");
  }

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 *   @see      PoengMerke::PoengMerke(...)
 *   @see      TidMerke::TidMerke(...)
 */
Personell::Personell(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2G - Finner og returnerer antallet av et gitt merke.
 *
 *   @param    tittel  -  Merkets tittel/navn/beskrivelse
 *   @param    valor   -  Merkets valør (Bronse, Solv, Gull)
 *   @return   Antall merker med EKSAKT 'tittel' OG 'valor'
 *   @see      Merke::hentTittel()
 *   @see      Merke::hentValor()
 */
int Personell::antallMerker(const string tittel, const Valor valor) const  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2C - Oppretter og returnerer et aktuelt merke.
 *
 *   @param    type  -  Aktuell merketype ('P/T') å lage nytt merke av
 *   @param    t     -  Merkets tittel/navn/beskrivelse
 *   @param    v     -  Merkets valør (Bronse, Solv, Gull)
 *   @return   Peker til nyopprettet aktuelt merke
 *   @see      PoengMerke::PoengMerke(...)
 *   @see      TidMerke::TidMerke(...)
 */
Merke* Personell::lagMerke(const char type, const string t, const Valor v) {

    //   LAG INNMATEN
}



/**
 *  Oppgave 2A - Leser inn ALLE egne data fra tastaturet.
 */
void Personell::lesData()  {

    //   LAG INNMATEN
}


/**
 *   Leser inn og returnerer valør for ett merke.
 *
 *   @return   Merkevalør (Bronse, Solv, Gull)
 */
Valor Personell::lesValor() const  {
  char tegn;

  do  {
     tegn = lesChar("\tValor (B(ronse), S(olv), G(ull))"); //  Leser og sikrer
  } while (tegn != 'B'  &&  tegn != 'S'  &&  tegn != 'G'); //    lovlig tegn.

  switch (tegn)  {
    case 'B':   return Bronse;                 //  Returnerer aktuell merke-
    case 'S':   return Solv;                   //    valør ut fra tegnet.
    case 'G':   return Gull;
  }
}


/**
 *   Oppgave 2E -  Legger inn ett nytt merke (versjon 1).
 *
 *   @see      skrivAlleData()
 *   @see      lesValor()
 *   @see      lagMerke(...)
 *   @see      Merke::lesData()
 *   @see      Merke::skrivData()
 */
void Personell::nyttMerke()  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2H - Legger inn ett nytt merke (versjon 2).
 *
 *   @see   skrivAlleData()
 *   @see   antallMerker(...)
 *   @see   lagMerke(...)
 *   @see   Merke::lesData()
 *   @see   Merke::skrivData()
 */
void Personell::nyttMerke2()  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2B - Skriver alle egne HOVEDdata ut på skjermen.
 */
void Personell::skrivHovedData() const  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2F - Skriver ALLE egne data ut på skjermen.
 *
 *   @see   skrivHovedData()
 *   @see   Merke::skrivData()
 */
void Personell::skrivAlleData() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
Merke::Merke(ifstream & inn)  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void Merke::lesData()  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2F - Skriver ALLE egne data ut på skjermen.
 */
void Merke::skrivData() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
PoengMerke::PoengMerke(ifstream & inn) : Merke(inn)  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *   @see   Merke::lesData()
 */
void PoengMerke::lesData()  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2F - Skriver ALLE egne (og baseklassens) data ut på skjermen.
 *
 *   @see   Merke::skrivData()
 */
void PoengMerke::skrivData() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------

/**
 *   Oppgave 2I - Leser inn ALLE egne data fra fil.
 *
 *   @param    inn  -  Filobjektet det leses inn data fra
 */
TidMerke::TidMerke(ifstream & inn) : Merke(inn)  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *   @see   Merke::lesData()
 */
void TidMerke::lesData()  {

    //   LAG INNMATEN
}


/**
 *   Oppgave 2F - Skriver ALLE egne (og baseklassens) data ut på skjermen.
 *
 *   @see   Merke::skrivData()
 */
void TidMerke::skrivData() const  {

    //   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2I - Leser ALT personell og ALLE deres merker inn fra fil.
 *
 *  @see   Personell::Personell(...)
 */
void lesFraFil()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2D - Legger inn (om mulig) et nytt merke.
 *
 *  @see   Personell::nyttMerke()
 */
void nyttMerke()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2A - Legger inn (om mulig) et nytt personell.
 *
 *  @see   Personell::Personell()
 *  @see   Personell::lesData()
 */
void nyttPersonell()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ut ALT om ETT personell.
 *
 *  @see   Personell::skrivAlleData()
 */
void skrivAltOmEttPersonell()  {

    //   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver ut HOVEDdata om ALT personell.
 *
 *  @see   Personell::skrivHovedData()
 */
void skrivAltPersonell()  {

    //   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   P  - nytt Personell\n"
       << "   A  - skriv ut Alt personellet\n"
       << "   M  - nytt Merke\n"
       << "   E  - skriv ut alt om Ett personell\n"
       << "   S  - statistikk over medaljer\n"
       << "   Q  - Quit / avslutt\n";
}
