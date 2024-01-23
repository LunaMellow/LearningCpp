/**
 *   L�sningsforslag til oppgave nr 9.
 *
 *   Program som lager, leser inn, skriver ut og sammenligner to datoer.
 *
 *   @file    OPPG_09.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


/**
 *  Dato (med dag, m�ned og �r).
 */
class Dato  {
  private:
    int  dag,
         maaned,
         aar;
  public:
      Dato()  {
          dag = maaned = 1;  aar = 2000;
      }

      Dato(int d, int m, int a)  {
          dag = d;   maaned = m;   aar = a;
      }

      void lesData()  {
          dag    = lesInt("\tDag  ", 1, 30);
          maaned = lesInt("\tM�ned", 1, 12);
          aar    = lesInt("\t�r   ", 1600, 2100);
      }

      void skrivData() const  {
          cout << dag << '/' << maaned << '-' << aar << '\n';
      }

      bool sammeAar(const Dato dato) const  {
          return (aar == dato.aar);
      }

      bool sammeAarsdag(const Dato dato) const  {
          return (dag == dato.dag  &&  maaned == dato.maaned);
      }

      bool tidligereEnn(const Dato dato) const;   //  Kun prototype - def. nedenfor.
};


/**
 *  Hovedprogrammet:
 */
int main ()  {
    Dato  dato1,
          dato2(7, 6, 2000);

    cout << "\n\nOpplysninger om 'dato1':\n";
    dato1.lesData();

    cout << "\n'dato1' er:   ";
    dato1.skrivData();
    cout << "'dato2' er:   ";
    dato2.skrivData();
    cout << "\n\n";

    cout << "Datoene er " << ((!dato1.sammeAar(dato2)) ? "IKKE " : "")
         << "i det samme �ret.\n\n";

    cout << "Datoene er " << ((!dato1.sammeAarsdag(dato2)) ? "IKKE " : "")
        << "samme dag i �ret.\n\n";


    if (dato1.sammeAarsdag(dato2) && dato1.sammeAar(dato2))
        cout << "Datoene er HELT like!";
    else if (dato1.tidligereEnn(dato2))
        cout << "'dato1' kommer F�R 'dato2'";
    else
        cout << "'dato2' kommer F�R 'dato1'";


    cout << "\n\n";

    return 0;
}


/**
 *  Finner ut og returnerer om egen dato er tdligere enn parameteren 'dato'.
 *
 *  @param    dato  - Dato-objekt � sammenligne egen dato med
 *  @return   Egen dato er tidligere (true) eller ei enn parameterens (false)?
 */
bool Dato::tidligereEnn(const Dato dato) const  {
    int antDager1 = dag + (maaned * 30);        //  Beregner ca.dagnr i �ret:
    int antDager2 = dato.dag + (dato.maaned * 30);

    for (int i = 1600; i < aar; i++)            //  TOTALT ca. antall dager
        antDager1 += 365;                       //    siden laveste �r (1600):
    for (int i = 1600; i < dato.aar; i++)
        antDager2 += 365;

    return (antDager1 < antDager2);             //  Egen dato f�r eller ei?
}
