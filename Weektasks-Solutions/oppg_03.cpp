/**
 *   Løsningsforslag til oppgave nr 3.
 *
 *   Modifisert utgave av løsningen til oppgave nr 2: med bruk av funksjoner.
 *
 *   @file    OPPG_03.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>          //  cout, cin
#include <iomanip>           //  setw
using namespace std;


const int MINTEMP   = -70;   ///<  Absolutt laveste mulige temperatur.
const int MAXTEMP   =  70;   ///<  Absolutt høyeste mulige temperatur.
const int MAXNEDBOR = 200;   ///<  Absolutt høyeste mulige nedbør pr.døgn.
const int MINDAGER  =  28;   ///<  Minimum antall dager i en måned.
const int MAXDAGER  =  31;   ///<  Maksimum antall dager i en måned.


float gjennomsnitt(const int verdi1, const int verdi2);
int lesTall(const char t[], const int min, const int max);


/**
 *  Hovedprogrammet:
 */
int main ()  {
  int svar,                 //  Brukersvar til om vil fortsette eller ei.
      antDager,             //  Antall dager i aktuell måned.
      min,                  //  Min.temp EN gitt dag.
      nedbor,               //  Nedbør EN gitt dag.
      totMin,               //  TOTALT min.grader i aktuell måned.
      totMax,               //  TOTALT max.grader i aktuell måned.
      totNedbor,            //  TOTALT nedbør i aktuell måned.
      mestNedbor,           //  Mest nedbør falt på en dag.
      nedborDag;            //  Dagnummeret med mest nedbør.

  svar = lesTall("\nLese inn værdata for en måned", 0, 1);   //  Kjøre programmet?

  while (svar == 1)  {       //  Ennå IKKE svart '0':
                             //  Leser antall dager i måneden (28-31):
     antDager = lesTall("Antall dager i måneden", MINDAGER, MAXDAGER);

     totMin = totMax = totNedbor = 0;     //  MÅ huske å nullstille/
     mestNedbor = -1;    nedborDag = 0;   //    initiere variable!

     for (int i = 1;  i <= antDager;  i++)  { //  Går gjennom HELE måneden:
         cout << "\nDag nr." << setw(2) << i << ":\n";
                                          //  Leser korrekt min.temp dag nr.i:
         min = lesTall("Minimumstemp", MINTEMP, MAXTEMP);
         totMin += min;                   //  Summerer totalen.
                                          //  Leser korrekt max.temp dag nr.i:
         totMax += lesTall("Maksimumstemp", min, MAXTEMP); //Summerer totalen.
                                          //  Leser korrekt nedbør dag nr.i:
         nedbor = lesTall("Nedbør", 0, MAXNEDBOR);
         totNedbor += nedbor;             //  Summerer totalen.

         if (nedbor > mestNedbor) {       //  Ny nedbørsrekord?
             mestNedbor = nedbor;         //  Lagrer unna rekorden,
             nedborDag = i;               //    og på hvilken dag.
         }
     }
                                    //  Skriver gjennomsnitter og EN totalsum:
     cout << "\n\nGjennomsnittlig min.temp: "
          << gjennomsnitt(totMin, antDager) << " grader C\n";
     cout << "Gjennomsnittlig max.temp: "
          << gjennomsnitt(totMax, antDager) << " grader C\n";
     cout << "Gjennomsnittlig nedbør:   "
          << gjennomsnitt(totNedbor, antDager) << " mm\n";
     cout << "Total nedbør i måneden:   " << totNedbor <<  " mm\n";
     cout << "Det falt mest nedbør på dag nr."
          << nedborDag << " med " << mestNedbor << " mm\n";
                                             //  Kjøre programmet igjen?
     svar = lesTall("\nLese inn værdata for en måned til", 0, 1);
  }

  cout << "\n\n\nHa en fortsatt god (vær(syk))dag!\n\n";

  return 0;
}


/**
 *  Funksjon som beregner float-gjennomsnittet av to int-verdier.
 *
 *  @param     verdi1  - int-verdien over brøkstreken
 *  @param     verdi2  - int-verdien under brøkstreken
 *  @return    float-verdien av   verdi1 / verdi2
 */
float gjennomsnitt(const int verdi1, const int verdi2) {
    return(static_cast <float> (verdi1) / verdi2);
}


/**
*  Leser og returnerer et heltall mellom to gitte grenser.
*
*  @param   t    - Ledetekst til brukeren når ber om input/et tall
*  @param   min  - Minimum for innlest og godtatt tallverdi
*  @param   max  - Maksimum for innlest og godtatt tallverdi
*  @return  Godtatt verdi i intervallet 'min' - 'max'
*/
int lesTall(const char t[], const int min, const int max)  {
    int tall;
    do {
       cout << t << " (" << min << " - " << max << "):  ";
       cin >> tall;
    } while (tall < min || tall > max);
    return tall;
}
