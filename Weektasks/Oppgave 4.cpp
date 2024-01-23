
/**     What time is largest?
 *
 *      Program description:
 *          - Take different times
 *          - Check which is largest
 *          - Print out the result
 *
 *      @file Oppgave 4.cpp
 *      @date 23-Jan-24
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

// Includes
#include <iostream>

// Namespace
using namespace std;

// Struct Declarations
struct Tid {
    int time,
        minutt,
        sekund;
};

// Functions
struct Tid storst(const struct Tid tid1, const struct Tid tid2);

/**
 *      Main Program starts here
 *
 *      @see storst(...)
 */
int main() {

    struct Tid tid1 = {12, 30, 45};
    struct Tid tid2 = {11, 45, 30};
    struct Tid tid3 = {13, 15, 20};
    struct Tid tid4 = {12, 30, 45};

    struct Tid storsteTid = storst(storst(tid1, tid2), storst(tid3, tid4));

    cout << "Av de fire tid-structene er: " << storsteTid.time << " timer, "
        << storsteTid.minutt << " minutter, og " << storsteTid.sekund << " sekunder.\n";

    return 0;
}

/**
 *  Finds which of the given time structs is larger
 *
 *  @param tid1 - First time struct
 *  @param tid2 - Second time struct
 *
 *  @return the larger struct
 */
struct Tid storst(const struct Tid tid1, const struct Tid tid2) {

    if (tid1.time > tid2.time)              return tid1;
    else if (tid2.time > tid1.time)         return tid2;
    else if (tid1.minutt > tid2.minutt)     return tid1;
    else if (tid2.minutt > tid1.minutt)     return tid2;
    else if (tid1.sekund > tid2.sekund)     return tid1;
    else                                    return tid2;

}