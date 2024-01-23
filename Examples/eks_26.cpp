/**
 *   Programeksempel nr 26 - Større programeksempel.
 *
 *   Eksemplet viser bruken av svært mye av det TOTALE pensumet i emnet.
 *   Bl.a vises:  pekere, objekter, arv, virtueller, filhåndtering,
 *                string, lambda-funksjoner, og fra STL:
 *                <vector>, <queue>, <list> og <map>, samt <algorithm>.
 *   Sammen med EKS_28.CPP og EKS_29.CPP vises NIVÅET på en eksamensoppgave
 *   (men dette eksemplet er i OMFANG større).
 *
 *   Programmet:
 *     - håndterer objekter av typene 'Alpinist' og 'Snowboarder'
 *     - inneholder en heiskø (queue), selve skiheisen (queue),
 *       grønn løype (map) og rød løype (list)
 *     - lar objekter flytte seg mellom disse fire ulike containerne
 *     - skriver ut innholdet i de fire containerne
 *     - lar brukeren:   - opprette nye objekter
 *                       - skrive detaljerte data om ETT objekt
 *                       - slette objekter
 *                       - (endre dataene i ETT objekt)
 *     - leser fra og skriver ALLE 4x containerne til fil
 *
 *   @file     EKS_26.CPP
 *   @author   Frode Haug, NTNU
 */

#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector    |
#include <queue>                   //  queue     | (stack det eneste av lærte
#include <list>                    //  list      | containere som IKKE brukes)
#include <map>                     //  map       |
#include <algorithm>               //  algorithm
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


/**
 *  Korttype (med dagskort, helge-/weekendkort og årskort).
 */
enum KortType  {  Dag,  Helg,  Aar };


/**
 *  Operasjon (med å SE en kjørers DETALJERTE data eller å ENDRE dataene).
 */
enum Operasjon {  Detaljer, Endre  };


//  NB:  I hele eksemplet er det brukt 'G' og 'R' for grønn og rød løype.
//       Dette kunne selvsagt, og like naturlig/bra, vært erstattet av 'enum'.


/**
 *  Kjører (med unikt nummer/ID, navn, korttype og kjørte grønne/røde løyper).
 */
class Kjorer {
  private:
      int       nr;
      string    navn;
      KortType  kort;
      vector <char> loyperKjort;

  public:
      Kjorer() { nr = 0; kort = Dag; }    //  Denne constructoren brukes ikke.
      Kjorer(const int nr);
      Kjorer(ifstream & inn);
      virtual ~Kjorer() {  }    //  Tom destructor. Ikke noe å si 'delete' om.

                         //  'hentID' MÅ LAGES I ALLE PROGRAM DER OBJEKTER
                         //   LIGGER I CONTAINERNE <list> (og/eller <map>) !!!
                         //   DENNE RETURNERER KUN KEYEN/DET OBJEKTET SKAL
                         //   SORTERES ETTER:  EN 'int' ELLER EN 'string'.
      int   hentID()    {    return nr;    }
      void  registrerLoype(const char loype);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivDetaljer() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Alpinist (med om har twintip ski eller ei, og tightsdress eller ei).
 */
class Alpinist : public Kjorer {
  private:
    bool twinTipSki,
         tightsDress;
  public:
    Alpinist() { twinTipSki = tightsDress = false; }      //  Brukes ikke her.
    Alpinist(const int nr);
    Alpinist(ifstream & inn);
    virtual ~Alpinist() {  }    //  Tom destructor. Ikke noe å si 'delete' om.
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivDetaljer() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Snowboarder (med om har saggebukse eller ei, og mørk hjelm eller ei).
 */
class Snowboarder : public Kjorer {
  private:
    bool saggeBukse,
         morkHjelm;
  public:
    Snowboarder() {  saggeBukse = morkHjelm = false; }    //  Brukes ikke her.
    Snowboarder(const int nr);
    Snowboarder(ifstream & inn);
    virtual ~Snowboarder() {  }  // Tom destructor. Ikke noe å si 'delete' om.
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivDetaljer() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


void detaljerEllerEndre(const Operasjon operasjon);
Kjorer* finnKjorer(const int nr, char & loype);
void lesFraFil();
void nyKjorer();
void skrivGronn();
void skrivKo(const string & s, queue <Kjorer*> ko);
void skrivMeny();
void skrivQueueTilFil(queue <Kjorer*> ko, ofstream & ut);
void skrivRod();
void skrivTilFil();
void slettAlleData();
void slette();
void tilHeisen();
void tilHeisKo();
void tilLoype(const char loype);


queue <Kjorer*> gHeisKo;       ///<  De som står i heis-kø.
queue <Kjorer*> gHeis;         ///<  De som er (på vei opp) i heisen.
list  <Kjorer*> gRod;          ///<  De som kjører rød løype.
map   <int, Kjorer*> gGronn;   ///<  De som kjører grønn løype.
int   gSisteNummer;            ///<  Nummer for siste registrerte kjører.


/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    lesFraFil();

    skrivMeny();
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'K':    tilHeisKo();                      break;
          case 'H':    tilHeisen();                      break;
          case 'G': case 'R':  tilLoype(kommando);       break;
          case 'N':    nyKjorer();                       break;
          case 'D':    detaljerEllerEndre(Detaljer);     break;
          case 'E':    detaljerEllerEndre(Endre);        break;
          case 'S':    slette();                         break;
          case '1':    skrivKo("heiskø", gHeisKo);       break;
          case '2':    skrivKo("heisen", gHeis);         break;
          case '3':    skrivGronn();                     break;
          case '4':    skrivRod();                       break;
          default:     skrivMeny();                      break;
        }
        kommando = lesChar("Kommando");
    }

    skrivTilFil();

    slettAlleData();

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Setter eget nummer/ID (ut fra parameters verdi).
 *
 *  @param   nr  - kjørerens eget nummer/ID
 */
Kjorer::Kjorer(const int nr) {
    kort = Dag;
    this->nr = nr;                  //  MÅ bruke 'this' om egen verdi, når
}                                   //    parameteren heter EKSAKT det samme.


/**
 *  Leser ALLE egne datamedlemmer inn fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Kjorer::Kjorer(ifstream & inn) {
    char tegn;
    inn >> nr >> tegn;                   //  Leser nummer/ID og 'D/H/A'.
    inn.ignore();                        //  Forkaster ' ' før navnet/tekst.
    switch (tegn)  {                     //  Konverterer bokstav til enum:
      case 'D':  kort = Dag;   break;
      case 'H':  kort = Helg;  break;
      case 'A':  kort = Aar;   break;
    }
    getline(inn, navn);                  //  Leser eget navn.
}


/**
 *  Tilbyr brukeren å endre på aktuelle datamedlemmer.
 */
void Kjorer::endreData() {
    cout << "\n\tEndre datamedlemmer:  IKKE IMPLEMENTERT ENNÅ\n\n";

    //  LATER
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 */
void Kjorer::lesData() {
    char tegn;

    cout << "\tNavn:     ";                //  Leser eget navn:
    getline(cin, navn);

    do {                                   //  Leser ALLTID 'D/H/A':
        tegn = lesChar("\tKorttype (D(ag), H(elg), A(ar)");
    } while (tegn != 'D'  &&  tegn != 'H'  &&  tegn != 'A');

    switch (tegn) {                        //  Konverterer bokstav til enum:
      case 'D':  kort = Dag;    break;
      case 'H':  kort = Helg;   break;
      case 'A':  kort = Aar;    break;
    }
}


/**
 *  Legger til 'G' eller 'A' bakerst i vectoren 'loyperkjort'.
 *
 *  @param   loype  - Løypen kjørt ('G' eller 'R')
 */
void Kjorer::registrerLoype(const char loype) {
    loyperKjort.push_back(loype);        //  Legger ny inn bakerst i vectoren.
}


/**
 *  Skriver ut ALLE egne data på skjermen.
 */
void Kjorer::skrivData() const  {                 //  Skriver nr/ID og navn:
    cout << setw(10) << nr << ":  " << navn << ",  ";
    switch (kort) {                               //  Skriver enum som tekst:
      case Dag:   cout << "dags";    break;
      case Helg:  cout << "helge";   break;
      case Aar:   cout << "års";     break;
    }                                             //  Antall løypeturer:
    cout << "kort,  antall turer: " << loyperKjort.size() << '\n';
}


/**
 *  Teller opp og skriver antall turer i grønn/rød løype, samt turrekkefølgen.
 */
void Kjorer::skrivDetaljer() const {
    int antG = 0, antR = 0;            //  Nullstiller antall turer i løypene.

    cout << "\tLøyper kjørt i dag:\n\t";
    for (const auto val : loyperKjort) {      //  Går gjennom alle turene:
        if (val == 'G') antG++;  else antR++; //  Teller opp antall i G/R.
        cout << ' ' << val;                   //  Skriver 'G' eller 'R'.
    }
    cout << "\n\tAltså: " << antG << " gang(er) i GRØNN, og "
                          << antR << " gang(er) i RØD løype.\n\n";
}


/**
 *  Skriver egne data til fil (untatt 'loyperKjort'!).
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Kjorer::skrivTilFil(ofstream & ut) const {
    ut << ' ' << nr << ' ';                //  Skriver ' ', eget nr/ID og ' '.
    switch (kort) {                        //  Konverterer og skriver
      case Dag:   ut << 'D';    break;     //    enum som bokstav:
      case Helg:  ut << 'H';    break;
      case Aar:   ut << 'A';    break;
    }
    ut << ' ' << navn << '\n';             //  Skriver ' ' og navnet.
}


// ---------------------------------------------------------------------------

/**
 *  Tom constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Kjørerens nummer/ID, som sendes til baseklassen
 */
Alpinist::Alpinist(const int nr) : Kjorer(nr) {
    twinTipSki = tightsDress = false;
}


/**
 *  Leser ALLE egne datamedlemmer inn fra fil (etter at baseklassen har lest).
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Alpinist::Alpinist(ifstream & inn) : Kjorer(inn)  {
    char tegn;
    inn >> tegn;                      //  Leser 2x '+/-', og gjør om til bool:
    twinTipSki = (tegn == '+');
    inn >> tegn;    inn.ignore();
    tightsDress = (tegn == '+');
}


/**
 *  Tilbyr brukeren å endre på aktuelle datamedlemmer.
 *
 *  @see   Kjorer::endreData()
 */
void Alpinist::endreData() {
    Kjorer::endreData();                         //  Baseklassens data endres.

    //  LATER:   Endre datamedlemmer - IKKE IMPLEMENTERT ENNÅ.
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 *
 *  @see   Kjorer::lesData()
 */
void Alpinist::lesData() {
    Kjorer::lesData();                            //  Baseklassens data leses.
    twinTipSki = (lesChar("\tTwintip ski?  (j/N)") == 'J');    //  Egne leses:
    tightsDress = (lesChar("\tTights dress? (j/N)") == 'J');
}


/**
 *  Skriver ut ALLE egne data på skjermen.
 *
 *  @see   Kjorer::skrivData()
 */
void Alpinist::skrivData() const  {
    Kjorer::skrivData();                    //  Baseklassens data skrives.
    cout << "\t\tAlpinist "                 //  Egne booler skrives som tekst:
         << (twinTipSki ? "med " : "uten ") << "Twintip ski og "
         << (tightsDress ? "med " : "uten ") << "Tightsdress\n";
}


/**
 *  Skriver ABSOLUTT ALLE datamedlemmer.
 *
 *  @see   skrivData()
 *  @see   Kjorer::skrivDetaljer()
 */
void Alpinist::skrivDetaljer() const {
    skrivData();                     //  Alle andre datadatamedlemmer skrives.
    Kjorer::skrivDetaljer();         //  Baseklassens detaljer skrives.
}


/**
 *  Skriver egne og baseklassens data til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Kjorer::skrivTilFil(...)
 */
void Alpinist::skrivTilFil(ofstream & ut) const {
    ut << 'A';                              //  Subklasse av typen 'A'.
    Kjorer::skrivTilFil(ut);                //  Baseklassens data skrives.
                                            //  Egne booler skrives som '+/-':
   ut << (twinTipSki ? "+" : "-") << ' ' << (tightsDress ? "+" : "-") << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Tom constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Kjørerens nummer/ID, som sendes til baseklassen
 */
Snowboarder::Snowboarder(const int nr) : Kjorer(nr) {
    saggeBukse = morkHjelm = false;
}


/**
 *  Leser ALLE egne datamedlemmer inn fra fil (etter at baseklassen har lest).
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Snowboarder::Snowboarder(ifstream & inn) : Kjorer(inn)  {
    char tegn;
    inn >> tegn;                      //  Leser 2x '+/-', og gjør om til bool:
    saggeBukse = (tegn == '+');
    inn >> tegn;    inn.ignore();
    morkHjelm = (tegn == '+');
}


/**
 *  Tilbyr brukeren å endre på aktuelle datamedlemmer.
 *
 *  @see   Kjorer::endreData()
 */
void Snowboarder::endreData() {
    Kjorer::endreData();                         //  Baseklassens data endres.

    //  LATER:   Endre datamedlemmer - IKKE IMPLEMENTERT ENNÅ.
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 *
 *  @see   Kjorer::lesData()
 */
void Snowboarder::lesData() {
    Kjorer::lesData();                            //  Baseklassens data leses.
    saggeBukse = (lesChar("\tSaggebukse?  (J/n)") != 'N');     //  Egne leses:
    morkHjelm  = (lesChar("\tMørk hjelm?  (J/n)") != 'N');
}


/**
 *  Skriver ut ALLE egne data på skjermen.
 *
 *  @see   Kjorer::skrivData()
 */
void Snowboarder::skrivData() const  {
    Kjorer::skrivData();                    //  Baseklassens data skrives.
    cout << "\t\tSnowboarder "              //  Egne booler skrives som tekst:
        << (saggeBukse ? "med " : "uten ") << "Saggebukse og "
        << (morkHjelm  ? "med " : "uten ") << "Mørk hjelm\n";
}


/**
 *  Skriver ABSOLUTT ALLE datamedlemmer.
 *
 *  @see   skrivData()
 *  @see   Kjorer::skrivDetaljer()
 */
void Snowboarder::skrivDetaljer() const {
    skrivData();                     //  Alle andre datadatamedlemmer skrives.
    Kjorer::skrivDetaljer();         //  Baseklassens detaljer skrives.
}


/**
 *  Skriver egne og baseklassens data til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Kjorer::skrivTilFil(...)
 */
void Snowboarder::skrivTilFil(ofstream & ut) const {
    ut << 'S';                             //  Subklasse av typen 'S'.
    Kjorer::skrivTilFil(ut);               //  Baseklassens data skrives.
                                           //  Egne booler skrives som '+/-':
    ut << (saggeBukse ? "+" : "-") << ' ' << (morkHjelm ? "+" : "-") << '\n';

}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Skriver ALLE detaljer ELLER endrer data om EN kjører.
 *
 *  @param   operasjon  - 'Detaljer' eller 'Endre' - etter hva som skal gjøres
 *  @see     finnKjorer(...)
 *  @see     virtual Kjorer::skrivDetaljer()
 *  @see     virtual Kjorer::endreData()
 */
void detaljerEllerEndre(const Operasjon operasjon) {
    Kjorer* kjorer = nullptr;    //  Peker til en Kjorer INNI EN CONTAINER !!!
    char loype;                  //  MÅ være med som parameter - brukes ikke.
    int nr;                      //  Ønsket kjørernummer å se/endre.

    if (!gGronn.empty() || !gRod.empty()) {    //  Kjører(e) i MINST en løype:
        nr = lesInt("\tNr", 1, gSisteNummer);  //  Leser ønsket kjørernummer.

        kjorer = finnKjorer(nr, loype);        //  Prøver å finne kjøreren i
                                               //  en av løypene.
        if (kjorer) {                          //  Kjøreren funnet:
            if (operasjon == Detaljer)
                kjorer->skrivDetaljer();       //  Vil se ALLE datadetaljer.
            else
                kjorer->endreData();           //  Vil endre datamedlemmer.
        } else
          cout << "\n\tUkjent nummer i begge løypene!\n\n";
    } else
        cout << "\n\tBegge løypene er tomme!\n\n";
}


/**
 *  Leter etter (og evt. returnerer peker til) en gitt kjører i en av løypene.
 *
 *  NB: LETER IKKE I DE 2x KØENE, DA FOR TUKLETE (OG HELLER IKKE MENINGEN/
 *      POENGET MED EN QUEUE). EI HELLER ER DA ITERATORER TILGJENGELIGE.
 *
 *  @param   nr     -  Kjørernummer det letes etter
 *  @param   loype  -  Evt. funnet i 'G'rønn eller 'R'ød løype (REF.OVERFØRT)
 *  @return  Peker til funnet 'Kjorer' INNI EN AV CONTAINERNE,  evt. 'nullptr'
 *  @see     Kjorer::hentID()
 */
Kjorer* finnKjorer(const int nr, char & loype) {

    auto it1 = gGronn.find(nr);     //  Prøver å finne vha. medlemsfunksjon.
    if (it1 != gGronn.end()) {      //  Funn i GRØNN løype (<map>):
        loype = 'G';                //  Setter om hvor funnet.
        return (it1->second);       //  Returnerer peker til 'Kjorer'.
    }                               //  NB:  En 'Kjorer' er tilpekt av
                                    //       'it1->second' !!!

                                    //  Ingen egen "find"-funksjon i <list>,
                                    //    derfor bruke funksjon i <algorithm>,
                                    //    iteratorer og lambda-funksjon:
                                    //  NB:  Bruken av 'hentID()' !!!
    auto it2 = find_if(gRod.begin(), gRod.end(),
                   [nr] (const auto & val) { return(val->hentID() == nr); } );
    if (it2 != gRod.end()) {        //  Funn i RØD løype (<list>):
        loype = 'R';                //  Setter om hvor funnet.
        return *it2;                //  Retunerer peker til 'Kjorer'.
    }                               //  NB:  'it2' ER SELV EN PEKER.
                                    //       Derfor ville 'return it2' ha vært
                                    //       retur av en peker til en peker.
                                    //       'return *it2' blir derfor korrekt
                                    //       return av en peker til 'Kjorer'.

    loype = '-';                    //  Ikke funnet:
    return nullptr;
}


/**
 *  Leser ALLE kjørere inn fra fil og ALLE legges rett inn i heiskøen.
 */
void lesFraFil() {
    ifstream  innfil("EKS_26.DTA");                 //  Åpner aktuell fil.
    char kjorerType;                                //  'A' eller 'S'.

    if (innfil) {                                   //  Filen funnet:
        cout << "\n\nLeser fra filen 'EKS_26.DTA' .....\n\n";
        innfil >> gSisteNummer;   innfil.ignore();  //  Leser siste nr.brukt.
        innfil >> kjorerType;                       //  Prøver å lese 1.felt.
        while (!innfil.eof()) {       //  Ennå ikke slutt på filen:
            switch (kjorerType) {     //  Lager og legger inn aktuell kjører:
              case 'A': gHeisKo.push(new Alpinist(innfil));            break;
              case 'S': gHeisKo.push(new Snowboarder(innfil));         break;
              default:  cout << "\n\tUlovlig kjørertype på filen!\n";  break;
            }
            innfil >> kjorerType;                   //  Prøver å lese 1.felt.
        }
        innfil.close();                             //  Lukker manuelt filen.
    } else
      cout << "\n\nFant ikke filen 'EKS_26.DTA'!\n\n";
}


/**
 *  Legger/setter inn en ny aktuell kjører i heiskøen.
 *
 *  @see   virtual Kjorer::lesData()
 */
void nyKjorer() {
    Kjorer* nyKjorer = nullptr;              //  Peker til nye aktuell kjører.
    char kjorerType;                         //  'A' eller 'S'.
                                //  Teller opp og skriver nytt unikt kjørernr:
    cout << "\tNy kjører har nr." << ++gSisteNummer << ":\n";

    do {                                     //  Leser ALLTID 'A' eller 'S':
        kjorerType = lesChar("\tA(lpinist) eller S(nowboarder)");
    } while (kjorerType != 'A'  &&  kjorerType != 'S');

    switch (kjorerType) {                    //  Lager en ny aktuell kjører:
       case 'A':  nyKjorer = new Alpinist(gSisteNummer);     break;
       case 'S':  nyKjorer = new Snowboarder(gSisteNummer);  break;
    }

    nyKjorer->lesData();                   //  Leser kjørerens datamedlemmer.
    gHeisKo.push(nyKjorer);                //  Legger inn den nye kjøreren.
}


/**
 *  Skriver ALLE kjørerne i den GRØNNE løypen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void skrivGronn() {
    cout << "\nFølgende " << gGronn.size() << " kjørere er i GRØNN løype:\n";
    for (const auto & val : gGronn)        //  Range-based for-løkke:
        (val.second)->skrivData();         //  Skriver kjørerens data.
                                           //  'val.second' er en PEKER!
//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gGronn.begin(), gGronn.end(),
//                    [] (const auto & val) { (val.second)->skrivData();  } );

    cout << "\n\n";
}


/**
 *  Skriver HELE en køs innhold.
 *
 *  @param   s  - Ledetekst i utskrift
 *  @param   ko - queue-container med Kjorer-pekere (lagret i en 'deque')
 *                NB: Får KOPI av PEKERNE til objektene i køen !!!
 *                    Men de TILPEKTE OBJEKTENE er de SAMME !!!
 *                    Hadde det vært brukt '&', så hadde original-pekerne
 *                    vært brukt - og blitt borte (når det sies 'pop') !!!
 *  @see    virtual Kjorer::skrivData()
 */
void skrivKo(const string & s, queue <Kjorer*> ko) {
    cout << "\nFølgende " << ko.size() << " kjørere er i " << s << ":\n";
    while (!ko.empty()) {               //  Ennå elementer igjen:
        (ko.front())->skrivData();      //  Viser/skriver den 1.TILPEKTE.
        ko.pop();                       //  Tar ut/fjerner den 1.PEKEREN.
    }
    cout << "\n\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tK - inn i heisKø\n"
         << "\tH - fra heiskø til Heisen\n"
         << "\tG - fra heisen til Grønn løype\n"
         << "\tR - fra heisen til Rød løype\n\n"
         << "\tN - Ny kjører\n"
         << "\tD - Detaljer om EN kjører  (KUN mulig når er i en løype)\n"
         << "\tE - Endre en kjører        (KUN mulig når er i en løype)\n"
         << "\tS - Slett/fjern en kjører  (KUN mulig når er i en løype)\n\n"
         << "\t1 - skriv HEISKØ\n"
         << "\t2 - skriv HEISEN\n"
         << "\t3 - skriv GRØNN løype\n"
         << "\t4 - skriv RØD løype\n\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Skriver HELE EN medsendt kø til angitt fil.
 *
 *  @param   ko - queue-container med Kjorer-pekere (lagret i en 'deque').
 *                Se ellers NB-kommentaren ifm 'ko' i 'skrivKo'-funksjonen.
 *  @param   ut - Filobjektet køen skal skrives til
 *  @see     virtual Kjorer::skrivTilFil(...)
 */
void skrivQueueTilFil(queue <Kjorer*> ko, ofstream & ut) {
    while (!ko.empty()) {               //  Ennå elementer igjen:
        (ko.front())->skrivTilFil(ut);  //  Skriver elementet til fil.
        ko.pop();                       //  Tar ut/fjerner den 1.PEKEREN.
    }
}


/**
 *  Skriver ALLE kjørerne i den RØDE løypen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void skrivRod() {
    cout << "\nFølgende " << gRod.size() << " kjørere er i RØD løype:\n";
    for (const auto & val : gRod)             //  Range-based for-løkke:
        val->skrivData();                     //  Skriver kjørerens data.
                                              //  'val' er en PEKER!
//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gRod.begin(), gRod.end(),
//                           [] (const auto & val) { val->skrivData();  } );
    cout << "\n\n";
}


/**
 *  Skriver ALLE 4x containernes innhold/kjørere til EN OG SAMME fil.
 *
 *  @see    skrivQueueTilFil(...)
 *  @see    virtual Kjorer::skrivTilFil(...)
 */
void skrivTilFil() {
    ofstream utfil("EKS_26.DT2");                 //  Åpner aktuell fil.
                                                  //  NB:  'DT2' !
    cout << "\nSkriver til filen 'EKS_26.DT2' .....\n\n";

    utfil << gSisteNummer << '\n';                //  Skriver siste nr. brukt.

    skrivQueueTilFil(gHeis, utfil);               //  Heisens innhold.

    skrivQueueTilFil(gHeisKo, utfil);             //  Heiskøens innhold.

    for_each(gGronn.begin(), gGronn.end(),        //  Grønn løypes innhold:
        [&utfil] (const auto & val) {  (val.second)->skrivTilFil(utfil);  } );

    for_each(gRod.begin(), gRod.end(),            //  Rød løypes innhold:
        [&utfil] (const auto & val) {  val->skrivTilFil(utfil);  } );

    utfil.close();                                //  Lukker filen manuelt.

//  NB: NB:  ALLE ELEMENTENE ER FORTSATT UBERØRT I ALLE CONTAINERNE !!!

//  NB:  Burde EGENTLIG IKKE ha skrevet til fil de som bare har hatt dagskort,
//       eller om det er søndag og kjøreren har hatt helgekort.
//       Men, fin øvelse å utvide koden (flere steder) med dette ......
}


/**
 *  Sletter ALLE elementene og TILPEKTE kjørere i ALLE containerne.
 *
 *  @see   virtual Kjorer::skrivTilFil(...)
 */
void slettAlleData() {
                   //  Alle de syv innrykkede kodelinjene (til kolonne nr.25)
                   //  er "overflødige", så lenge 'skrivTilFil' (rett ovenfor)
                   //  har gjort dette allerede.
                   //  Ellers måtte/kunne filskriving ha vært gjort på denne
                   //  måten, samtidig som ALT i ALLE containerne slettes.
                        ofstream utfil("EKS_26.DT3");
                        cout << "\nSkriver til filen 'EKS_26.DT3' .....\n\n";
                        utfil << gSisteNummer << '\n';

                                              //  HEISKØEN:
    while (!gHeisKo.empty()) {                //  Ennå elementer igjen:
                        (gHeisKo.front())->skrivTilFil(utfil);
        delete gHeisKo.front();               //  Sletter 1.TILPEKTE 'Kjorer'.
        gHeisKo.pop();                        //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i HEISKØEN:     " << gHeisKo.size() << '\n';

                                              //  HEISEN:
    while (!gHeis.empty()) {                  //  Ennå elementer igjen:
                        (gHeis.front())->skrivTilFil(utfil);
        delete gHeis.front();                 //  Sletter 1.TILPEKTE 'Kjorer'.
        gHeis.pop();                          //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i HEISEN:       " << gHeis.size() << '\n';


    while (!gGronn.empty()) {                 //  GRØNN LØYPE:
        Kjorer* it = (gGronn.begin())->second;  //  PEKER til 1.KJORER.
                        it->skrivTilFil(utfil);
        delete it;                            //  Sletter 1.TILPEKTE 'Kjorer'.
        gGronn.erase(gGronn.begin());         //  Sletter PARET key og PEKER.
//  Alternativt for de fire siste linjene ovenfor:
//      auto it = gGronn.begin();
//                        (it->second)->skrivTilFil(utfil);
//      delete (it->second);                  //  Sletter TILPEKTE 'Kjorer'.
//      gGronn.erase(it);                     //  Sletter PARET key og PEKER.
    }
    cout << "\tAntall elementer i GRØNN LØYPE:  " << gGronn.size() << '\n';

                                              //  RØD LØYPE:
    while (!gRod.empty()) {                   //  Ennå elementer igjen:
                        (gRod.front())->skrivTilFil(utfil);
        delete gRod.front();                  //  Sletter 1.TILPEKTE 'Kjorer'.
        gRod.pop_front();                     //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i RØD LØYPE:    " << gRod.size() << '\n';
}


/**
 *  Sletter (om mulig) en ønsket nummerangitt kjører (når er i en av løypene).
 *
 *  @see   finnKjorer(...)
 *  @see   Kjorer::hentID()
 *  @see   virtual Kjorer:skrivData()
 */
void slette() {
//  NB: Denne funksjonen er MYE LIK 'tilHeisKo'. Så, de kunne til en viss grad
//      ha vært laget på samme måte som 'detaljerEllerEndre'. Men, det hadde
//      blitt såpass mange 'if' og 'else' for å skille på meldinger og hva
//      som skal gjøres, at derfor er det laget to ulike funksjoner.

    Kjorer* kjorer = nullptr; //  Peker til en Kjorer INNI EN CONTAINER !!!
    char loype;               //  Hvilken løype funnet i (evt. 'G' eller 'R').
    int nr;                   //  Ønsket kjørernummer å slette.

    if (!gGronn.empty() || !gRod.empty()) {       //  Kjører i minst EN løype:
       nr = lesInt("\tSlette nr", 0, gSisteNummer);   //  Ønsket nr. å slette.

       if (nr) {                            // 'nr' er IKKE 0 (null):
          kjorer = finnKjorer(nr, loype);   //  Prøver å finne kjøreren i
                                            //    en av løypene.
          if (kjorer) {                     //  Kjøreren funnet:
             if (loype == 'G')              //  Funnet i GRØNN løype:
                gGronn.erase(nr);           //  Sletter PARET key og PEKER.
             else if (loype == 'R') {       //  Er i RØD løype:
                                            //  Bruker funksjon i <algorithm>:
                auto it = find_if(gRod.begin(), gRod.end(),
                     [nr](const auto & val) { return(val->hentID() == nr); });
                if (it != gRod.end())       //  Fortsatt funn:
                   gRod.erase(it);          //  Sletter SELVE PEKEREN.
             }
             cout << "\tSlettet er altså:\n";
             kjorer->skrivData();           //  Skriver den som slettes.
             delete kjorer;          //  NÅ FØRST SLETTES SELVE KJØREREN !!!
                                     //  NB:  Hadde det vært gjort tidligere
                                     //       (sammen med 'skrivData'), f.eks.
                                     //       rett etter 'if (kjorer)', så
                                     //       ville setningen 'val->hentID()'
                                     //       ha blitt meningsløs.
          } else
            cout << "\n\tUkjent nummer i begge løypene!\n\n";
       } else
         cout << "\n\tOK - ingen slettes.\n\n";
    } else
      cout << "\n\tBegge løypene er tomme!\n\n";
}


/**
 *  Flytter (om mulig) 1.kjører i heiskøen til inn bakerst/nederst i heisen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void tilHeisen() {
  if (!gHeisKo.empty()) {                   //  Noen i heiskøen:
      (gHeisKo.front())->skrivData();       //  Skriver den første sine data.
    cout << "\n\tflyttes fra heiskøen og inn (nederst/bakerst) i heisen.\n\n";
      gHeis.push(gHeisKo.front());          //  KOPIERER pekeren til 'gHeis'.
      gHeisKo.pop();                        //  Sletter 1.pekeren i 'gHeisKo'.
  }  else
      cout << "\n\tHeiskøen er tom, så ingen å sette inn i heisen!\n\n";
}


/**
 *  Flytter (om mulig) en kjører fra en av løypene til bakerst i heiskøen.
 *
 *  @see   finnKjorer(...)
 *  @see   virtual Kjorer::skrivData()
 *  @see   Kjorer::hentID()
 */
void tilHeisKo()  {
    Kjorer* kjorer = nullptr;    //  Kjøreren evt. funnet i en av løypene.
    char loype;                  //  Evt. funnet i 'G'rønn eller 'R'ød løype.
    int nr;                      //  Ønsket kjørernummer fra løype til heiskø.

    if (!gGronn.empty()  ||  !gRod.empty()) {     //  Kjører i minst EN løype:
        cout << "\tFlytte fra en løype til heiskø:\n";
        nr = lesInt("\tNr", 1, gSisteNummer);     //  Ønsket nr. å flytte.

        kjorer = finnKjorer(nr, loype);       //  Prøver å finne kjøreren i
                                              //    en av løypene.
        if (kjorer) {                         //  Kjøreren funnet:
            kjorer->skrivData();              //  Skriver kjørerens data.
            if (loype == 'G') {               //  Funnet i GRØNN løype:
               cout << "\n\tflyttes FRA GRØNN løype og inn i heiskøen.\n\n";
               gHeisKo.push(kjorer);          //  Legger inn Kjorer-PEKER.
               gGronn.erase(nr);              //  Sletter PARET key og PEKER.
           } else if (loype == 'R') {         //  Funnet i RØD løype:
               cout << "\n\tflyttes FRA RØD løype og inn i heiskøen.\n\n";
               gHeisKo.push(kjorer);          //  Legger inn Kjorer-PEKER.
                                              //  Sletter SELVE PEKEREN:
               gRod.remove_if([nr] (const auto & val)
                                   { return(val->hentID() == nr); });
//  Alternativt vha. funksjon i <algorithm>, da ingen egen "find" i <list>:
/*       auto it = find_if(gRod.begin(), gRod.end(),
                   [nr] (const auto & val) { return(val->hentID() == nr); } );
         if (it != gRod.end())           //  Funn:
            gRod.erase(it);              //  Sletter SELVE PEKEREN.
         else   //  Kjøreren er jo funnet - så what???:
            cout << "\n\tSEMANTISK FEIL-1 - dette skal ikke skje!!\n\n";  */
           } else     //  Kjøreren er jo funnet, men IKKE 'G/R' - så what???:
             cout << "\n\tSEMANTISK FEIL-2 - dette skal ikke skje!!\n\n";
                      // *****************************************************
                      // **   Jfr/vs. EXCEPTIONS kap.16.1 i læreboka        **
                      // **                      (som ikke er pensum).      **
                      // *****************************************************
        } else
          cout << "\n\tUkjent nummer i begge løypene!\n\n";
    } else
      cout << "\n\tBegge løypene er tomme!\n\n";
}


/**
 *  Flytter (om mulig) fra heisen og over til grønn eller rød løype.
 *
 *  @param   loype  - Bokstaven ('G/R') for hvilken løype å flytte til
 *  @see     virtual Kjorer::skrivData()
 *  @see     Kjorer::registrerLoype
 *  @see     Kjorer::hentID()
 */
void tilLoype(const char loype) {
  if (!gHeis.empty()) {                          //  Kjører(e) i heisen:
     (gHeis.front())->skrivData();               //  1.kjørers data skrives.
     cout << "\n\tflyttes fra heisen og over i "
          << ((loype == 'G') ? "GRØNN" : "RØD") << " løype\n\n";

     gHeis.front()->registrerLoype(loype);       //  Oppdaterer kjørerens
                                                 //    "statistikk" med 'G/R'.
     if (loype == 'G')                           //  Flyttes til GRØNN:
                                             //  NØKKEL OG PEKER LEGGES INN:
                                             //  NB:  BRUKEN AV 'hentID()' !!!
       gGronn[gHeis.front()->hentID()] = gHeis.front();
//  Alternativt litt mer omstendelig/formelt:
//                gGronn.insert(pair <int, Kjorer*>
//                             ((gHeis.front())->hentID(), gHeis.front()));


     else {                                   //  Flyttes til RØD:
       gRod.push_back(gHeis.front());   //  Legger inn PEKER bakerst i listen:
                                        //  NB:  SORTERER !!!!!!!!!!!!!! :
       gRod.sort([](Kjorer* k1, Kjorer* k2)
                                { return (k1->hentID() < k2->hentID()); });
     }
     gHeis.pop();                             //  Fjerner PEKER fra heisen.

  } else
    cout << "\n\tHeisen er tom, så ingen å sette inn i noen løype!\n\n";
}
