/**
 *   Programeksempel nr 28 - Større programeksempel.
 *
 *   Eksemplet viser bruken av svært mye av det TOTALE pensumet i emnet.
 *   Bl.a vises:  pekere, objekter, filhåndtering, lambda-funksjoner,
 *                string og fra STL: <vector>, <list>, <map> og <algorithm>.
 *                Bruk av datastrukturer er spesielt vektlagt,
 *                derfor er IKKE arv og virtueller med (vises IKKE).
 *   Sammen med EKS_26.CPP og EKS_29.CPP vises NIVÅET på en eksamensoppgave
 *   (men dette eksemplet er i OMFANG noe større).
 *   (Eksemplet er en utvidelse av oblig nr.3 i tidligere IMT1082.)
 *
 *   Programmet:
 *     - holder oversikt over 20x aktuelle medisiner og Nx pasienter
 *     - registrerer resepter og legene som skriver ut disse
 *     - skriver ut oversikt over ALLE medisiner, pasienter og leger
 *     - skriver ALLE reseptene fra en gitt lege
 *     - skriver ALLE reseptene utskrevet på/til en gitt pasient
 *     - fjerner ALLE resepter eldre enn en viss dato
 *
 *   - Alle legene og pasientene(!) har UNIKE navn (ingen duplikater).
 *   - Det registreres KUN resepter omkring 20x mye brukte medisiner.
 *
 *   @file     EKS_28.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector
#include <list>                    //  list
#include <map>                     //  map
#include <algorithm>               //  sort (for_each)
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


class Resept;         //  PREDEKLARASJON - da 'Lege' refererer til 'Resept'!!!


/**
 *  Lege (med navn, adresse, telefon og en liste med legens resepter).
 */
class Lege {
  private:                    //  NB: navn (som er ID'en) er map'ens "first".
      string adresse;
      int    tlf;
      list   <Resept*> resepter;
  public:
      Lege()  {  tlf = 0;  }
      ~Lege();
      void   fjernResepter(const int dato);
      void   lesData();
      void   lesFraFil(ifstream & inn);
      void   registrerResept(const int nr);
      void   skrivAlt() const;
      void   skrivHovedData() const;
      void   skrivPasienter(const int nr) const;
      void   skrivTilFil(ofstream & ut) const;
};


/**
 *  Medisiner (inneholdende KUN en vector med 20x aktuelle medsinnavn).
 */
class Medisiner {
  private:
    vector <string> navn;
  public:
    int    finn(const string nvn) const;
    string hentNavn(const unsigned int i) const;
    void   lesFraFil(const string filNavn);
    void   skrivAlle() const;
};


/**
 *  Pasienter (inneholdende KUN en vector med de Nx UNIKE pasientnavnene).
 */
class Pasienter {
  private:
    vector <string> navn;
  public:
    int    finn(const string nvn);
    int    finnes(const string nvn) const;
    string hentNavn(const unsigned int i) const;
    void   lesFraFil(const string filNavn);
    void   skrivAlle() const;
    void   skrivTilFil(const string filNavn) const;
};


/**
 *  Resept (med dato, medisinens nummer, pasientens nummer og ANTALL PILLER).
 */
class Resept {
  private:
      int  dato,     //  På formatet:  ÅÅMMDD
           medNr,    //  Nummer/tall/indeks i 'Medisiner'.
           pasNr,    //  Nummer/tall/indeks i 'Pasienter'.
           antall;
  public:
      Resept()        {  dato = medNr = pasNr = antall = 0;  }
      Resept(int nr)  {  medNr = nr;   dato = pasNr = antall = 0;  }
      bool eldreEnn(const int d)              {  return (dato < d);  }
      int  hentID()                           {  return dato;  }
      bool skrevetUtPaa(const int pNr) const  {  return (pasNr == pNr);  }
      void lesData();
      void lesFraFil(ifstream & inn);
      void skrivData() const;
      void skrivTilFil(ofstream & ut) const;
};


void fjernResepter();
void legeOversikt();
void lesLegerOgResepterFraFil();
void pasientOversikt();
void registrerResept();
void skrivAlleLeger();
void skrivLegerOgResepterTilFil();
void skrivMeny();
void slettLegerOgResepter();


map <string, Lege*> gLeger;        ///<  Datastrukturen med ALLE UNIKE legene.
Medisiner    gMedisiner;           ///<  Alle 20x aktuelle medisinnavnene.
Pasienter    gPasienter;           ///<  Alle pasientnavnene totalt.


/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    gMedisiner.lesFraFil("EKS_28_MEDISINER.DTA");
    gPasienter.lesFraFil("EKS_28_PASIENTER.DTA");
    lesLegerOgResepterFraFil();

    skrivMeny();
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'M':  gMedisiner.skrivAlle();  break;
          case 'N':  gPasienter.skrivAlle();  break;
          case 'A':  skrivAlleLeger();        break;
          case 'R':  registrerResept();       break;
          case 'L':  legeOversikt();          break;
          case 'P':  pasientOversikt();       break;
          case 'F':  fjernResepter();         break;
          default:   skrivMeny();             break;
        }
        kommando = lesChar("Kommando");
    }

    gPasienter.skrivTilFil("EKS_28_PASIENTER.DT2");
    skrivLegerOgResepterTilFil();

    slettLegerOgResepter();

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Destructor som sletter/fjerner ALLE reseptene fra listen.
 */
Lege::~Lege() {
    while (!resepter.empty()) {               //  Ennå elementer igjen:
                    //  (resepter.front())->skrivData();
        delete resepter.front();              //  Sletter 1.TILPEKTE 'Resept'.
        resepter.pop_front();                 //  Fjerner den 1.PEKEREN.
    }
}


/**
 *  Fjerner (om mulig) ALLE resepter hos en lege som eldre enn 'dato'.
 *
 *  @param    dato  -  Datoen det skal sjekkes om resepter er eldre enn
 *  @see      Resept::eldreEnn(...)
 */
void Lege::fjernResepter(const int dato) {
    skrivHovedData();                   //  Skriver legens HOVEDdata.
    if (!resepter.empty()) {            //  Legen HAR resepter:
        auto resept = resepter.front(); //  Peker til den første.
                                        //  Ikke tomt, og DEN FØRSTE er eldre:
        while (!resepter.empty()  &&  resept->eldreEnn(dato)) {
            delete resepter.front();    //  Sletter den 1.TILPEKTE.
            resepter.pop_front();       //  Fjerner PEKEREN.
            if (!resepter.empty())      //  Om ennå ikke tomt:
                resept = resepter.front();  //  PEKER til den første.
        }                               //  Status etter evt. fjerning:
        cout << "\t\t#resepter etterpå:  " << resepter.size() << '\n';
    }
}


/**
 *  Leser inn flere av legens data fra brukeren/tastaturet.
 */
void Lege::lesData() {
    cout << "\t\tAdresse:  ";   getline(cin, adresse);
    tlf = lesInt("\t\tTelefon", 10000000, 99999999);
}


/**
 *  Leser ALT om legen (og vedkommendes resepter) inn fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra
 *  @see      Resept::Resept()
 *  @see      Resept::lesFraFil(...)
 */
void Lege::lesFraFil(ifstream & inn) {
    Resept*  resept = nullptr;
    int antResepter;

    inn >> tlf;  inn.ignore();             //  Leser: - legens telefonnummer
    getline(inn, adresse);                 //         - adresse
    inn >> antResepter;   inn.ignore();    //         - antall resepter

    for (int i = 1;  i <= antResepter;  i++)  {  //   - ALLE reseptene:
        resept = new Resept();                   //      Lager ny resept.
        resept->lesFraFil(inn);                  //      Leser resten selv.
        resepter.push_back(resept);              //      Legges i listen.
    }
                                      //  Sorterer reseptene "overflødig"?!!!:
    resepter.sort([](Resept* r1, Resept* r2)
                    { return (r1->hentID() < r2->hentID()); });
}


/**
 *  Registerer og legger inn en ny resept hos legen.
 *
 *  @param    nr  -  Reseptens allerede fundne medisinnummer.
 *  @see      Resept::Resept(...)
 *  @see      Resept::lesData()
 */
void Lege::registrerResept(const int nr) {
    Resept* nyResept = new Resept(nr);     //  Oppretter en ny 'Resept'.
    nyResept->lesData();                   //  Leser selv egne data.
    resepter.push_back(nyResept);          //  Legges inn BAKERST i listen.
                                           //  NB:  SORTERER! - etter dato:
    resepter.sort([](Resept* r1, Resept* r2)
                    { return (r1->hentID() < r2->hentID()); });
                                           //  Status etter registrering:
    cout << "\n\t\tAntall resepter hos legen nå:  "
         << resepter.size() << "\n\n";
}


/**
 *  Skriver ALT om legen til skjermen (inkl ALLE vedkommendes resepter).
 *
 *  @see      skrivHovedData()
 *  @see      Resept::skrivData()
 */
void Lege::skrivAlt() const  {
    skrivHovedData();
    for (const auto & val : resepter)
        val->skrivData();

//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//  for_each(resepter.begin(), resepter.end(),
//           [] (const auto & val) { val->skrivData();  } );
}


/**
 *  Skriver alle HOVEDdata om legen (dvs IKKE reseptene).
 */
void Lege::skrivHovedData() const  {
    cout << ", " << adresse  << ", " << tlf
         << "\n\t    #resepter:  " << resepter.size() << ":\n";
}


/**
 *  Skriver kun alle legens resepter utskrevet til pasient med nummer 'nr'.
 *
 *  @param    nr  -  pasientens unike nummer i 'Pasient'
 *  @see      skrivHovedData()
 *  @see      Resept::skrevetUtPaa(...)
 *  @see      Resept::skrivData()
 */
void Lege::skrivPasienter(const int nr) const {
    int antall = 0;                    //  Antall resepter evt. til pasienten.
    skrivHovedData();
    for (const auto & val : resepter)  //  Går gjennom alle reseptene:
        if (val->skrevetUtPaa(nr)) {   //  Utskrevet på aktuell pasient:
            antall++;                  //  Teller opp antall aktuelle.
            val->skrivData();          //  Skriver vedkommende resept.
        }
    cout << "\t\tAntall resepter hos DENNE legen:  " << antall << '\n';
}


/**
 *  Skriver ALT om legen til fil (inkl ALLE vedkommendes resepter).
 *
 *  @param    ut  -  Filobjektet det skal skrives ut til.
 *  @see      Resept::skrivTilFil(...)
 */
void Lege::skrivTilFil(ofstream & ut) const {     //  Skriver alle EGNE data:
                                     //  Skriver tlf, adr og antall resepter:
    ut << tlf << ' ' << adresse << '\n' << resepter.size() << '\n';

    for (const auto & val : resepter)             //  Alle reseptene
        val->skrivTilFil(ut);                     //    skriver ut seg selv.
}


// ---------------------------------------------------------------------------

/**
 *  Leter etter medisinnavnet 'nvn' og returnerer om mulig dets indeks+1.
 *
 *  @param    nvn  -  Aktuelt medisinnavn å finne/lete etter.
 *  @return   Indeksen+1 for 'nvn' i 'navn', evt. 0 (null) om intet funn.
 */
int  Medisiner::finn(const string nvn) const {
    for (unsigned int i = 0;  i < navn.size();  i++)
        if (navn[i] == nvn) return (i+1);
    return 0;
}


/**
 *  Returnerer (om mulig) navnet til medisinen med indeks lik 'i-1'.
 *
 *  @param    i  -  (i-1) er aktuell indeks å finne navnet for
 *  @return   Medisinnavnet for nr.'i-1', evt. bare "" (om uaktuell indeks).
 */
string Medisiner::hentNavn(const unsigned int i) const {
    if (i > 0  &&  i <= navn.size())        //  Indeks i aktuelt intervall:
        return (navn[i-1]);                 //  Retunerer medsinnavnet.
    else                                    //  Utenfor aktuelle indekser:
        cout << "\n\tIndeks for medisinnavn utenfor lovlig intervall 1-"
             << navn.size() << " !\n";
    return "";                              //  Returnerer tomt navn.
}


/**
 *  Leser inn alle aktuelle medisinnavn fra fil.
 *
 *  @param    filNavn  -  Filnavnet det skal leses inn fra.
 */
void Medisiner::lesFraFil(const string filNavn) {
    ifstream innfil(filNavn);               //  Prøver å åpne aktuell fil.
    string mNavn;                           //  Innlest medisinnavn.

    if (innfil) {                           //  Filen funnet:
        cout << "\n\tLeser medisinnavn fra 'EKS_28_MEDISINER.DTA' .....\n";

        getline(innfil, mNavn);             //  Leser (om mulig) medisinnavn.
        while (!innfil.eof()) {             //  Navn funnet:
            navn.push_back(mNavn);          //  Legges inn i vectoren.
            getline(innfil, mNavn);         //  Leser (om mulig) medisinnavn.
        }
        sort(navn.begin(), navn.end());     //  SORTERER ALLE NAVNENE !!!
        innfil.close();                     //  Lukker filen manuelt.
    } else
        cout << "\n\tFinner ikke filen 'EKS_28_MEDISINER.DTA' .....\n";
}


/**
 *  Skriver ut ALLE medisinnavnene på skjermen.
 */
void Medisiner::skrivAlle() const {
    cout << "\n\tAlle " << navn.size() << " aktuelle medisinnavn:\n";
    for (unsigned int i = 0;  i < navn.size();  i++)
        cout << "\t\t" << setw(2) << i+1 << ":  " << navn[i] << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Leter etter/legger inn pasientnavnet 'nvn' og returnerer dets indeks+1.
 *
 *  @param    nvn  -  Aktuelt pasientnavn å finne eller legge inn.
 *  @return   Indeksen+1 for 'nvn' i 'navn'
 */                                           //   IKKE 'const' da evt. legger
int Pasienter::finn(const string nvn) {       //     inn nye ikke-fundne.
    for (unsigned int i = 0;  i < navn.size();  i++)
        if (navn[i] == nvn) return (i+1);     //  Funn!  Returnerer
                                              //  Ikke funn, dvs. ny:
    navn.push_back(nvn);                      //  Legger inn bakerst.
    return navn.size();                       //  Retunerer siste indeks+1 !
}                  //  SORTERER IKKE - ellers vil pasienter bytte indeks !!!


/**
 *  Leter etter pasientnavnet 'nvn' og returnerer om mulig dets indeks+1.
 *
 *  Ulik 'finn' (rett ovenfor) - da KUN leter, men legger IKKE inn.
 *  Begge disse to funksjonene kunne selvsagt ha vært kodet som EN
 *  funksjon, og innmaten styres litt ulikt vha. parameter.
 *  Fin øvelse å evt. gjøre/skrive om dette selv......

 *  @param    nvn  -  Aktuelt pasientnavn å finne/lete etter.
 *  @return   Indeksen+1 for 'nvn' i 'navn', evt. 0 (null) om intet funn.
 */
int Pasienter::finnes(const string nvn) const {
    for (unsigned int i = 0; i < navn.size(); i++)
        if (navn[i] == nvn) return (i+1);
    return 0;
}


/**
 *  Returnerer (om mulig) navnet til pasienten med indeks lik 'i-1'.
 *
 *  @param    i  -  (i-1) er aktuell indeks å finne navnet for
 *  @return   Pasientnavnet for nr.'i-1', evt. bare "" (om uaktuell indeks).
 */
string Pasienter::hentNavn(const unsigned int i) const {
    if (i > 0  &&  i <= navn.size())
        return (navn[i-1]);
    else
        cout << "\n\tIndeks for pasientnavn utenfor lovlig intervall 1-"
             << navn.size() << " !\n";
    return "";
}


/**
 *  Leser inn alle aktuelle pasientnavn fra fil.
 *
 *  @param    filNavn  -  Filnavnet det skal leses inn fra.
 */
void Pasienter::lesFraFil(const string filNavn) {
    ifstream innfil(filNavn);               //  Prøver å åpne aktuell fil.
    string pNavn;                           //  Innlest pasientnavn.
    int    antall;                          //  Antall pasientnavn på filen.

    if (innfil) {                           //  Filen funnet:
        cout << "\n\tLeser pasientnavn fra 'EKS_28_PASIENTER.DTA' .....\n";

        innfil >> antall;   innfil.ignore();   //  Leser antall pasientnavn.
        for (int i = 1;  i <= antall;  i++) {  //  Leser disse navnene:
            getline(innfil, pNavn);
            navn.push_back(pNavn);             //  Legger BAKERST i vectoren.
        }
 // IKKE   sort(navn.begin(), navn.end());  - ellers bytter de indeks !!!
        innfil.close();                        //  Lukker filen manuelt.
    } else
        cout << "\n\tFinner ikke filen 'EKS_28_PASIENTER.DTA' .....\n";
}


/**
 *  Skriver ut ALLE pasientnavnene på skjermen.
 */
void Pasienter::skrivAlle() const {
    cout << "\n\tAlle " << navn.size() <<" hittil registrerte pasientnavn:\n";
    for (unsigned int i = 0; i < navn.size(); i++) {
        cout << "\t\t" << setw(2) << i + 1 << ":  " << navn[i] << '\n';
        if (((i + 1) % 20) == 0) {              //  Stanser for hvert 20.navn:
            cout << "\t\t\t\t\t\tSkriv ENTER/CR .....";  cin.ignore();
        }
    }
}


/**
 *  Skriver ut ALLE pasientnavnene på skjermen.
 *
 *  @param    filNavn  -  Filnavnet det skal skrives ut til.
 */
void Pasienter::skrivTilFil(const string filNavn) const {
    ofstream utfil(filNavn);               //  Åpner aktuell fil å skrive til.

    cout << "\n\tSkriver pasientnavn til 'EKS_28_PASIENTER.DT2' .....\n";

    utfil << navn.size() << '\n';          //  Skriver antall pasientnavn.
    for (const auto & val : navn)          //  Skriver alle navnene til fil:
        utfil << val << '\n';

    utfil.close();                         //  Lukker filen manuelt.
}


// ---------------------------------------------------------------------------

/**
 *  Leser inn de fleste av reseptens data fra brukeren/tastaturet.
 *  @see      Pasient::finn(...)
 */
void Resept::lesData() {
    string pNavn;                        //  Pasientnavn
    antall = lesInt("\tAntall av medisinen", 1, 200);
    dato = lesInt("\tDato               ", 200101, 251231);
    cout << "\tPasientnavn:  ";   getline(cin, pNavn);
    pasNr = gPasienter.finn(pNavn);      //  Indeksen for (nyinnlagt) pasient.
}


/**
 *  Leser ALT om resepten inn fra fil.
 *
 *  @param    inn  -  Filobjektet det leses inn fra.
 */
void Resept::lesFraFil(ifstream & inn) {
    inn >> dato >> medNr >> pasNr >> antall;   inn.ignore();
}


/**
 *  Skriver ALLE reseptens data ut på skjermen (noen nr omgjort til tekst).
 *
 *  @see      Medisin::hentNavn(...)
 *  @see      Pasient::hentNavn(...)
 */
void Resept::skrivData() const  {
    cout << "\t\t" << dato << ":  " << gMedisiner.hentNavn(medNr)
         << " (" << antall << " piller)\n\t\t\t\ttil pasient: "
         << gPasienter.hentNavn(pasNr) << '\n';
}


/**
 *  Skriver ALLE medisinens data ut til filen 'ut'.
 *
 *  @param    ut  -  Filobjektet det skrives ut til.
 */
void Resept::skrivTilFil(ofstream & ut)  const  {
    ut << dato << ' ' << medNr << ' ' << pasNr << ' ' << antall << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Fjerner (om mulig) ALLE resepter hos ALLE leger ELDRE enn en gitt dato.
 *
 *  @see   Lege::fjernResepter(...)
 */
void fjernResepter() {                   //  De FØR("!!!!) datoen fjernes:
    int fDato = lesInt("\tFjerne resepter FØR dato", 200101, 253112);
    cout << '\n';
    for (const auto & val : gLeger)  {
        cout << '\t' << val.first;
        (val.second)->fjernResepter(fDato);
    }
}


/**
 *  Skriver (om mulig) ALLE reseptene for EN navngitt lege.
 *
 *  @see   Lege::skrivAlt()
 */
void legeOversikt() {
    string legeNavn;                 //  Aktuelt legenavn å skrive ALT om.
    Lege*  lege = nullptr;           //  Peker til evt. funnet/aktuell lege.

    cout << "\tSe ALLE reseptene til lege:  ";   getline(cin, legeNavn);
    if (gLeger.find(legeNavn) != gLeger.end()) {  //  Funn !!!
       lege = gLeger[legeNavn];                   //  PEKER til Lege-objektet!
       cout << '\t' << legeNavn;
       lege->skrivAlt();                          //  Legen skriver selv.
    } else
        cout << "\n\tIngen lege med dette navnet!\n\n";
}


/**
 *  Leser ALLE leger og ALLE deres resepter inn fra fil.
 *
 *  @see   Lege::Lege(...)
 *  @see   Lege::lesFraFil(...)
 */
void lesLegerOgResepterFraFil() {
    ifstream innfil("EKS_28_LEGERRESEPTER.DTA");
    Lege* lege = nullptr;                          //  Nytt Lege-objekt.
    string lNavn;                                  //  Innlest legenavn.
    int antLeger;                                  //  Antall leger på filen.

    if (innfil) {                                  //  Filen funnet:
        cout << "\n\tLeser leger og reseptper fra "
             << "'EKS_28_LEGERRESEPTER.DTA' .....\n";

        innfil >> antLeger;   innfil.ignore();     //  Leser antall leger.
        for (int i = 1;  i <= antLeger;  i++) {    //  Leser alle legene:
            getline(innfil, lNavn);                //  Leser legens navn.
            lege = new Lege();                     //  Lager nytt Lege-objekt.
            lege->lesFraFil(innfil);               //  Leser selv egne data.
            gLeger[lNavn] = lege;                  //  LEGGES INN I <map>'en!!
        }
        innfil.close();                            //  Lukker filen manuelt.
    } else
        cout << "\n\tFinner ikke filen 'EKS_28_LEGERRESEPTER.DTA' .....\n";
}


/**
 *  Skriver (om mulig) ALLE resepter utskrevet til/på EN navngitt pasient.
 *
 *  @see   Pasient::finnes(...)
 *  @see   Lege::skrivPasienter(...)
 */
void pasientOversikt() {
    string pasNavn;                          //  Pasientnavn.
    int    pasNr;                            //  Pasientens indeks/nummer.
    cout << "\tSe ALLE reseptene til pasient:  ";   getline(cin, pasNavn);
    if ((pasNr = gPasienter.finnes(pasNavn)) != 0)  //  Navnet finnes:
        for (const auto & val : gLeger)  {
            cout << '\t' << val.first;              //  Hver lege skriver selv
            (val.second)->skrivPasienter(pasNr);    //    eventuelle resepter.
        }
    else
        cout << "\n\tIngen pasient med dette navnet!\n";
}


/**
 *  Legger inn (om medisinnavnet er blant de 20x) en ny resept.
 *
 *  @see   Medisin::finn(...)
 *  @see   Lege::Lege(...)
 *  @see   Lege::lesData()
 *  @see   Lege::registrerResept(...)
 */
void registrerResept() {
    Lege*  lege = nullptr;                   //  Peker til (evt. ny) lege.
    string medNavn,                          //  Reseptens medisinnavn.
           legeNavn;                         //  Reseptens legenavn.
    int    nr = 0;                           //  Medisinens indeks.
    bool   feilNavn = true;                  //  Antar feilskrevet med.navn!

    cout << "\n\tRegistering av ny resept:\n";
    cout << "\tMedisinnavn:  ";   getline(cin, medNavn);   //  Leser med.navn.
    nr = gMedisiner.finn(medNavn);           //  Finner dens indeks.
    while (nr == 0  &&  feilNavn)  {         //  IKKE funnet og feilskrevet:
        cout << "\t\tIkke blant de 20x det skal registreres resepter for!\n";
        if (lesChar("\t\tEr medisinnavnet korrekt skrevet (J/n)") == 'N') {
           cout << "\tMedisinnavn:  ";   getline(cin, medNavn);
           nr = gMedisiner.finn(medNavn);    //  Leser nytt med.navn.
        } else                               //  Skrevet riktig/korrekt, men
           feilNavn = false;                 //    IKKE blant de 20x aktuelle!
    }

    if (nr != 0) {                           //  Blant de 20x aktuelle:
        cout << "\tLegenavn:     ";   getline(cin, legeNavn);
        if (gLeger.find(legeNavn) == gLeger.end()) {   //  Nytt legenavn:
            lege = new Lege();               //  Ny lege opprettes,
            lege->lesData();                 //    leser selv egne data, og
            gLeger[legeNavn] = lege;         //    LEGGES INN I <map>'en !!
        }

//  INVARIANT:  Legen finnes nå!!   (enten nyinnlagt eller fantes fra før)

        lege = (gLeger.find(legeNavn))->second;   //  PEKER til Lege-objektet.

        lege->registrerResept(nr);           //  Resept registreres hos legen.

    } else
      cout << "\n\tOK. Resepten registreres derfor ikke!\n\n";
}


/**
 *  Skriver ut ALLE legenes HOVEDdata på skjermen.
 *
 *  @see   Lege::skrivHovedData()
 */
void skrivAlleLeger() {
    if (!gLeger.empty()) {                       //  Det finnes lege(r):
        for (const auto & val : gLeger)  {
            cout << '\t' << val.first;           //  Hver lege skriver selv
            (val.second)->skrivHovedData();      //   sine HOVEDdata.
        }

//  Alternativt vha. iterator:
//    for (auto it = gLeger.begin();  it != gLeger.end();  it++) {
//        cout << '\t' << it->first;
//        (it->second)->skrivHovedData();
//    }

//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gLeger.begin(), gLeger.end(),
//             [] (const auto & val) { cout << '\t' << val.first;
//                                     (val.second)->skrivHovedData();  } );
    } else
        cout << "\n\tIngen leger (og resepter) registrert foreløpig!\n\n";
}


/**
 *  Skriver ALLE leger og ALLE deres resepter ut til fil.
 *
 *  @see   Lege::skrivTilFil(...)
 */
void skrivLegerOgResepterTilFil() {
    ofstream utfil("EKS_28_LEGERRESEPTER.DT2");

    cout << "\n\tSkriver leger og reseptper til "
         << "'EKS_28_LEGERRESEPTER.DT2' .....\n";

    utfil << gLeger.size() << '\n';        //  Skriver antall leger.
    for (const auto & val : gLeger) {
        utfil << val.first << '\n';        //  Hver lege skriver selv til fil:
        (val.second)->skrivTilFil(utfil);  //  Lege-peker sin funksjon!
    }
    utfil.close();                         //  Lukker filen manuelt.
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tM - alle Medisinnavnene\n"
         << "\tN - alle pasientNavnene\n"
         << "\tA - skriv hoveddatene om Alle legene\n"
         << "\tR - Registrer en ny resept\n"
         << "\tL - oversikt over reseptene fra en bestemt Lege\n"
         << "\tP - oversikt over reseptene til en bestemt Pasient\n"
         << "\tF - Fjern alle gamle resepter\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Sletter ALLE legene og deres resepter.
 *
 *  @see   Lege::~Lege()
 */
void slettLegerOgResepter()  {
    while (!gLeger.empty())  {          //  Fortsatt IKKE tomt for leger.
        auto it = gLeger.begin();       //  PEKER til den første i <map>'en.
        delete (it->second);            //  Sletter TILPEKT 'Lege'.
        gLeger.erase(it);               //  Sletter PARET key og PEKER.
    }
}
