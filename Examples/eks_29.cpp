/**
 *   Programeksempel nr 29 - Større programeksempel.
 *
 *   Eksemplet viser bruken av svært mye av det TOTALE pensumet i emnet.
 *   Bl.a vises:  pekere, objekter, arv, virtueller, filhåndtering, string,
 *                <list>, <algorithm> og lambda-funksjoner.
 *   Eksemplet viser NIVÅET og OMFANGET på en eksamensoppgave.
 *   (Eksemplet er sterkt basert på eksamen 5.januar 2012 i tidligere IMT1082)
 *
 *   Programmet holder orden på ulike typer gjenstander (malerier, møbler
 *   og ting). Alle disse (arvede objektene) ligger i en og samme <list>.
 *   NB: Tillater duplikate/likenavnede gjenstander i lista!
 *       (Noe hadde da antagelig vært enklere ved å bruke <multimap>,
 *       men dette har vi hverken brukt eller lært noe om i dette emnet.)
 *
 *   Det er mulig å:
 *      - Skrive alt om:  - alle gjenstandene
 *      -                 - gjenstand(er) med et gitt navn
 *      -                 - gjenstander av en viss type/kategori
 *      - Legge inn en ny (subklasse av en) gjenstand
 *      - Slette/fjerne ALLE gjenstander med et gitt navn
 *      - Skrive hele datastrukturen TIL fil
 *      - Lese hele datastrukturen FRA fil
 *
 *   @file     EKS_29.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <list>                    //  list
#include <algorithm>               //  find_if, for_each, count_if
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int    MINAAR = 1500;        ///<  Gjenstand ikke eldre enn dette.
const int    MAXAAR = 2030;        ///<  Gjenstand ikke yngre enn dette.
const int    MINANT = 1;           ///<  Min. antall av en 'Ting'.
const int    MAXANT = 100;         ///<  Max. antall av en 'Ting'.
const float  MINSUM = 1.0;         ///<  Min. verdi/betalt for en gjenstand.
const float  MAXSUM = 200000.0;    ///<  Max. verdi/betalt for en gjenstand.


/**
 *  Type (av gjenstand som:  ikke-satt,  maleri,  møbel  eller  ting).
 */
enum  Type { ikkeSatt, maleri, mobel, ting };


/**
 *  Gjenstand (med navn, ca årstall, antatt verdi og hva betalt for den).
 */
class Gjenstand  {
  private:
    string  navn;                  //  Navnet.
    int     aar;                   //  Gjenstanden er fra dette ca. året.
    float   verdi, betalt;         //  Dens antatte ca. verdi og kjøpesum.
  protected:
    Type  type;                    //  Brukes/settes primært av subklassene.

  public:
    Gjenstand(string nvn);
    Gjenstand(ifstream & inn);
//  ALLE klasser uten DESTRUCTOR, da ingen medlemsfunksjoner bruker 'new'.

    string  hentID() const  {  return navn;  }
    bool    erAvType(const Type type) const  {  return (this->type == type); }

    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Maleri (med kunstnerens navn).
 */
class Maleri : public Gjenstand {
  private:
    string kunstner;
  public:
    Maleri(string nvn);
    Maleri(ifstream & inn);
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Mobel (med beskrivelse av møbelet).
 */
class Mobel : public Gjenstand {
  private:
    string beskrivelse;
  public:
    Mobel(string nvn);
    Mobel(ifstream & inn);
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Ting (med tingens stoff/materiale, og antallet man har av den).
 */
class Ting : public Gjenstand {
  private:                    //  Stoffet/materialet tingen er laget av:
    string stoff;             //     porselen, krystall, stål, jern,...
    int    antall;

  public:
    Ting(string nvn);
    Ting(ifstream & inn);
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


Type lesType();
void lesFraFil();
void nyGjenstand();
void skrivAlle();
void skrivAlleAvType();
void skrivAlleMedNavn();
void skrivMeny();
void skrivTilFil();
void slettGjenstand();


list <Gjenstand*> gGjenstandene;   ///<  Liste med ALLE de ulike gjenstandene.


/**
 *  Hovedprogrammet:
 */
int main() {           //  HOVEDPROGRAM:
    char valg;

    lesFraFil();

    skrivMeny();
    valg = lesChar("\n\nKommando");
    while (valg != 'Q') {
        switch (valg) {
          case 'A': skrivAlle();            break;
          case 'M': skrivAlleMedNavn();     break;
          case 'T': skrivAlleAvType();      break;
          case 'N': nyGjenstand();          break;
          case 'S': slettGjenstand();       break;
          default:  skrivMeny();            break;
        }
        valg = lesChar("\n\nKommando");
    }

    skrivTilFil();

//  slettHeleListen();          - ikke kodet/laget (da litt unødvendig)

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Initierer datamedlemmene.
 *
 *  @param    nvn  - Gjenstandens navn
 */
Gjenstand::Gjenstand(string nvn)  {
  navn = nvn;                                   //  Lagrer unna medsendt navn.
  type = ikkeSatt;   aar = verdi = betalt = 0;  //  Initierer/nullstiller.
}


/**
 *  Leser datamedlemmene fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra
 */
Gjenstand::Gjenstand(ifstream & inn)  {
    type = ikkeSatt;                         //  Setter foreløpig verdi.
    getline(inn, navn);                      //  Leser gjenstandens navn.
    inn >> aar >> verdi >> betalt;           //  Leser datamedlemmer fra fil.
    inn.ignore();                            //  Forkaster avsluttende '\n'.
}


/**
 *  Leser inn de ulike datamedlemmene fra brukeren/tastaturet.
 */
void Gjenstand::lesData()  {
  aar = lesInt("\tÅr", MINAAR, MAXAAR);
  verdi = lesFloat("\tVerdi", MINSUM, MAXSUM);
  betalt = lesFloat("\tBetalt", MINSUM, MAXSUM);
}


/**
 *  Skriver ALLE klassens data ut på skjermen.
 */
void Gjenstand::skrivData() const {
    cout << '\t' << navn << "\n\t\t"
         << "År: " << aar << "\tVerdi kr." << verdi
         << "\t  Betalt kr." << betalt << '\n';
}


/**
 *  Skriver ALLE datamedlemmer ut på fil.
 *
 *  @param    ut  -  Filobjektet det skrives ut til
 */
void Gjenstand::skrivTilFil(ofstream & ut) const  {
    ut << navn << '\n' << aar << ' ' << verdi << ' ' << betalt << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Initierer datamedlemmet.
 *
 *  @param    nvn  - Gjenstandens navn - sendes til baseklassens constructor
 */
Maleri::Maleri(string nvn) : Gjenstand(nvn) {
    type = maleri;                           //  Setter aktuell subklassetype.
}


/**
 *  Leser datamedlemmene fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra
 */
Maleri::Maleri(ifstream & inn) : Gjenstand(inn) {
    type = maleri;                           //  Setter aktuell subklassetype.
    getline(inn, kunstner);                  //  Leser datamedlemmet fra fil.
}


/**
 *  Leser inn de ulike datamedlemmene fra brukeren/tastaturet.
 */
void Maleri::lesData() {
    Gjenstand::lesData();
    cout << "\tKunstner:  ";  getline(cin, kunstner); // Leser kunstnernavnet:
}


/**
 *  Skriver ALLE klassens data ut på skjermen.
 */
void Maleri::skrivData() const  {
    cout << "\n\tMALERI:";
    Gjenstand::skrivData();                  //  Skriver/displayer "mors"
    cout << "\t\tKunstner: " << kunstner << '\n';  //  og egne data:
}


/**
 *  Skriver ALLE datamedlemmer ut på fil.
 *
 *  @param    ut  -  Filobjektet det skrives ut til
 */
void Maleri::skrivTilFil(ofstream & ut) const  {
    ut << "A ";                                  //  'A' for "mAleri".
    Gjenstand::skrivTilFil(ut);
    ut << kunstner << '\n';
}


// ---------------------------------------------------------------------------


/*
 *  Initierer datamedlemmet.
 *
 *  @param    nvn  - Gjenstandens navn - sendes til baseklassens constructor
 */
Mobel::Mobel(string nvn) : Gjenstand(nvn) {
    type = mobel;                            //  Setter aktuell subklassetype.
}


/**
 *  Leser datamedlemmene fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra
 */
Mobel::Mobel(ifstream & inn) : Gjenstand(inn) {
    type = mobel;                            //  Setter aktuell subklassetype.
    getline(inn, beskrivelse);               //  Leser datamedlemmet fra fil.
}


/**
 *  Leser inn de ulike datamedlemmene fra brukeren/tastaturet.
 */
void Mobel::lesData() {
    Gjenstand::lesData();
    cout << "\tBeskrivelse:  ";
    getline(cin, beskrivelse);               //  Leser beskrivelsen.
}


/**
 *  Skriver ALLE klassens data ut på skjermen.
 */
void Mobel::skrivData() const  {
    cout << "\n\tMØBEL:";
    Gjenstand::skrivData();                  //  Skriver/displayer "mors"
    cout << "\t\tBeskrivelse: " << beskrivelse << '\n';   //  og egne data:
}


/**
 *  Skriver ALLE datamedlemmer ut på fil.
 *
 *  @param    ut  -  Filobjektet det skrives ut til
 */
void Mobel::skrivTilFil(ofstream  & ut) const  {
    ut << "O ";                                  //  'O' for "mObel".
    Gjenstand::skrivTilFil(ut);
    ut << beskrivelse << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Initierer datamedlemmene.
 *
 *  @param    nvn  - Gjenstandens navn - sendes til baseklassens constructor
 */
Ting::Ting(string nvn) : Gjenstand(nvn) {
    type = ting;                        //  Setter aktuell subklassetype.
    antall = 0;                         //  Setter foreløpig antall av tingen.
}


/**
 *  Leser datamedlemmene fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra
 */
Ting::Ting(ifstream & inn) : Gjenstand(inn) {
    type = ting;                             //  Setter aktuell subklassetype.
    inn >> antall;  inn.ignore();            //  Leser datamedlemmer fra fil:
    getline(inn, stoff);
}


/**
 *  Leser inn de ulike datamedlemmene fra brukeren/tastaturet.
 */
void Ting::lesData() {
    Gjenstand::lesData();
    cout << "\tStoff:  ";  getline(cin, stoff);     //  Leser stoff og antall:
    antall = lesInt("\tAntall", MINANT, MAXANT);
}


/**
 *  Skriver ALLE klassens data ut på skjermen.
 */
void Ting::skrivData() const  {
    cout << "\n\tTING:";                     //  Skriver/displayer "mors"
    Gjenstand::skrivData();                  //    egne data:
    cout << "\t\tAntall: " << antall << "\tStoff: " << stoff << '\n';
}


/**
 *  Skriver ALLE datamedlemmer ut på fil.
 *
 *  @param    ut  -  Filobjektet det skrives ut til
 */
void Ting::skrivTilFil(ofstream & ut) const  {
    ut << "T ";                                  //  'T' for "Ting".
    Gjenstand::skrivTilFil(ut);
    ut << antall << ' ' << stoff << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Leser og returnerer lovlig type gjenstand (enum).
 *
 *  return   Enum-verdi (maleri, mobel, ting) for en aktuell gjenstand
 */
Type lesType()  {
    char tegn;

    do                          //  Leser ALLTID  'A', 'O' eller 'T':
       tegn = lesChar("\tGjenstand-type (m)A(leri), (m)O(bel), T(ing)");
    while (tegn != 'A'  &&  tegn != 'O'  &&  tegn != 'T');

    switch (tegn) {             //  Gjør om til og returnerer aktuell type:
      case 'A':  return maleri;
      case 'O':  return mobel;
      case 'T':  return ting;
    }
    return ikkeSatt;            //  Skal ALDRI kunne skje (da sikrer(?!!!)
}                               //    ovenfor at ER BARE 'A', 'O' eller 'T').


/**
 *  Leser ALLE gjenstander (maleri, møbel og ting) inn fra fil.
 *
 *  @see   Maleri::Maleri(...)
 *  @see   Mobel::Mobel(...)
 *  @see   Ting::Ting(...)
 *  @see   Gjenstand::hentID()
 */
void lesFraFil()  {
   ifstream innfil("EKS_29_GJENSTANDER.DTA");
   Gjenstand* nyGjenstand = nullptr;
   char type = ' ';                          //  'A', 'O' eller 'T'.

   if (innfil) {                             //  Filen finnes:
      cout << "\n\n\tLeser fra filen 'EKS_29_GJENSTANDER.DTA'......\n\n";
      innfil >> type;                        //  Leser om mulig 'A', 'O', 'T'.
      while (!innfil.eof()) {                //  Ennå ikke fil-slutt:
         innfil.ignore();                    //  Skipper ' ' (EN blank).
         switch (type) {                     //  Aktuell ny lages:
           case 'A': nyGjenstand = new Maleri(innfil);   break;
           case 'O': nyGjenstand = new Mobel(innfil);    break;
           case 'T': nyGjenstand = new Ting(innfil);     break;
         }
         gGjenstandene.push_back(nyGjenstand);    //  Legges BAKERST i listen.

         innfil >> type;                     //  Leser om mulig 'A', 'O', 'T'.
      }
                                             //  SORTERER! - etter navn:
      gGjenstandene.sort([](const Gjenstand* g1, const Gjenstand* g2)
                           {  return (g1->hentID() < g2->hentID());  });

      innfil.close();                        //  Lukker filen manuelt.
   } else                                    //  Filen finnes IKKE:
       cout << "\n\n\tFant ikke filen 'EKS_29_GJENSTANDER.DTA'!\n\n";
}


/**
 *  Legg inn en ny gjenstand (Maleri, Mobel eller Ting).
 *
 *  @see   Maleri::Maleri(...)
 *  @see   Mobel::Mobel(...)
 *  @see   Ting::Ting(...)
 *  @see   virtual Gjenstand::lesData()
 *  @see   Gjenstand::hentID()
 */
void nyGjenstand()  {
    Gjenstand* nyGjenstand = nullptr;      //  Peker til nytt objekt.
    string nvn;                            //  Ny gjenstands navn.
    const Type type = lesType();           //  Ønsket subklasse-objekt.

    cout << "\tNy gjenstands navn:  ";   getline(cin, nvn);

    switch (type) {                        //  Aktuell ny lages:
      case maleri: nyGjenstand = new Maleri(nvn);   break;
      case mobel:  nyGjenstand = new Mobel(nvn);    break;
      case ting:   nyGjenstand = new Ting(nvn);     break;
    }

    nyGjenstand->lesData();                //  Leser selv egne data.

    gGjenstandene.push_back(nyGjenstand);  //  Legges BAKERST i listen.
                                           //  SORTERER! - etter navn:
    gGjenstandene.sort([](const Gjenstand* g1, const Gjenstand* g2)
                         {  return (g1->hentID() < g2->hentID());  });
}


/**
 *  Skriver ut HELE listens innhold på skjermen.
 *
 *  @see   virtual Gjenstand::skrivData()
 */
void skrivAlle() {
    for (const auto & val : gGjenstandene)
        val->skrivData();           //  Burde stanse for hver 5.(jfr EKS_28).

//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//  for_each(gGjenstandene.begin(), gGjenstandene.end(),
//          [] (const auto & val) { val->skrivData();  } );

    cout << "\n\tAntall gjenstander:  " << gGjenstandene.size() << '\n';
}



/**
 *  Skriver ALT om ALLE gjenstander av en gitt type.
 *
 *  @see   Gjenstand::erAvType(...)
 *  @see   virtual Gjenstand::skrivData()
 */
void skrivAlleAvType()  {
    int antall = 0;                 //  Antall objekter skrevet ut/funnet.
    const Type type = lesType();    //  KAN være 'const' da initieres ved,
                                    //     opprettelse, og endres aldri igjen!

    for (const auto & val : gGjenstandene)      //  Går gjennom hele listen:
        if (val->erAvType(type))  {
            antall++;                           //  Teller opp antall treff.
            val->skrivData();                   //  Skriver objektets data.
        }

    cout << "\n\tAntall gjenstander av denne typen:  " << antall << '\n';
}


/**
 *  Skriver ALT om ALLE med samme navn.
 *
 *  @see   Gjenstand::hentID()
 *  @see   virtual Gjenstand::skrivData()
 */
void skrivAlleMedNavn()  {
    string nvn;                    //  Navn til gjenstand(er) å skrive ALT om.
    int antall = 0;                //  Antall objekter skrevet ut/funnet.
                                   //  Leser gjenstanden(e)s navn.
    cout << "\tSe ALT om gjenstanden:  ";   getline(cin, nvn);

    for (const auto & val : gGjenstandene)      //  Går gjennom hele listen:
        if (val->hentID() == nvn)  {            //  HAR navnet:
            antall++;                           //  Teller opp antall treff.
            val->skrivData();                   //  Skriver objektets data.
        }

//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//  for_each(gGjenstandene.begin(), gGjenstandene.end(),
//      [nvn, &antall](const auto & val)
//          { if (val->hentID() == nvn) { antall++;   val->skrivData(); }  });


//  Alternativt vha. iterator, 'find_if(...)' og lambda-funksjon:
//  auto it = find_if(gGjenstandene.begin(), gGjenstandene.end(),
//                 [nvn](const auto & val) { return(val->hentID() == nvn); });
//  while (it != gGjenstandene.end()) {       //  Så lenge funn:
//      antall++;
//      (*it)->skrivData();
//      it = find_if(++it, gGjenstandene.end(),  // MEGET viktig med '++' !!!
//                [nvn](const auto & val) { return(val->hentID() == nvn); });
//    }

    cout << "\n\tAntall gjenstander med dette navnet:  " << antall << '\n';
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
   cout << "\nFølgende kommandoer er tilgjengelige:\n"
        << "\n   A  - skriv Alle gjenstandene"
        << "\n   M  - skriv alt om gjenstand(er) Med et gitt navn"
        << "\n   T  - skriv gjenstander av en viss Type (maleri, møbel, ting)"
        << "\n   N  - Ny gjenstand"
        << "\n   S  - Slette/fjerne alle gjenstander med et gitt navn"
        << "\n   Q  - Quit / avslutt";
}


/**
 *  Skriver ALLE Gjenstander (maleri, møbel og ting) ut til fil.
 *
 *  @see   virtual Gjenstand::skrivTilFil(...)
 */
void skrivTilFil()  {
    ofstream utfil("EKS_29_GJENSTANDER.DT2");

    cout << "\n\n\tSkriver til filen 'EKS_29_GJENSTANDER.DT2'......\n\n";

    for (const auto & val : gGjenstandene)      //  Går gjennom hele listen:
        val->skrivTilFil(utfil);                //  Skriver objektet til fil.

// Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gGjenstandene.begin(), gGjenstandene.end(),
//             [&utfil] (const auto & val) { val->skrivTilFil(utfil);  } );
    utfil.close();                              //  Lukker filen manuelt.
}


/**
 *  Sletter/fjerner ALLE gjenstand(er) med et gitt navn.
 *
 *  @see   Gjenstand::hentID()
 */
void slettGjenstand() {
    string nvn;                           //  Navn til gjenstand(er) å slette.
    int  antall = 0;                      //  Antall gjenstander med navnet.

    cout << "\tSlette/fjerne ALLE gjenstand(er) med navnet:  ";
    getline(cin, nvn);
                                          //  FINNER ANTALLET MED NAVNET:
    antall = count_if(gGjenstandene.begin(), gGjenstandene.end(),
                  [nvn](const auto & val) { return (val->hentID() == nvn); });

    cout << "\n\tDet er " << antall << " gjenstand(er) med dette navnet.\n";

    if (antall > 0) {                        //  Gjenstand(er) ble funnet:
        cout << "\n\tØnsker du VIRKELIG å slette/fjerne "
             << ((antall > 1) ? "ALLE disse" : "denne");
        if (lesChar(" (j/N)") == 'J') {      //  VIL slette alle:
                              //  Aktuelle PEKERE slettes (memorylekkasje!!!):
            gGjenstandene.remove_if([nvn](const auto & val)  //
                                         { return (val->hentID() == nvn); });
            cout << "\n\t" << antall << " gjenstander er slettet!"
                 << "\n\tDet er nå " << gGjenstandene.size()
                 << " gjenstander tilbake i listen.\n";
        }  else
            cout << "\n\tOK - ingen gjenstand har blitt slettet.\n";
    }


    //  Øving/oppgave:
    //
    //      1)  Skriv om slik at memory-lekkasjen ikke skjer rett ovenfor.
    //
    //      2)  IKKE la ALLE med et gitt navn slettes kollektivt,
    //          men brukeren bestemmer individuelt om hvilke som skal slettes.
    //          Hint:  "Manuell" bruk av iteratorer må nok påregnes.....
}
