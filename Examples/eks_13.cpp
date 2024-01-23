/**
 *   Programeksempel nr 13 - Constructorer/destructorer ifm arvehierarki,
 *                           samt kall av spesifikk constructor i baseklasse.
 *
 *   @file     EKS_13.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
using namespace std;


/**
 *  3x klasse i arvehierarki ( A <-- B <-- C ) KUN med constructor/destructor:
 */
class A {
  public:
    A()        {  cout << "\tA1\n";  }    //  Kun "frivillig" dersom ingen (1)
                                          //    constr. MED parametre finnes.
    A(int aa)  {  cout << "\tA2\n";  }

    ~A()       {  cout << "Klasse A dør\n\n";  }         //                (5)
};


class B : public A {
  public:
    B()        {  cout << "\tB1\n";  }    //  Kaller automatisk A().       (3)
                                          //  Kun "frivillig" dersom ingen (1)
                                          //    constr. MED parametre finnes.
    B(int bb)  {  cout << "\tB2\n";  }    //  Prøver å utføre A().         (3)

    ~B()       { cout << "Klasse B dør\n";  }            //                (5)
};


class C : public B {
  public:
    C()        {  cout << "\tC1\n";  }    //  Kaller automatisk B().       (3)
                                          //  Kun "frivillig" dersom ingen (1)
                                          //    constr. MED parametre finnes.
    C(int cc)  {  cout << "\tC2\n";  }    //  Prøver å utføre B().         (3)

    C(int c1, int c2) : B(c1)             //  KALLER SPESIFIKK CONSTRUCTOR (2)
               {  cout << "\tC3\n";  }    //    I BASEKLASSEN !!!

    ~C()       {  cout << "Klasse C dør\n";  }           //                (5)
};


/**
*  Hovedprogrammet:
*/
int main() {

    cout << "\n\nLager objekter UTEN parametre:\n";
    cout << "A:";   A aobj1;              //  Utskrift:  A1                (4)
    cout << "B:";   B bobj1;              //  Utskrift:  A1  B1            (4)
    cout << "C:";   C cobj1;              //  Utskrift:  A1  B1  C1        (4)

    cout << "\n\nLager objekter MED parametre:\n";
    cout << "A:";   A aobj2(1);           //  Utskrift:  A2                (4)
    cout << "B:";   B bobj2(2);           //  Utskrift:  A1  B2            (4)
    cout << "C:";   C cobj2(3);           //  Utskrift:  A1  B1  C2        (4)

    cout << "\n\nConstructor med to parametre og kall til spesifikk ";
    cout << "constructor i baseklasse:\n";
    cout << "C:";   C cobj3(4, 5);        //  Utskrift:  A1  B2  C3        (4)

  cout << "\nLOKALE objekter slettes baklengs ift. definisjonsrekkefølgen:\n";
    return 0;
}

// ***************************************************************************
// **   Noen fakta om CONSTRUCTORER:                                        **
// **    (1)  - Dersom det lages en constructor MED parametre, så BØR også  **
// **           klassen inneholde en constructor UTEN parametre             **
// **           (evt. med tom funksjonsinnmat/"kropp").                     **
// **    (2)  - I en avledet klasses constructor KAN man manuelt tilkalle   **
// **           en spesiell constructor i baseklassen (vha. parametre).     **
// **           (Men IKKE spesielle videre oppover i arvetreet.)            **
// **    (3)  - Når intet eksplisitt er kodet, så vil alle baseklassenes    **
// **           constructorer (uten parametre) prøves automatisk utført.    **
// **           (KUN OK at de ikke finnes, dersom baseklassene ei heller    **
// **           inneholder constructorer MED parametre.)                    **
// **    (4)  - Egen eksekveres/kjøres ETTER alle baseklassenes.            **
// **                                                                       **
// **   DESTRUCTORER:                                                       **
// **    (5)  - Egen eksekveres/kjøres FØR alle baseklassenes.              **
// ***************************************************************************
