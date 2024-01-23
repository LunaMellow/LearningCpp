/**
 *   Programeksempel nr 18 - Større programeksempel.
 *
 *   Eksemplet vektlegger:  klasser, arv, virtueller, pekere og datastruktur.
 *
 *   Programmet:
 *      - Registrerer nye gjester på campingplassen
 *      - Sletter/fjerner de som reiser/"sjekker ut" - skriver beløp å betale
 *      - Skriver ut status ('X', '-') for campingplassens ulike felter
 *   (Eksemplet er basert på ideen fra Eksamen 7.juni 1996.)
 *
 *   @file     EKS_18.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int TELT    = 100;           ///<  Prisen for telt pr.døgn.
const int BIL     = 250;           ///<  Prisen for bobil pr.døgn.
const int VOGN    = 250;           ///<  Prisen for campingvogn pr.døgn.
const int STROM   =  40;           ///<  Prisen for strøm pr.døgn.
const int FORTELT =  50;           ///<  Prisen for fortelt pr.døgn.
const int PERSON  =  30;           ///<  Prisen for en person pr.døgn.
const int ANTFELT = 200;           ///<  Antall felter på campingplassen.


/**
 *  Type (med 'telt', 'bobil', 'campingvogn').
 */
enum Type { telt, bobil, campingvogn };


/**
 *  Camping-enhet (med feltnumer, gjestens navn og adresse, evt. bilens regnr,
 *                klasse-typen, antall personer i enheten, ankomst-/avreisedag
 *                (i året) og grunnprisen pr døgn (TELT, BIL, VOGN).
 */
class Enhet  {             //  = TELT også !!!
  private:
    int feltNr;
    string navn,           //  Gjestens navn.
           adr,            //  Gjestens gateadresse og poststed.
           regNr;          //  Bilens registeringsnummer (evnt. blank).

  protected:
    Type type;             //  Type enhet:  'telt', 'bobil', 'campingvogn'
    int  antPersoner;      //  Antall personer/gjester i enheten.
    int  ankDag;           //  Dag for ankomst (dagens absolutte nr. i året).
    int  avrDag;           //  Dag for avreise (dagens absolutte nr. i året).
    int  grunnpris;        //  Grunnpris pr.døgn (= TELT, BIL eller VOGN).

    void skrivType() const;  //  Skriver enum-verdi ut som tekst.

  public:
    Enhet()  {  cout << "'Enhet' MÅ opprettes med feltnummer!\n";  }

    Enhet(int nr)  {         //  Setter initielle data:
      feltNr = nr;   navn = adr = regNr = "";
      antPersoner = ankDag = avrDag = 0;   type = telt;   grunnpris = TELT;
    }
                        //  MÅ være 'virtual' for å kjøre subklassenes også !!
    virtual ~Enhet()  {  cout << "'Enhet'-objekt dør.\n";  }

    int  hentFeltNr() const  {  return feltNr;  }

    void lesAvreiseDag() { avrDag = lesInt("\tAvreisedag", ankDag + 1, 365); }

    virtual void faktura() const;
    virtual void lesData();
    virtual void skrivData() const;
};


/**
 *  Bobil (med bruk av strøm eller ei) - subklasse av 'Enhet'.
 */
class Bobil : public Enhet {
  protected:
    bool strom;                    //  Har gjesten brukt strøm eller ei.

  public:
    Bobil() { cout << "'Bobil' MÅ opprettes med feltnummer!\n"; }

    Bobil(int nr) : Enhet(nr)      //  Setter initielle data:
                    {  strom = false;   type = bobil;   grunnpris = BIL;  }

    virtual ~Bobil()  {  cout << "'Bobil'-objekt dør.\n";  }

    virtual void faktura() const;
    virtual void lesData();
    virtual void skrivData() const;
};


/**
 *  Campingvogn (med fortelt eller ei og vognlengde) - subklasse av 'Bobil'.
 */
class Campingvogn : public Bobil {
  private:
    bool   fortelt;                //  Har gjesten brukt fortelt eller ei.
    float  lengde;                 //  Campingvognens lengde (i meter).

  public:
    Campingvogn()  { cout << "'Campingvogn' MÅ opprettes med feltnummer!\n"; }
                                   //  Setter initielle data:
    Campingvogn(int nr) : Bobil(nr)  {  fortelt = false;   lengde = 0.0F;
                      type = campingvogn;   grunnpris = VOGN;  }

    virtual ~Campingvogn()  {  cout << "'Campingvogn'-objekt dør.\n";  }

    virtual void faktura() const;
    virtual void lesData();
    virtual void skrivData() const;
};


int  finnGjest(const int nr);
void nyGjest();
void plassensStatus();
void slettGjest();


vector <Enhet*>  gGjestene;           ///<  Oversikten over nåværende gjester.
vector <bool>    gFelt(ANTFELT);      ///<  Status for plassens ulike felter.


/**
 *  Hovedprogrammet:
 */
int main() {
    char kommando =
             lesChar("\n\nGi kommando (N(y), S(lett), P(lasstatus), Q(uit))");

    while (kommando != 'Q') {
        switch (kommando)  {
          case 'N':  nyGjest();         break;
          case 'S':  slettGjest();      break;
          case 'P':  plassensStatus();  break;
        }
        kommando =
             lesChar("\n\nGi kommando (N(y), S(lett), P(lasstatus), Q(uit))");
    }

    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Regner og skriver ut TOTALPRISEN for Enhet-/Telt-gjestens opphold.
 */
void Enhet::faktura() const  {
    cout << "\tPRIS    :  "
         << (grunnpris + (PERSON * antPersoner)) * (avrDag - ankDag) << '\n';
}


/**
 *  Leser inn alle klassens datamedlemmer.
 */
void Enhet::lesData() {
    ankDag = lesInt("\tAnkomstdag", 1, 364);
    cout << "\tNavn                  :  ";  getline(cin, navn);
    cout << "\tAdresse (gate og sted):  ";  getline(cin, adr);
    cout << "\tBilens reg.nr         :  ";  getline(cin, regNr);
    if (regNr.length() == 0)  regNr = "-- -----";          //  Blankt regnr.
    antPersoner = lesInt("\tAntall personer", 1, 10);
}


/**
 *  Skriver ut alle klassens datamedlemmer.
 */
void Enhet::skrivData() const   {
    cout << "\n\tFelt nr :  " << feltNr          //  'type' skrives ut av
         << "\n\tType    :  ";   skrivType();    //     en egen funksjon.
    cout << "\n\tNavn    :  " << navn
         << "\n\tAdresse :  " << adr
         << "\n\tReg.nr  :  " << regNr
         << "\n\tAnt.pers:  " << antPersoner
         << "\n\tAnt.døgn:  " << avrDag - ankDag << '\n';
}


/**
 *  Skriver ut enum-verdien 'type' som tekst.
 */
void Enhet::skrivType() const {
    switch (type) {
      case telt:         cout << "Telt";         break;
      case bobil:        cout << "Bobil";        break;
      case campingvogn:  cout << "Campingvogn";  break;
    }
}

// ---------------------------------------------------------------------------

/**
 *  Regner og skriver ut TOTALPRISEN for Bobilen-gjestens opphold.
 */
void Bobil::faktura() const  {
    cout << "\tPRIS    :  "
         << (grunnpris + (PERSON * antPersoner)
            +(STROM * static_cast <int> (strom))) * (avrDag - ankDag) << '\n';
}


/**
 *  Leser inn alle klassens datamedlemmer - også de arvede.
 */
void Bobil::lesData() {
    Enhet::lesData();
    strom = (lesChar("\tBruke strøm (j/N)") == 'J');
}


/**
 *  Skriver ut alle klassens datamedlemmer - også de arvede.
 */
void Bobil::skrivData() const  {
    Enhet::skrivData();
    cout << "\tStrøm   :  " << (strom ? "Ja" : "Nei") << '\n';
}

// ---------------------------------------------------------------------------

/**
 *  Regner og skriver ut TOTALPRISEN for Campingvogn-gjestens opphold.
 */
void Campingvogn::faktura() const  {
    cout << "\tPRIS    :  ";
    cout << (grunnpris + (PERSON * antPersoner)
       +(STROM * static_cast <int> (strom))
       +(FORTELT * static_cast <int> (fortelt)))  * (avrDag - ankDag) << '\n';
}


/**
 *  Leser inn alle klassens datamedlemmer - også de arvede.
 */
void Campingvogn::lesData() {
    Bobil::lesData();
    fortelt = (lesChar("\tFortelt (j/N)") == 'J');
    lengde = lesFloat("\tVognens lengde (i meter)", 2.0, 12.0);
}


/**
 *  Skriver ut alle klassens datamedlemmer - også de arvede.
 */
void Campingvogn::skrivData() const  {
    Bobil::skrivData();
    cout << "\tFortelt :  " << (fortelt ? "Ja" : "Nei")
         << "\n\tVognlen :  " << lengde << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Finner (om mulig) indeksen for en gjest med et visst feltnummer.
 *
 *  @param    nr  - Aktuelt feltnummer å lete etter hos enhetene
 *  @return   Gjestens indeks i 'gGjestene'. evt. -1 om ikke funnet
 *  @see      Enhet::hentFeltNr()
 */
int finnGjest(const int nr) {
    for (int i = 0; i < gGjestene.size(); i++)  //  Går gjennom alle gjestene:
        if (gGjestene[i]->hentFeltNr() == nr) return i;  //  Match!
    return -1;                                  //  Ingen match.
}


/**
 *  Legger inn (om mulig) i datastrukturen en ny gjest på campingplassen.
 *
 *  @see   Enhet::Enhet(...)
 *  @see   Bobil::Bobil(...)
 *  @see   Campingvogn::Campingvogn(...)
 *  @see   Enhet::lesData()
 */
void nyGjest() {                  //  Registerer en ny gjest i lista.
    char type;
    int feltNr;
    Enhet* nyGjest = nullptr;     //  VIKTIG! For ellers vil kompilatoren
                                  //    kunne protestere på at den etter
                                  //    switch'en ser uinitialisert ut.

    cout << "\n\nREGISTRERING AV NY GJEST:\n";
    do {                                         // Leser "type" gjest:
       type = lesChar("\tType (T(elt), B(obil), C(ampingvogn)");
    } while (type != 'T'  &&  type != 'B'  &&  type != 'C');

    feltNr = lesInt("\tFeltnummer", 0, ANTFELT);

    if (feltNr) {                              //  '0' (null) er IKKE skrevet:
        if (!gFelt[feltNr-1])  {               //  Feltet er ledig:

            gFelt[feltNr-1] = true;            //  Setter feltet som opptatt.

            switch (type) {                    //  Oppretter relevant objekt:
              case 'T':  nyGjest = new Enhet(feltNr);        break;
              case 'B':  nyGjest = new Bobil(feltNr);        break;
              case 'C':  nyGjest = new Campingvogn(feltNr);  break;
            }

            nyGjest->lesData();                //  Objektets data leses.

            gGjestene.push_back(nyGjest);      //  Legger inn i vectoren.

       } else
         cout << "\n\tFeltet er allerede opptatt, prøv med et annet!";
    } else
      cout << "\n\tOK - ingen ny gjest er registrert.";
}


/**
 *  Skriver ut status for ALLE felter på hele campingplassen.
 */
void plassensStatus() {
    cout << "\n\nStatus for ALLE feltene på HELE campingplassen:\n";
    for (int i = 0;  i < ANTFELT;  i++) {    //  = gFelt.size()
                                             //  Men IKKE gFelt.capacity() !!!
        cout << setw(4) << i+1 << ": " << (gFelt[i] ? "X" : "-");
        if (((i+1) % 15) == 0)  cout << '\n';   //  '\n' for hver femtende.
    }
    cout << '\n';
}


/**
 *  Sletter/fjerner (om mulig) en gjest fra campingplassen - faktura skrives.
 *
 *  @see   finnGjest(...)
 *  @see   Enhet::lesAvreiseDag();
 *  @see   Enhet::skrivData();
 *  @see   Enhet::faktura();
 */
void slettGjest() {
    int feltNr,                                 //  Utsjekkende feltnummer.
        indeks;                                 //  Gjestens indeks i
                                                //    vectoren 'gGjestene'.
    cout << "\n\nUTSJEKKING AV GJEST:\n";
    feltNr = lesInt("\tFra feltnummer", 1, ANTFELT);  //  Leser feltnummer.

    if (gFelt[feltNr-1]) {                      //  Feltet er korrekt i bruk:
                                                //  Prøver å finne gjest med
        indeks = finnGjest(feltNr);             //    angitt feltnummer.

        if (indeks >= 0) {                      //  Gjesten funnet:
            gGjestene[indeks]->lesAvreiseDag(); //  Leser avreisedagen.
            gGjestene[indeks]->skrivData();     //  Skriver ALLE data.
            gGjestene[indeks]->faktura();       //  Skriver sluttfaktura.

            gFelt[feltNr-1] = false;            //  Setter feltet som ledig.

            delete gGjestene[indeks];           //  Sletter objektet.
                                                //  Flytter den bakerste frem:
            gGjestene[indeks] = gGjestene[gGjestene.size()-1];
            gGjestene.pop_back();               //  Sletter bakerste peker.

        } else
          cout << "\n\tIngen gjest har dette feltnummeret!\n";
    } else
        cout << "\n\tIngen registrert på dette feltet. Feil feltnummer?\n";
}


// ***************************************************************************
/*    OPPGAVE/ØVELSE:

      Skriv om hele eksemplet ved å:
         - kutte HELT UT vectoren 'gFelt'
         - la vectoren 'gGjestene' bli ANTFELT lang.
           'gGjestene[i]' vil da representere felt nr.i+1
           Peker dette elementet til 'nullptr', så betyr det at ingen
           bor/er på feltet. Ellers peker den til enheten som er der.
           Dermed kan også 'feltNr' kuttes ut i 'Enhet', og trenger da
           heller ikke sendes med oppover som parameter blant constructorene.
*/
// ***************************************************************************
