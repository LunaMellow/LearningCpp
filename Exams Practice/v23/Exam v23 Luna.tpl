/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2023, oppgave 2.
 *
 *   Programmet holder orden på en persons lunsj- og middagsbesøk på
 *   ulike spisesteder/kafeer/restauranter.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Spisesteder'-objekter.
 *      - skriver ut ALLE spisesteder, eller ALT om ETT spiested
 *      - legger inn et nytt spisested eller måltid
 *      - skriver alle måltider spist på en gitt dato
 *      - frigir alt allokert minne
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V23_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>
#include <list>
#include <map>
#include <algorithm>               //  find_if, for_each
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


class Maaltid;                     //  Pre-deklarasjon.


/**
 *  Spisested (navn, adresse, telefon og ALLE måltidene spist der).
 */
class Spisested {
  private:
    string navn,                     //  UNIKT navn - sortert på dette.
           adresse,
           tlf;                      //  'tlf' er string, da også KAN
                                     //    inneholde '+', landskode og blanke.
    map <int, Maaltid*> maaltidene;  //  'int' er dato på formatet: MMDD
                                     //    og er UNIKT for hvert spisested.
  public:
    Spisested(const string nvn)  {  navn = nvn;  }      //       (Ferdiglaget)
    Spisested(ifstream & inn);                          //  Oppgave 2I
    ~Spisested();                                       //  Oppgave 2H
    Maaltid* finnMaaltidPaaDato(const int dato) const;  //  Oppgave 2E
    string hentID() const  { return navn; }             //       (Ferdiglaget)
    void lesData();                                     //  Oppgave 2D
    void nyttMaaltid();                                 //  Oppgave 2F
    void skrivAlleData()  const;                        //  Oppgave 2C
    void skrivHovedData() const;                        //  Oppgave 2A
};


/**
 *  Baseklassen Maaltid (kun med navnet på måltidets hovedrett).
 */
class Maaltid  {
  protected:
    string hovedrett;         //  Tekst (lunsj/middag) eller blank (middag).

  public:
    Maaltid()  {  }
    Maaltid(ifstream & inn);                            //  Oppgave 2I
    virtual ~Maaltid()  {  }
    virtual void lesData() = 0;             //  = 0 betyr 'pure virtual',
    virtual void skrivData() const = 0;     //    dvs. subklasser MÅ lage dem.
};


/**
 *  Avledet klasse Lunsj (kun med om har drukket kaffe eller ei til lunsj).
 */
class Lunsj : public Maaltid  {
  private:
    bool kaffe;               //  Drikker evt. KUN vann i tillegg (til lunsj).

  public:
    Lunsj()  {  }
    Lunsj(ifstream & inn);                              //  Oppgave 2I
    virtual ~Lunsj()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
};


/**
 *  Avledet klasse Middag (med evt navn på forrett, dessert og/eller drikken).
 */
class Middag: public Maaltid  {
  private:
    string forrett,           //  Tekst eller blank.
           dessert,           //  Tekst eller blank.
           drikke;            //  Tekst eller blank.

  public:
    Middag()  {  }
    Middag(ifstream & inn);                             //  Oppgave 2I
    virtual ~Middag()  {  }
    virtual void lesData();                             //  Oppgave 2F
    virtual void skrivData() const;                     //  Oppgave 2C
};


Spisested* finnSpisested(const string navn);  //  Oppgave 2B
void frigiAllokertMinne();                    //  Oppgave 2H
void lesFraFil();                             //  Oppgave 2I
void nyttMaaltid();                           //  Oppgave 2F
void nyttSpisested();                         //  Oppgave 2D
void skrivAlleSpisesteder();                  //  Oppgave 2A
void skrivEttSpisested();                     //  Oppgave 2C
void skrivMeny();
void spistEnGittDato();                       //  Oppgave 2G


list <Spisested*> gSpisestedene;              ///<  ALLE aktuelle spisesteder.


/**
 *  Hovedprogrammet:
 */
int main() {
  char valg;

  lesFraFil();                                     //  Oppgave 2I

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'A': skrivAlleSpisesteder();   break;  //  Oppgave 2A
       case 'E': skrivEttSpisested();      break;  //  Oppgave 2C
       case 'S': nyttSpisested();          break;  //  Oppgave 2D
       case 'M': nyttMaaltid();            break;  //  Oppgave 2F
       case 'D': spistEnGittDato();        break;  //  Oppgave 2G
       default:  skrivMeny();              break;
     }
     valg = lesChar("\nKommando");
  }

  frigiAllokertMinne();                            //  Oppgave 2H

  cout << "\n\n";
  return 0;
}


/**
 *  Oppgave 2I - Leser inn fra fil ALT om ETT spisested.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Spisested::Spisested(ifstream & inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2H - Sletter/fjerner ALLE data inni ETT spisested.
 */
Spisested::~Spisested()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2E - Finner og returnerer (om mulig) 'Maaltid' på en gitt dato.
 *
 *  @param    dato  -  Datoen det ønskes å finne et måltid på
 *  @return   Måltidet på gitt dato, evt. nullptr (om ingen dato-match)
 */
Maaltid* Spisested::finnMaaltidPaaDato(const int dato) const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2D - Leser inn spisestedets resterende enkelt-datamedlemmer.
 */
void Spisested::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Legger inn (om mulig) nytt måltid på en ny dato.
 */
void Spisested::nyttMaaltid()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT spisested.
 */
void Spisested::skrivAlleData() const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut på skjermen enkelt-datamedlemmene.
 */
void Spisested::skrivHovedData() const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2I - Leser inn 'Maaltid'ets eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Maaltid::Maaltid(ifstream & inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2I - Leser inn fra fil 'Lunsj' sitt eneste datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Lunsj::Lunsj(ifstream & inn) : Maaltid(inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Leser inn (hoved)retten under lunsjen.
 */
void Lunsj::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Lunsj::skrivData() const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2I - Leser inn fra fil 'Middag' sine tre datamedlem.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Middag::Middag(ifstream & inn) : Maaltid(inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Leser inn evt rettene og drikken under middagen.
 */
void Middag::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE datamedlemmene.
 */
void Middag::skrivData() const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2B- Finner og returnerer (om mulig) peker til et gitt spisested.
 *
 *  @param    navn  -  Navnet på det søkte spisestedet
 *  @return   Peker til aktuelt navngitt spisested eller nullptr
 */
Spisested* finnSpisested(const string navn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2H - Frigir/sletter ALT allokert minne/memory.
 */
void frigiAllokertMinne()  {

	//   LAG INNMATEN
}



/**
 *  Oppgave 2I - Leser ALLE spisestedene med måltider inn fra fil.
 */
void lesFraFil()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Legger inn (om mulig) ett nytt måltid på et spisested.
 */
void nyttMaaltid()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2D - Legger inn (om mulig) ett nytt spisested.
 */
void nyttSpisested()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut på skjermen HOVEDdataene om ALLE spisesteder.
 */
void skrivAlleSpisesteder()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Skriver ut på skjermen ALLE data om ETT gitt spisested.
 */
void skrivEttSpisested()  {

	//   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFølgende kommandoer er tilgjengelige:\n"
       << "   A  - skriv Alle spisesteder\n"
       << "   E  - skriv Ett spisested\n"
       << "   S  - nytt Spisested\n"
       << "   M  - nytt Maaltid\n"
       << "   D  - steder spist paa en gitt Dato\n"
       << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2G - Skriver ut på skjermen (om mulig) alle måltider spist en
 *               gitt dato, og på hvilket spisested dette har forekommet.
 */
void spistEnGittDato()  {

	//   LAG INNMATEN
}
