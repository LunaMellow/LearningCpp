/**
 *   Løsning til kontinuasjonseksamen i OOProg (i C++), august 2023, oppgave 1A.
 *
 *   @file     EX_S23_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;


const int MAX = 4;


class A  {
  protected:
    vector <int> tall;

  public:
    A()  {  }
    A(const int n) {  for (int i = 1;  i < MAX;  i++)  tall.push_back(i*n);  }
    void display() const { for (const auto & val : tall) cout << val << ' '; }
    virtual bool funk(const int t) const  {  return (tall.at(1) != 15);  }
};


class B : public A {
  private:
    string txt;

  public:
   B(const int n, const string t)
      {  txt = t;  for (int i = MAX;  i < MAX*2;  i++) tall.push_back(i*n);  }
   void display2()
      {  cout << tall.front() << ' ' << tall.back() << ' ' << tall.size();   }
   virtual bool funk(const string t) const  {  return (!(txt == t));  }
};


int main() {
  A* obj1 = new A(5);
  B* obj2 = new B(3, "Raches");
  A* obj3 = new B(4, "Therma");

  obj1->display();   cout << '\n';
  obj2->display();   cout << '\n';
  cout << ((obj2->funk("Raches")) ? "Nas" : "Evdilos") << '\n';
  cout << ((obj3->funk(15)) ? "Nas" : "Evdilos")       << '\n';
  obj2->display2();  cout << ' ';
                     ((dynamic_cast <B*> (obj3)))->display2(); cout << '\n';

  return 0;
}



//  Utskrift:  5 10 15
//             12 15 18 21
//             Evdilos
//             Nas
//             12 21 4 16 28 4
