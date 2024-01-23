/**
 *   Løsningsforslag til oppgave nr 17.
 *
 *   Program som leser værdata fra filen "OPPG_17.DTA" og finner
 *   hvilken desemberdato som har laveste temperatur (TAN-kolonnen).
 *   (Svar:   14.12.1981  med  -20.8 grader)
 *
 *   @file    OPPG_17.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout
#include <fstream>                 //  ifstream
#include <string>                  //  string
using namespace std;


const int SKIPLINES =    24;       ///<  Antall innledende linjer å ignorere.
const int STNR      = 18700;       ///<  1.felt/tall på hver aktuelle linje.


/**
 *  Hovedprogrammet:
 */
int main() {
    string buffer,                     //  Tekst(linje) og
           dato;                       //    aktuell desemberdato.
    int    nr;                         //  1.felt/tall på linjen.

    float tam, tan,                    //  Tallene i kolonnene TAM og TAN.
          minst = 100.0F;              //  Minste des.temp (hittil).

    ifstream innfil("OPPG_17.DTA");    //  Definerer og åpner fil.

    if (innfil) {                      //  Filen finnes:
                                       //  Ignorerer innlendende linjer:
       for (int i = 1; i <= SKIPLINES; i++)   getline(innfil, buffer);

       innfil >> nr;                   //  Leser (om mulig) 1.felt/tall.
       while (!innfil.eof()  &&  nr == STNR) {  //  Fortsatt aktuelle linjer:
           innfil >> buffer;                    //  Leser datoen.

           if (buffer.substr(3, 2) == "12")  {  //  Datoen er i desember.
              innfil >> tam >> tan;             //  Leser TAM og TAN tallene.
              if (tan < minst) {                //  Ny minste temperatur?
                 minst = tan;                   //  Oppdaterer ny minste temp
                 dato = buffer;                 //    og datoen.
               }
           } 

           getline(innfil, buffer);        //  Leser uansett resten av linjen.

           innfil >> nr;                   //  Leser (om mulig) 1.felt/tall.
        }

        cout << "Kaldeste dato i desember: " << dato << "  med " << minst << '\n';
        innfil.close();

    } else
      cout << "\n\nKlarer ikke å finne/åpne filen 'OPPG_17.DTA' !\n\n";


    return 0;
}