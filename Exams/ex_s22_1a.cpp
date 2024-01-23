/**
 *   Løsning til kontinuasjonseksamen i OOProg (i C++), august 2022, oppgave 1A.
 *
 *   @file     EX_S22_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


class A {
  protected:
    int aa1, aa2;

  public:
    A()  { aa1 = 30;  aa2 = 17;  }
    A(const int a1, const int a2)  {  aa1 = a1;  aa2 = a2;  }
    virtual void display() const   {  cout << aa2 << ' ' << aa1 << ' ';  }
    virtual bool erLik(const int aa) const  {  return (aa1 == aa);  }
};


class B : public A {
  private:
    int bb1, bb2;
  public:
    B(const int b1, const int b2) { bb1 = b1;  bb2 = b2; }
    B(const int b1, const int b2, const int b3, const int b4) : A(b3, b2)
       {  bb1 = b4;  bb2 = b1;  }
    void display() const  {  A::display();  cout << bb1 << ' ' << bb2;  }
    bool erLik(const int bb) const
                               {  return(aa1 % 20 == bb  ||  bb1 % 10 == bb);  }
};


int main() {
    A ob1, ob2(17, 8);      ob1.display();  ob2.display();    cout << '\n';
    B* ob3 = new B(30, 5);           ob3->display();          cout << '\n';
    B* ob4 = new B(29, 6, 26, 9);    ob4->display();          cout << '\n';
    cout << (ob2.erLik(17)) << ' ' << (!ob1.erLik(17)) << '\n';
    cout << (ob4->erLik(6)) << ' ' << (ob3->erLik(4))  << '\n';
    return 0;
}



//  Utskrift:  17 30 8 17
//             17 30 30 5
//             6 26 9 29
//             1 1
//             1 0
