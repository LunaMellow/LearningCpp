/**
 *   @file     EKS_27FUNC.CPP
 *   @author   Frode Haug, NTNU
 */

#include <iostream>
#include <string>
#include "EKS_27CLASS.H"        //  'Personbase'
#include "EKS_27FUNC.H"         //  'ny'
using namespace std;

                          //  Global variabel DEFINERT i EKS_27MAIN.CPP: !!!!!
extern Personbase* gPersoner;   //  Bruker nøkkelordet 'extern' !!!


void ny()  {                    //  Leser navn og legger inn ny person.
    string navnet;
    cout << "\n\nPerson-navn:      ";
    getline(cin, navnet);
    gPersoner->nyPerson(navnet);
}