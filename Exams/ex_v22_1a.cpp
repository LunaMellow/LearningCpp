/**
 *   Løsning til eksamen i OOProg (i C++), mai 2022, oppgave 1A.
 *
 *   @file     EX_V22_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
using namespace std;


class A {
  private:
    string txt;
    char ch;

  public:
    A(const string t, const char c) { txt = t;  ch = c; }
    virtual void display() const { cout << txt << ' ' << ch << ' '; }
    bool erLik(const string t) const { return (txt == t); }
};


class B : public A {
  private:
    string txt1, txt2;

  public:
    B(const string t1, const string t2, const string t3, const char c)
      : A(t3, c)  {  txt1 = t2;   txt2 = t1;  }
    virtual void display() const
      {  A::display();  cout << txt2 << ' ' << txt1;  }
    bool erLik(const string t) const
      {  return (txt1 == t  ||  txt2 == t);  }
    bool erLik(const B & b) const
      {  return (txt1 == b.txt1  ||  txt2 == b.txt2);  }
};


int main() {
    B* bobj1 = new B("Tore", "Brug", "Avik", 'x');
    bobj1->display();                              cout << '\n';
    A* bobj2 = new B("Anne", "Brud", "Haug", '-');
    bobj2->display();                              cout << '\n';
    cout << ((bobj1->erLik("Tore"))  ? "A&T" : "T&A")   << '\n';
    cout << (!(bobj2->erLik("Haug")) ? "A&T" : "T&A")   << '\n';
    cout << ((bobj1->erLik(*(dynamic_cast <B*> (bobj2)))) ? "A&T" : "T&A") << '\n';
    delete bobj1;   delete bobj2;
    return 0;
}



//  Utskrift:  Avik x Tore Brug
//             Haug - Anne Brud
//             A&T
//             T&A
//             T&A
