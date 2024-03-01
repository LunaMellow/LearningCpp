
/**     Oblig 2
 *
 *      Program description:
 *          - Create objects for different animals, both airborn and waterbased
 *          - Reads in necessary data about them
 *          - Then creates a subset of all of the wildlife
 *
 *      @file Oblig 1.cpp
 *      @date 26-Feb-2024
 *
 *      @author Luna Sofie Bergh
 *      @alias LunaMellow
 */

// Includes
#include <iostream>
#include <string>
#include "LesData2.h"

// Namespace
using namespace std;

// Function declarations
void skrivMeny();

/**
 *  @brief The Dyr class represents an animal
 */
class Dyr{
private:
    string navn;
public:

    /**
    *   @brief Default constructor
    *   Initializes the Dyr object by calling lesData()
    */
    Dyr(){
        lesData();
    };

    /**
     *  @brief Constructor with name parameter
     *  @param navn The name of the animal
     */
    Dyr(string navn){
        this->navn = navn;
    };

    /**
     *  @brief Reads data for the animal
     */
    void lesData(){
        cout << "\tNavn: ";
        getline(cin, navn);
    };

    /**
     *  @brief Writes data for the animal
     */
    void skrivData(){
        cout << "\tNavn: " << navn << "\n";
    };
};

/**
 *  @brief The DyrIVann class represents water based animals
 */
class DyrIVann : public Dyr{
private:
    int vekt;
public:

    /**
     *   @brief Default constructor
     *   Initializes the DyrIVann object by calling lesData()
     */
    DyrIVann(){
        lesData();
    };

    /**
     * @brief Constructor with name parameter
     * @param navn The name of the animal
     */
    DyrIVann(string navn) : Dyr(navn){
        lesData();
    };

    /**
     *  @brief Reads data for the animal
     */
    void lesData(){
        vekt = lesInt("Vekt", 0, 1000);
    };

    /**
     *  @brief Writes data for the animal
     */
    void skrivData(){
        Dyr::skrivData();
        cout << "\tVekt: " << vekt << " gram\n";
    };
};

/**
 *  @brief The Fisk class represents fish
 */
class Fisk : public DyrIVann{
private:
    int lengde;
public:

    /**
     *   @brief Default constructor
     *   Initializes the Fisk object by calling lesData()
     */
    Fisk(){
        lesData();
    };

    /**
     * @brief Constructor with name parameter
     * @param navn The name of the fish
     */
    Fisk(string navn) : DyrIVann(navn){
        lesData();
    };

    /**
     *  @brief Reads data for the fish
     */
    void lesData(){
        lengde = lesInt("Lengde", 0, 100);
    };

    /**
     *  @brief Writes data for the fish
     */
    void skrivData(){
        cout << "\nFisk:\n";
        DyrIVann::skrivData();
        cout << "\tLengde: " << lengde << " cm\n";
    };
};

/**
 *  @brief The Skalldyr class represents shellfish
 */
class Skalldyr : public DyrIVann{
private:
    int smakskala;
public:

    /**
     *   @brief Default constructor
     *   Initializes the Skalldyr object by calling lesData()
     */
    Skalldyr(){
        lesData();
    };

    /**
     *  @brief Reads data for the shellfish
     */
    void lesData(){
        smakskala = lesInt("Hvor godt smaker den", 1, 10);
    };

    /**
     *  @brief Writes data for the shellfish
     */
    void skrivData(){
        cout << "\nSkalldyr:\n";
        DyrIVann::skrivData();
        cout << "\tRating (1 - 10): " << smakskala << "\n";
    };
};

/**
 *  @brief The DyrILuft class represents airborn animals
 */
class DyrILuft : public Dyr{
private:
    bool trekkdyr;
public:

    /**
     *   @brief Default constructor
     *   Initializes the DyrILuft object by calling lesData()
     */
    DyrILuft(){
        lesData();
    };

    /**
     *  @brief Reads data for the animal
     */
    void lesData(){
        char trekk = lesChar("\tTrekkdyr (y/n)");
        trekkdyr = (trekk == 'Y');
    };

    /**
     *  @brief Writes data for the animal
     */
    void skrivData(){
        Dyr::skrivData();
        cout << "\tTrekkdyr: " << (trekkdyr ? "Ja" : "Nei") << "\n";
    };
};

/**
 *  @brief The Fugl class represents birds
 */
class Fugl : public DyrILuft{
private:
    int vingespann;
public:

    /**
     *   @brief Default constructor
     *   Initializes the Fugl object by calling lesData()
     */
    Fugl(){
        lesData();
    };

    /**
     *  @brief Reads data for the bird
     */
    void lesData(){
        vingespann = lesInt("\tVingespann", 0, 100);
    };

    /**
     *  @brief Writes data for the bird
     */
    void skrivData(){
        cout << "\nFugl:\n";
        DyrILuft::skrivData();
        cout << "\tVingespann: " << vingespann << " cm\n";
    };
};

/**
 *  @brief The Insekt class represents insects
 */
class Insekt : public DyrILuft{
private:
    int bein;
public:

    /**
     *   @brief Default constructor
     *   Initializes the Insekt object by calling lesData()
     */
    Insekt(){
        lesData();
    };

    /**
     *  @brief Reads data for the insect
     */
    void lesData(){
        bein = lesInt("\tAntall bein", 0, 1000);
    };

    /**
     *  @brief Writes data for the insect
     */
    void skrivData(){
        cout << "\nInsekt:\n";
        DyrILuft::skrivData();
        cout << "\tAntall bein: " << bein << "\n";
        cout << (bein >= 1000 ? "\tTusenbein: Ja" : "\tTusenbein: Nei") << "\n";
    };
};

/**
 *  Main Program
 */
int main(){

    skrivMeny();
    char kommando = lesChar("\nKommando");

    while (kommando != 'Q'){
        switch (kommando){

            // Fish
            case 'F':{
                string navn;
                cout << "\tNavn: ";
                getline(cin, navn);
                if (navn.size() == 0){
                    Fisk* fisk = new Fisk;
                    fisk->skrivData();
                    delete fisk;
                    fisk = nullptr;
                }
                else{
                    Fisk* fisk = new Fisk(navn);
                    fisk->skrivData();
                    delete fisk;
                    fisk = nullptr;
                }
                break;
            }

            // Insect
            case 'I':{
                Insekt* insekt = new Insekt;
                insekt->skrivData();
                delete insekt;
                insekt = nullptr;
                break;
            }

            // Shellfish
            case 'S':{
                Skalldyr* skalldyr = new Skalldyr;
                skalldyr->skrivData();
                delete skalldyr;
                skalldyr = nullptr;
                break;
            }

            // Bird
            case 'K':{
                Fugl* fugl = new Fugl;
                fugl->skrivData();
                break;
            }

            default:{
                skrivMeny();
                break;
            }}

        kommando = lesChar("\nKommando");
    }
}

/**
 *  @brief Prints out the menu
 */
void skrivMeny(){
    cout << "\nMeny"
         << "\n-----------------"
         << "\nF - Fisk"
         << "\nI - Insekt"
         << "\nS - Skalldyr"
         << "\nK - Fugl"
         << "\n-----------------"
         << "\nQ - Avslutt"
         << "\n";
}