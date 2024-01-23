/**
 *   Løsningsforslag til kontinuasjonseksamen i OOProg (i C++), 
 *                                              august 2020, oppgave 2.
 *
 *   Programmet holder orden på nettarrangementer (konserter og foredrag).
 *
 *   Programmet:
 *      - inneholder EN <map> med key/dato (unike) og pekere til 
 *        'NettArrangement' (i praksis 'Musikk'- eller 'Foredrag'-objekter)
 *      - skriver ALLE data om ALLE arrangementene ut på skjermen
 *      - skriver ALLE arrangementene i en viss TIDSPERIODE ut på skjermen
 *      - skriver ALLE foredragene i en viss NAVNGITT SERIE ut på skjermen 
 *      - sletter ett arrangement
 *      - legger inn ett nytt arrangement
 *      - leser og skriver HELE datastrukturen fra/til fil
 *
 *   @file     EX_S20_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>                  //  string
#include <map>                     //  map
#include <algorithm>               //  find_if
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int FDATO = 200101;          ///<  Første mulige dato (1/1-2020).
const int SDATO = 301231;          ///<  Siste mulige dato (31/12-2030).


/**
 *  ArrType (arrangementstype som:  'ikkeSatt', 'musikk' og 'foredrag').
 */
enum  ArrType  {  ikkeSatt, musikk, foredrag  };


/**
 *  Kategori (om er arrangert av:  en 'privat' eller 'offentlig' aktør).
 */
enum  Kategori  {  privat,  offentlig  };


/**
 *  NettArrangement (med dato (unik - max ett arrangement hver dag),
 *                   startklokkeslett, Vippsnummer, ca varighet i timer,
 *                   arrangementsnavn, navn på aktør og en enum 'type').
 */
class NettArrangement {
  private:
      int     dato,               //  = ID – dette er key'en i <map>en,
              klokken,            //         på formen: ÅÅMMDD.
              vippsNr;
      float   varighet;
      string  arrNavn,
              aktor;
  protected:
      ArrType type;
  public:
      NettArrangement(const int dato) {  this->dato = dato;   type = ikkeSatt; 
                                  klokken = vippsNr = 0;   varighet = 0.0F;  }
      NettArrangement(ifstream & inn);                     //  Oppgave 2G
      int  hentID() const  {  return dato;  }
      void settID(const int dato)  { this->dato = dato; }  //  Ny ifm.Oppg.2E
      bool erAvType(const ArrType type) const { return (this->type == type); }
      bool liktArrNavn(const string nvn) const  {  return (arrNavn == nvn);  }
      virtual void lesData();                              //  Oppgave 2E
      virtual void skrivData() const;                      //  Oppgave 2A
      virtual void skrivTilFil(ofstream & ut) const;       //  Oppgave 2F
};


/**
 *  Musikk (med kun antall personer (i bandet) på scenen.
 */
class Musikk : public NettArrangement {
  private:
      int  antPersoner;
  public:
      Musikk(const int dato) : NettArrangement(dato) 
            {  type = musikk;  antPersoner = 0;  }
      Musikk(ifstream & inn);                              //  Oppgave 2G
      virtual void lesData();                              //  Oppgave 2E
      virtual void skrivData() const;                      //  Oppgave 2A
      virtual void skrivTilFil(ofstream & ut) const;       //  Oppgave 2F
};


/**
 *  Foredrag (med hvilket nummer i en evt serie, og om 'privat'/'offentlig').
 */
class Foredrag : public NettArrangement {
  private:
      int      serieNr;
      Kategori kategori;
  public:
      Foredrag(const int dato) : NettArrangement(dato)  
              {  type = foredrag;   serieNr = 1;   kategori = privat;  }
      Foredrag(ifstream & inn);                         //  Oppgave 2G
      void okSisteNr() { serieNr++; }                   //  Ny ifm. Oppgave 2E
      virtual void lesData();                           //  Oppgave 2E
      virtual void skrivData() const;                   //  Oppgave 2A
      virtual void skrivTilFil(ofstream & ut) const;    //  Oppgave 2F
};


void lesFraFil();                   //  Oppgave 2G
void nyttArrangement();             //  Oppgave 2E
void skrivAlt();                    //  Oppgave 2A
void skrivForedragsserie();         //  Oppgave 2C
void skrivMeny();
void skrivTidsperiode();            //  Oppgave 2B
void skrivTilFil();                 //  Oppgave 2F
void slettArrangement();            //  Oppgave 2D


map <int, NettArrangement*>  gArrangementer;    ///<  ALLE arrangementene.


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesFraFil();                                       //  Oppgave 2G

    skrivMeny();
    valg = lesChar("\n\nKommando");
    while (valg != 'Q') {
        switch (valg) {
          case 'A': skrivAlt();             break;     //  Oppgave 2A
          case 'T': skrivTidsperiode();     break;     //  Oppgave 2B
          case 'F': skrivForedragsserie();  break;     //  Oppgave 2C
          case 'S': slettArrangement();     break;     //  Oppgave 2D
          case 'N': nyttArrangement();      break;     //  Oppgave 2E
          default:  skrivMeny();            break;
        }
        valg = lesChar("\n\nKommando");
    }

    skrivTilFil();                                     //  Oppgave 2F

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 */
NettArrangement::NettArrangement(ifstream & inn) {    //  Leser ALLE egne data
    inn >> dato >> klokken >> vippsNr >> varighet;  inn.ignore();  //  inn fra
    getline(inn, arrNavn);    getline(inn, aktor);                 //  fil:
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 */
void NettArrangement::lesData() {
    cout << "\tArrangementsnavn:  ";   getline(cin, arrNavn); //Leser tekster:
    cout << "\tAktør:  ";  getline(cin, aktor);
    klokken  = lesInt("\tStarter kl.", 0, 23);           //  Leser numeriske
    varighet = lesFloat("\tVarer i timer", 0.5F, 10.0F); //    verdier i passe
    vippsNr  = lesInt("\tVippsnr", 10000, 99999999);     //    intervall:
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 */
void NettArrangement::skrivData() const {
  cout << dato << " kl." << klokken << " i " << varighet << " time(r).  "
       << "Vippsnr: " << vippsNr << "\n\t\t"
       << arrNavn << "  med  " << aktor << '\n';
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 */
void NettArrangement::skrivTilFil(ofstream & ut) const {
    ut << ' ' << dato << ' ' << klokken << ' '
       << vippsNr << ' ' << varighet << '\n'
       << arrNavn << '\n' << aktor << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 *  @see    NettArrangement::NettArrangement(...)
 */
Musikk::Musikk(ifstream & inn) : NettArrangement(inn) {
    type = musikk;                           //  Setter aktuell subklassetype.
    inn >> antPersoner;   inn.ignore();      //  Leser datamedlemmet fra fil.
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *  @see    NettArrangement::lesData()
 */
void Musikk::lesData() {
    NettArrangement::lesData();              //  Baseklassens data leses.
    antPersoner = lesInt("\tAntall personer på scenen", 1, 20); // Egen leses.
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 *
 *  @see    NettArrangement::skrivData()
 */
void Musikk::skrivData() const {             // Eget data skrives:
    cout << "\tMUSIKK (" << antPersoner << " person(er)):\n\t\t"; 
    NettArrangement::skrivData();            //  Baseklassens data skrives.
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 *  @see     NettArrangement::skrivTilFil(...)
 */
void Musikk::skrivTilFil(ofstream & ut) const {
    ut << 'M';                               //  'Musikk'-objekt sine data.
    NettArrangement::skrivTilFil(ut);        //  Baseklassens data skrives.
    ut << antPersoner << '\n';               //  Egne data skrives.
}


// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn egne data fra fil.
 *
 *  @param  inn  -  Filobjektet det leses inn data fra
 *  @see    NettArrangement::NettArrangement(...)
 */
Foredrag::Foredrag(ifstream & inn) : NettArrangement(inn) {
    char kat;
    type = foredrag;                         //  Setter aktuell subklassetype.
    inn >> serieNr >> kat;   inn.ignore();   //  Leser datamedlemmer fra fil.
    kategori = (kat == 'P') ? privat : offentlig;   //  Gjør om char til enum.
}


/**
 *  Oppgave 2E - Leser inn ALLE egne data fra tastaturet.
 *
 *  @see    NettArrangement::lesData()
 */
void Foredrag::lesData() {
    NettArrangement::lesData();              //  Baseklassens data leses.
    kategori = (lesChar("\tArrangert av P(rivat) eller O(ffentlig)") == 'P') ?
                                          privat  :  offentlig;
}


/**
 *  Oppgave 2A - Skriver ALLE egne data ut på skjermen.
 *
 *  @see    NettArrangement::skrivData()
 */
void Foredrag::skrivData() const {
    cout << "\tFOREDRAG (nr." << serieNr << ",  i "     //  Egne data skrives:
         << ((kategori == privat)? "privat" : "offentlig")  // Enum som tekst.
         << " regi):\n\t\t";
    NettArrangement::skrivData();            //  Baseklassens data skrives.
}


/**
 *  Oppgave 2F - Skriver ALLE egne data ut på fil.
 *
 *  @param   ut  -  Filobjektet det skrives ut data til
 *  @see     NettArrangement::skrivTilFil(...)
 */
void Foredrag::skrivTilFil(ofstream & ut) const {
    ut << 'F';                               //  'Foredrag'-objekt sine data.
    NettArrangement::skrivTilFil(ut);        //  Baseklassens data skrives.
                                             //  Egne data skrives til filen:
    ut << serieNr << ' ' << ((kategori == privat) ? "P" : "O") << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser hele datastrukturen (ulike arrangementer) inn fra fil.
 *
 *  @see      Musikk::Musikk(...)
 *  @see      Foredrag::Foredrag(...)
 *  @see      NettArrangement::hentID()
 */
void lesFraFil() {
    ifstream innfil("EX_S20_NETTARRANGEMENT.DTA");
    char arrType;                              //  'M' eller 'F'.
    NettArrangement* nyttArrangement =  nullptr;

    if (innfil) {                              //  Filen finnes:
       cout << "\n\n\tLeser fra filen 'EX_S20_NETTARRANGEMENT.DTA'......\n\n";

       innfil >> arrType;                      //  Leser(?) 1.felt i ny post.
       while (!innfil.eof()) {                 //  Mer på filen:
           switch (arrType) {                  //  Aktuelt objekt leser selv:
              case 'M':  nyttArrangement = new Musikk(innfil);         break;
              case 'F':  nyttArrangement = new Foredrag(innfil);       break;
              default:   cout << "\n\tUlovlig bokstav på filen!\n\n";  break;
           }
                                               //  Legger inn i <map>en:
           gArrangementer[nyttArrangement->hentID()] = nyttArrangement;

           innfil >> arrType;                  //  Leser(?) 1.felt i ny post.
       }
       innfil.close();                        //  Lukker filen manuelt.
    } else                                    //  Filen finnes IKKE:
      cout << "\n\n\tFant ikke filen 'EX_S20_NETTARRANGEMENT.DTA'!\n\n";
}


/**
 *  Oppgave 2E - Legger inn (om mulig) ett nytt arrangement (Musikk/Foredrag).
 *
 *  @see      Musikk::Musikk(...)
 *  @see      Foredrag::Foredrag(...)
 *  @see      NettArrangement::lesData()
 *  @see      NettArrangement::skrivData()
 *  @see      NettArrangement::liktArrNavn(...)
 *  @see      NettArrangement::erAvType(...)
 *  @see      NettArrangement::hentID()
 *  @see      Foredrag::settID(...)
 *  @see      Foredrag::okSisteNr()
 */
void nyttArrangement() {                         //  Diverse hjelpepekere:
  NettArrangement* nyttArrangement = nullptr, *sisteArrangement = nullptr;
  Foredrag* nyttForedrag = nullptr,  *sisteForedag = nullptr;
  int dato;                                         //  Aktuell ny dato.
  string foredragsNavn;              //  Evt. kopi av navngitt foredragsserie.
  char arrType = lesChar("\tArrangementstype (M(usikk), F(oredrag))");

  if (arrType == 'M' || arrType == 'F') {           // 'M' eller 'F':
     dato = lesInt("\tDato", FDATO, SDATO);         //  Ønsket dato:

     auto it = gArrangementer.find(dato);           //  Finnes allerede?

     if (it == gArrangementer.end()) {              //  Nei (atlså ny dato):
        if (arrType == 'M') {                       //  Musikk-arrangement:
           nyttArrangement = new Musikk(dato);      //  Oppretter nytt objekt.
           nyttArrangement->lesData();              //  Leser dataene.
           gArrangementer[dato] = nyttArrangement;  //  Inni i <map>en.
        } else {                                    //  Foredrag-arrangement:
           if (lesChar("\tN(ytt) eller S(erie)") == 'N') {   //  Nytt:
              nyttArrangement = new Foredrag(dato); //  Oppretter nytt objekt.
              nyttArrangement->lesData();           //  Leser dataene.
              gArrangementer[dato] = nyttArrangement; //  Inni i <map>en.
           }
           else {                                  //  Nytt foredrag i serien:
               cout << "\tForedragsseriens navn:  ";
               getline(cin, foredragsNavn);        //  Leser seriens navn.
                                               //  Finner den første i serien:
               auto it = find_if(gArrangementer.begin(),
                   gArrangementer.end(),
                   [foredragsNavn](const auto & val)
               { return((val.second)->liktArrNavn(foredragsNavn)); });
                                               //  LETER ETTER SISTE I SERIEN:
               while (it != gArrangementer.end()) {
                   sisteArrangement = it->second; //  Peker til selve arrangm.
                                                  //  MEGET viktig med '++'!!:
                   it = find_if(++it, gArrangementer.end(),
                       [foredragsNavn](const auto & val)
                   { return((val.second)->liktArrNavn(foredragsNavn)); });
               }

               if (sisteArrangement != nullptr  &&   //  Funn av navngitt arr.
                  sisteArrangement->erAvType(foredrag)) {   // OG foredrag(!):
                  if (sisteArrangement->hentID() < dato) {  // Senere dato:
                                      //  VET at PEKER til et 'Foredrag',
                                      //  derfor caster om: (jfr. EKS_17.CPP)
                   sisteForedag = dynamic_cast <Foredrag*> (sisteArrangement);
                                      //  Oppretter "dummy" Foredrag-objekt:
                       nyttForedrag = new Foredrag(0);  //  "Fake" dato.
                                      //  KOPIERER SISTE FUNDNE FOREDRAGET:
                       *nyttForedrag = *sisteForedag;
                                      //  Endrer 2x påkrevde/kopierte verdier:
                       nyttForedrag->settID(dato);   // NY KORREKT dato!
                       nyttForedrag->okSisteNr();    // NYTT ØKET serienummer!

                       cout << "\n\tLegger inn nytt foredrag i serie:\n";
                       nyttForedrag->skrivData();    //  Skriver nyinnlagt.
                       gArrangementer[dato] = nyttForedrag;  // Inn i <map>en.
                   } else                            //  For tidlig dato:
                     cout << "\n\tDatoen er tidligere enn siste i serien!\n";
               } else                                //  Ukjent foredrag:
                 cout << "\n\tIngen foredrag med dette navnet!\n";
           }
        }
     } else                                          //  På eksisterende dato:
       cout << "\n\tArrangement på denne datoen allerede!\n";
  } else                                             //  Annet enn 'M' og 'F':
    cout << "\n\tOK - ulovlig arrangementstype. Ingenting registrert.\n";
}


/**
 *  Oppgave 2A - Skriver ALT om ALLE arrangementene ut på skjermen.
 *
 *  @see      NettArrangement::skrivData()
 */
void skrivAlt() {
    for (const auto & val : gArrangementer)  //  Hvert arrangement skriver
        (val.second)->skrivData();           //    selv ALLE sine data.
                                             //  Skriver antall arrangementer:
    cout << "\n\tTotalt: " << gArrangementer.size() << " arrangement(er).\n";
}


/**
 *  Oppgave 2C - Skriver ALLE foredragene i en NAVNGITT SERIE ut på skjermen.
 *
 *  @see      NettArrangement::erAvType(...)
 *  @see      NettArrangement::liktArrNavn(...)
 *  @see      NettArrangement::skrivData()
 */
void skrivForedragsserie() {
    string foredragsNavn;

    if (!gArrangementer.empty()) {                 //  Det finnes arrangement:
        cout << "\tForedragsseriens navn:  ";
        getline(cin, foredragsNavn);

        cout << "\n\n\tFølgende foredrag i denne serien:\n\n";
        for (const auto & val : gArrangementer)    //  Går gjennom alle arr:
            if ((val.second)->erAvType(foredrag)   //  Er et foredrag  OG
                &&  (val.second)->liktArrNavn(foredragsNavn))  //  likt navn:
               (val.second)->skrivData();          //  Skriver objektet.
    } else
      cout << "\n\tIngen arrangementer registrert foreløpig!\n\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelige:\n"
         << "\n   A  - skriv Alle arrangementer"
         << "\n   T  - skriv alle arrangement i en viss Tidsperiode"
         << "\n   F  - skriv en hel Foredragsserie"
         << "\n   S  - Slett arrangement"
         << "\n   N  - Nytt arrangement"
         << "\n   Q  - Quit / avslutt";
}


/**
 *  Oppgave 2B - Skriver ALLE arrangementene i en TIDSPERIODE ut på skjermen.
 *
 *  @see      NettArrangement::hentID()
 *  @see      NettArrangement::skrivData()
 */
void skrivTidsperiode() {
    int startDato,                             //  Datoer for tidsintervallet:
        sluttDato,
        dato,                                  //  Aktuelt objekts dato.
        antall = 0;                            //  Antall funn/matcher.

    if (!gArrangementer.empty()) {             //  Det finnes arrangement:
        startDato = lesInt("\tStartdato", FDATO, SDATO);
        sluttDato = lesInt("\tSluttdato", startDato, SDATO);

        cout << "\n\n\tFølgende arrangement er i denne perioden:\n\n";
        for (const auto & val : gArrangementer) {  //  Går gjennom alle arr:
            dato = (val.second)->hentID();     //  Dato i aktuelt intervall:
            if (dato >= startDato  &&  dato <= sluttDato) {
                antall++;                      //  Teller opp antall funn.
                (val.second)->skrivData();     //  Skriver objektet.
            }
        }                                      //  Skriver antall funn av
        cout << "\n\t" << antall << " arrangement av "   // totalantallet:
             << gArrangementer.size() << " er i denne perioden.\n";
    } else
      cout << "\n\tIngen arrangementer registrert foreløpig!\n\n";
}


/**
 *  Oppgave 2F - Skriver hele datastrukturen (ulike arrangementer) ut til fil.
 *
 *  @see      NettArrangement::skrivTilFil(...)
 */
void skrivTilFil() {
    ofstream utfil("EX_S20_NETTARRANGEMENT.DT2");

    cout << "\n\n\tSkriver til filen 'EX_S20_NETTARRANGEMENT.DT2'......\n\n";

    for (const auto & val : gArrangementer) // Hvert arrangement skriver selv:
        (val.second)->skrivTilFil(utfil);   // Arrangement-peker sin funksjon.
    
    utfil.close();                          // Lukker manuelt.
}


/**
 *  Oppgave 2D - Sletter (om mulig) ett gitt arrangement på en gitt dato.
 *
 *  @see      NettArrangement::skrivData()
 */
void slettArrangement() {
    int dato; 

    if (!gArrangementer.empty()) {            //  Det finnes arrangement:
                                              //  Leser aktuell dato:
        dato = lesInt("\tSlett arrangement på datoen", FDATO, SDATO);
        auto it = gArrangementer.find(dato);  //  Prøver å finne arr. på dato.
    
        if (it != gArrangementer.end()) {     // Funn:
           cout << "\n\tSletter arrangementet:\n";
           (it->second)->skrivData();         //  Skriver arrangementets data.
           delete it->second;                 //  Sletter TILPEKT arrangement.
           gArrangementer.erase(it);          //  Sletter PARET key og PEKER.
        } else                                //  Ikke funnet:
          cout << "\n\tIngen arrangement på denne datoen!\n";
    } else
       cout << "\n\tIngen arrangementer registrert foreløpig!\n\n";
}