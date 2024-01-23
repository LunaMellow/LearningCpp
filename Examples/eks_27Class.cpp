/**
 *   @file     EKS_27CLASS.CPP
 *   @author   Frode Haug, NTNU
 */

#include <iostream>
#include <string>
#include "EKS_27CONST.H"        //  'MAXALDER'
#include "EKS_27STRUCT.H"       //  'Person'
#include "EKS_27CLASS.H"        //  'Personbase'
#include "LesData3.h"           //  Verktøykasse for lesing av diverse data
                                //  NB:  LesData3.h - nr.3 !!!
using namespace std;


Personbase :: Personbase()  {         //  Initierer evt. 'Personbase'

}


Personbase ::  ~Personbase()  {       //  Sletter alt i vectoren:
  for (int i = 0; i < personer.size(); i++)
      delete personer[i];
  personer.clear();
}


void Personbase :: nyPerson(const string & nvn)  {
     Person* nyPerson = new Person;
     nyPerson->navn  = nvn;
     nyPerson->alder = lesInt("Alder", 0, MAXALDER);
     personer.push_back(nyPerson);
}


void Personbase :: display() const {
  cout << "\n\nPERSONBASENS INNHOLD:\n";
  for (const auto & val : personer)
      cout << "\tNavn:  " << val->navn << ",  alder: " << val->alder << '\n';
}
