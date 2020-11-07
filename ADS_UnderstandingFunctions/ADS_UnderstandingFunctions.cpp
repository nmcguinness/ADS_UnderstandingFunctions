/*****************************************************************//**
 * \file   ADS_UnderstandingFunctions.cpp
 * \brief  Demonstrates the FOUR methods that we have for representing
 * functions in C++
 *
 * \author NMCG
 * \date   November 2020
 *********************************************************************/
#include <iostream>
#include <list>
#include <functional>
using namespace std;
struct Bike {
    string name;
    float price;
    bool bStreetBike = true;
    //remember we can also add methods, just like a class
    //  friend ostream& operator<<(ostream& os, const Bike& bike);
};

void print(list<Bike> list, string seller) {
    int index = 1;

    cout << seller << endl;
    for (Bike b : list)
        cout << index++ << "] " << b.name
        << "\t" << b.price
        << "\t" << (b.bStreetBike ? "Street" : "Mountain") << endl;
}

void print(list<Bike> list, string seller, string email) {
    int index = 1;

    cout << seller << endl;
    cout << email << endl;
    for (Bike b : list)
        cout << index++ << "] " << b.name
        << "\t" << b.price
        << "\t" << (b.bStreetBike ? "Street" : "Mountain") << endl;
}

/*
void print(list<Bike> list, Function printFunction) {
    int index = 1;
    for (Bike b : list) {
        printFunction(index, b);
        index++;
    }
}
*/

void printBike_EU(int index, Bike b) {
    cout << index << "] " << b.name << "\t" << b.price
        << "\t" << (b.bStreetBike ? "Street" : "Mountain") << endl;
}

void printBike_US(int index, Bike b) {
    cout << index << "." << endl << "Name:" << b.name << endl << "Price:" << b.price
        << endl << "Style:" << (b.bStreetBike ? "Street" : "Mountain") << endl;
}

//version 1 - uses a pointer to a function
void print(list<Bike> list, void (*fPtr)(int, Bike)) {
    int index = 1;
    for (Bike b : list) {
        fPtr(index, b);
        index++;
    }
}

//version 2 - STL function
void print(list<Bike> list, std::function<void(int, Bike)> myFunc) {
    int index = 1;

    for (Bike b : list) {
        myFunc(index, b);
        index++;
    }
}

struct StandardHeaderFunctor {
    string name;
    string email;

    void operator()() {
        cout << "*************" << name << "*************" << endl;
        cout << "*************" << email << "*************" << endl;
    }
};

void print(list<Bike> list, std::function<void(int, Bike)> myFunc,
    std::function<void(string, string)> headerFunc) {
    int index = 1;
    headerFunc("halfords", "halfords@...");
    for (Bike b : list) {
        myFunc(index, b);
        index++;
    }
}

float getY(float slope, float yIntercept, float x) {
    return slope * x + yIntercept;
}

int main()
{
    /*
        Four methods to model a function:
        1. Function pointer - old-school, inflexible, efficient, syntactically complex
        2. STL functions
        3. Functors
        4. Lambda functions
    */

    //create a list of struct instances    
    list<Bike> bikeList = {
        {"raid", 1099, false },
         {"carrera vengeance", 1319, false },
          {"indur", 360, true }
    };

    print(bikeList, "*********************Halfords***********************");


    //we can instanciate a pointer to the print function using the code below and then call print()
    //void (*fPtr)(int, Bike) = &printBike_EU;
    //print(bikeList, fPtr);

    //or we can just get the address of the printBike_EU function and pass directly into print()
    print(bikeList, &printBike_EU);

    cout << endl;

    std::function<void(int, Bike)> myPrintFunc = printBike_US;
    //auto myPrintFunc = printBike_US;
    print(bikeList, myPrintFunc);

    //...later on that day...
   /* Bike b;
    b.name = "raleigh";
    b.price = 999.99;
    fPtr(5, b);*/


    std::function<float(float, float, float)> lineFunc = getY;
    //call the function using lineFunc
    cout << getY(0.5, 2, 6) << endl;
}


