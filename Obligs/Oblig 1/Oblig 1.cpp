
/**     Oblig 1
 *
 *      Program description:
 *          - User command input
 *          - Add or show restaurants reviewed
 *          - Flush the memory and exit
 *
 *      @file Oblig 1.cpp
 *      @date 09-Feb-24
 *
 *      @author Luna Sofie Bergh
 *      @alias LunaMellow
 */

// Includes
#include <iostream>
#include <vector>
#include "LesData2.h"       // Toolbox to read numbers and chars

// Namespace
using namespace std;

// Struct declarations
struct Restaurant {
    string navn,
            adresse,        // Gateadresse i en og samme by
            type,           // Indisk, japansk, thai, italiensk, gresk, ....
            omtale;         // Lengre evaluering/bekrivelse/vurdering
    int terningkast;        // Verdien 1 - 6
};

// Struct initialization
vector <Restaurant*> gRestauranter;

// Function declarations
void nyRestaurant();
void restaurantLesData(Restaurant & restaurant);
void restaurantSkrivData(const Restaurant* restaurant);
void skrivAlleRestauranter();
void skrivMeny();
void slettAlt();

/**
 *  @brief   -   Main program
 *  @see     -   nyRestaurant(...)
 *               skrivAlleRestauranter(...)
 *               skrivMeny(...)
 *               lesChar(...)
 *               slettAlt(...)
 */
int main() {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
            case 'N': nyRestaurant();               break;
            case 'V': skrivAlleRestauranter();      break;
            default:  skrivMeny();                  break;
        }
        kommando = lesChar("\nKommando");
    }

    slettAlt(); // Flush the memory
    return 0;
}

/**
 *  @brief   -   Creates new restaurant struct
 *  @see     -   restaurantLesData(...)
 */
void nyRestaurant() {
    cout << "\nOpprett ny restaurant"
            "\n-----------------------\n";

    // Creates and reads data into new restaurant struct
    auto nyRestaurant = new Restaurant;
    gRestauranter.push_back(nyRestaurant);
    restaurantLesData(*nyRestaurant);
}

/**
 *  @brief              -   Reads user input into given restaurant
 *  @see                -   lesInt(...)
 *  @param restaurant   -   Restaurant struct
 */
void restaurantLesData(Restaurant & restaurant) {
    cout << "\tNavn: ";         getline(cin, restaurant.navn);
    cout << "\tAdresse: ";      getline(cin, restaurant.adresse);
    cout << "\tType: ";         getline(cin, restaurant.type);
    cout << "\tOmtale: ";       getline(cin, restaurant.omtale);
    restaurant.terningkast =    lesInt("\tTerningkast", 1, 6);
}

/**
 *  @brief              -   Writes everything about a given restaurant
 *  @param restaurant   -   Restaurant struct
 */
void restaurantSkrivData(const Restaurant* restaurant) {
    cout << "\n"                  << restaurant->navn         << endl;
    cout << "\tAdresse: "         << restaurant->adresse      << endl;
    cout << "\tType: "            << restaurant->type         << endl;
    cout << "\tOmtale: "          << restaurant->omtale       << endl;
    cout << "\tTerningkast: "     << restaurant->terningkast  << endl;
    cout << endl;
}

/**
 *  @brief   -   Writes out every restaurant
 *  @see     -   restaurantSkrivData(...)
 */
void skrivAlleRestauranter() {
    cout << "\nAlle restauranter"
            "\n-----------------------";

    // Loop through all restaurants and write the data
    for (const auto& restaurant : gRestauranter) {
        restaurantSkrivData(restaurant);
    }
}

/**
 *  @brief   -   Writes out the menu to the terminal
 */
void skrivMeny() {
    cout << "\nMeny"
            "\n-----------------------"
            "\nN - Ny restaurant"
            "\nV - Vis restaurantene"
            "\n"
            "\nQ - Quit"
            "\n-----------------------";
}

/**
 *  @brief   -   Deletes all data in all restaurant structs
 */
void slettAlt() {

    // Delete all data from structs
    while (!gRestauranter.empty()) {                    //  As long as POINTERS in the vector:
        delete gRestauranter[gRestauranter.size()-1];   //  Deletes the LAST POINTED-TO.
        gRestauranter.pop_back();                       //  Deletes/Removes the POINTER itself.
    }
    cout << "\nVectoren er tom\nAntall restauranter er: " << gRestauranter.size() << "\n";
}