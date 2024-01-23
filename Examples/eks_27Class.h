
#ifndef __EKS_27CLASS_H
#define __EKS_27CLASS_H

#include <string>
#include <vector>
#include "EKS_27STRUCT.H"              //  'Person'

//  IKKE BRUK "using namespace std;" I H-FILER !!!!!
//  Skriv istedet "std::" der det trengs!


class Personbase  {
 private:
   std::vector <Person*> personer;     //  vector med pekere til 'Person'er.

 public:
   Personbase();
   ~Personbase();
   void nyPerson(const std::string & nvn);
   void display() const;
};

#endif