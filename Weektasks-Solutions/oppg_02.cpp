/**
 *   Løsningsforslag til oppgave nr 2 (basert på eksempel nr 17 i PROG1001).
 *
 *   @file    OPPG_02.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>          //  cout, cin
#include <iomanip>           //  setw
#include <cctype>            //  toupper
using namespace std;


const int MINTEMP   = -70;   ///<  Absolutt laveste mulige temperatur.
const int MAXTEMP   =  70;   ///<  Absolutt høyeste mulige temperatur.
const int MAXNEDBOR = 200;   ///<  Absolutt høyeste mulige nedbør pr.døgn.
const int MINDAGER  =  28;   ///<  Minimum antall dager i en måned.
const int MAXDAGER  =  31;   ///<  Maksimum antall dager i en måned.


/**
 *  Hovedprogrammet:
 */
int main ()  {
  char svar;                 //  Brukersvar til om vil fortsette eller ei.
  int  antDager,             //  Antall dager i aktuell måned.
       min,                  //  Min.temp EN gitt dag.
       max,                  //  Max.temp EN gitt dag.
       nedbor,               //  Nedbør EN gitt dag.
       totMin,               //  TOTALT min.grader i aktuell måned.
       totMax,               //  TOTALT max.grader i aktuell måned.
       totNedbor,            //  TOTALT nedbør i aktuell måned.
       mestNedbor,           //  Mest nedbør falt på en dag.
       nedborDag;            //  Dagnummeret med mest nedbør.

  cout << "\nLese inn værdata for en måned (J/n): ";   //  Kjøre programmet?
  cin >> svar;   svar = toupper(svar);


  while (svar != 'N')  {     //  Ennå IKKE svart 'N':
     do {                    //  Leser antall dager i måneden (28-31):
        cout << "Antall dager i måneden ("
             << MINDAGER << '-' << MAXDAGER << "):  ";
        cin >> antDager;
     } while (antDager < MINDAGER  ||  antDager > MAXDAGER);

     totMin = totMax = totNedbor = 0;     //  MÅ huske å nullstille/
     mestNedbor = -1;    nedborDag = 0;   //    initiere variable!

     for (int i = 1;  i <= antDager;  i++)  { //  Går gjennom HELE måneden:
         cout << "\nDag nr." << setw(2) << i << ":\n";

         do {                             //  Leser korrekt min.temp dag nr.i:
             cout << "\tMinimumstemp (" << setw(2) << MINTEMP
                  << " til " << setw(2) << MAXTEMP << "):  ";
             cin >> min;
         } while(min < MINTEMP ||  min > MAXTEMP);
         totMin += min;                   //  Summerer totalen.

         do {                             //  Leser korrekt max.temp dag nr.i:
             cout << "\tMaksimumstemp (" << setw(2) << min
                  << " til " << setw(2) << MAXTEMP << "):  ";
             cin >> max;
         } while(max < min  ||  max > MAXTEMP);
         totMax += max;                   //  Summerer totalen.

         do {                             //  Leser korrekt nedbør dag nr.i:
            cout << "\tNedbør (0 til " << MAXNEDBOR << "): ";
            cin >> nedbor;
         } while(nedbor < 0  ||  nedbor > MAXNEDBOR);
         totNedbor += nedbor;             //  Summerer totalen.

         if (nedbor > mestNedbor) {       //  Ny nedbørsrekord?
             mestNedbor = nedbor;         //  Lagrer unna rekorden,
             nedborDag = i;               //    og på hvilken dag.
         }
     }

                                    //  Skriver gjennomsnitter og EN totalsum:
     cout << "\n\nGjennomsnittlig min.temp: "
          << static_cast <float> (totMin) / antDager << " grader C\n";
     cout << "Gjennomsnittlig max.temp: "
          << static_cast <float> (totMax) / antDager << " grader C\n";
     cout << "Gjennomsnittlig nedbør:   "
          << static_cast <float> (totNedbor) / antDager << " mm\n";
     cout << "Total nedbør i måneden:   " << totNedbor <<  " mm\n";
     cout << "Det falt mest nedbør på dag nr."
          << nedborDag << " med " << mestNedbor << " mm\n";

                                             //  Kjøre programmet igjen?
     cout << "\nLese inn værdata for en måned til (J/n): ";
     cin >> svar;   svar = toupper(svar);
  }

  cout << "\n\n\nHa en fortsatt god (vær(syk))dag!\n\n";

  return 0;
}