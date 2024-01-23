/**
 *   Løsning til eksamen i OOProg (i C++), mai 2023, oppgave 1A.
 *
 *   @file     EX_V23_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>     //  'find' skriver evt. startindeksen for tekstmatch
using namespace std;


class X  {
  protected:
    string nvn;
    bool   student;

  public:
    X(const string t, const bool s) { nvn = t;  student = s; }
    virtual void display() const { cout << nvn << ' ' << student; }
    void har(const string t) const  {  cout << nvn.find(t);  }
    bool lik(const bool s) const  {  return (student == s);  }
    virtual bool ulik(const string t) const  {  return (nvn != t);  }
};


class Y : public X {
  private:
    int  alder;

  public:
    Y(const string t, const bool s, const int a) : X(t, s)  {  alder = a;  }
    virtual void display() const  {  X::display();  cout << ", " << alder;  }
    bool lik(const string t) const  {  return (nvn == t);  }
    virtual bool ulik(const int a) const  {  return (alder != a);  }
};


int main() {
  Y* student1 = new Y("Iris", true, 20);
  X* student2 = new X("Arne", false);
  Y* student3 = new Y("Mari", true, 21);

  student3->display();  cout << "   ";  student2->display();   cout << '\n';
  cout << student1->ulik(21) << "   " << student2->ulik("Arna")     << '\n';
  student1->har("is");  cout << "   ";  student3->har("r");    cout << '\n';
  cout << ((student2->lik(true))   ? "AIM" : "MIA") << '\n';
  cout << ((student1->lik("Irma")) ? "MAI" : "MIA") << '\n';

  delete student1;  delete student2;  delete student3;
  return 0;
}



//  Utskrift:  Mari 1, 21   Arne 0
//             1   1
//             2   2
//             MIA
//             MIA
