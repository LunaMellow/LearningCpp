/**
 *   L�sningsforslag til oppgave nr 15.
 *
 *   @file    OPPG_15.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


/**
 *  Kj�ret�y (med registreringsnummer).
 */
class Kjoretoy  {
  private:
      string regNr;

  public:                            //  3x virtuelle funksjoner:
      virtual void lesData()  {  cout << "\tRegnr:  ";  getline(cin, regNr); }

      virtual void skrivData() const {  cout << "\tRegnr:  " << regNr;   }
                            // Pure virtual: n�rmeste sublasser M� lage den !!
      virtual bool tomt() const = 0; 
};


/**
 *  Bil (med antall n�v�rende passasjerer i bilen).  
 */
class Bil : public Kjoretoy  {
  private:
      int antPassasjerer;

  public:
      virtual void lesData()  { 
          Kjoretoy::lesData();
          antPassasjerer = lesInt("\tN�v�rende antall passasjerer", 0, 6);  }

      virtual void skrivData() const {
          Kjoretoy::skrivData();
          cout << ",  #passasjerer pt: " << antPassasjerer << '\n';
      }

      virtual bool tomt() const {  return (antPassasjerer == 0);  }
};


/**
 *  Vogntog (med n�v�rende antall tonn i lasten).
 */
class Vogntog : public Kjoretoy  {
  private:
      float tonnLast;

  public:
      virtual void lesData() {
          Kjoretoy::lesData();
          tonnLast = lesFloat("\tN�v�rende tonn last", 0, 50);
      }

      virtual void skrivData() const {
          Kjoretoy::skrivData();
          cout << ",  #tonn last pt: " << tonnLast << '\n';
      }

      virtual bool tomt() const  { return (tonnLast == 0.0F); }
};


vector <Kjoretoy*>  gKjoretoyene;    ///<  Datastruktur med ulike objekter(!).


/**
 *  Hovedprogrammet:
 */
int main ()  {
    Kjoretoy* nyttKjoretoy;
    char type;
    int  i, antallKjoretoy;

    do {
        do {
            type = lesChar("B(il) eller V(ogntog)");
        } while (type != 'B'  &&  type != 'V');
                                           //  Lager ny inn Bil eller Vogntog:
        if (type == 'B')  nyttKjoretoy = new Bil;
        else              nyttKjoretoy = new Vogntog;

        nyttKjoretoy->lesData();           //  Leser aktuelt objekts data:

        gKjoretoyene.push_back(nyttKjoretoy);  //  Legger inn i vectoren.

    } while (lesChar("\nLegge inn flere biler/vogntog (J/n)") != 'N');


    antallKjoretoy = gKjoretoyene.size();      //  Unnalagrer antall kj�ret�y:
    cout << "\n\nAntall kj�ret�y: " << antallKjoretoy << "\n\n";


    for (i = 0; i < antallKjoretoy; i++) {     //  Skriver ALLE kj�ret�yene:
        cout << "Kj�ret�y nr. " << i+1 << ":  ";
        gKjoretoyene[i]->skrivData();
    }

                                               //  Skriver nr. til de tomme:
    cout << "\n\nKj�ret�y som er tomme (for passasjerer eller last):\n\tNr:";
    for (i = 0; i < antallKjoretoy; i++)
        if (gKjoretoyene[i]->tomt())  cout << "  " << i+1;


    for (i = 0; i < antallKjoretoy; i++)
        delete gKjoretoyene[i];                //  Sletter ALLE kj�ret�yene,
    gKjoretoyene.clear();                      //    og  ALLE pekerne til dem. 


    cout << "\n\n";

    return 0;
}