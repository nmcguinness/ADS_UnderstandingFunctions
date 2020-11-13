/*****************************************************************//**
 * \file   ADS_UnderstandingFunctions.cpp
 * \brief  Demonstrates the FOUR methods that we have for representing functions in C++
 *
 * \author NMCG
 * \date   November 2020
 *********************************************************************/
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
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

float add(int x, int y) {
    return x / y;
}

void displayMessage(string msg) {
    //screen
}
void sendMessage(string msg) {
    //network
}
void storeMessage(string msg) {
    //file
}

//void processMessage(list<string> list, std::unary_function<void(string)> process) {
//    for(string s : list)
//        process(s);
//}


/// @brief Trims leading and trailing whitespace
/// @param str String input containing leading/trailing whitespace
/// @return Trimmed string
/// @see https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
string trim(string str) {

    size_t p = str.find_first_not_of(" \t");
    str.erase(0, p);

    p = str.find_last_not_of(" \t");
    if (string::npos != p)
        str.erase(p + 1);

    return str;
}

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string processString(string target, list<function<string(string)>> transformFuncList) {
    
    string transformed = target;
    for (function<string(string)> func : transformFuncList) {
        transformed = func(transformed);
    }
    return transformed;
}

//a functor is normally (params + function) in this case we just have a function BUT we can still use a functor
class TrimStringFunctor {
private:
   // int x;
  //  string s;
public:
    string operator()(string str) {
        size_t p = str.find_first_not_of(" \t");
        str.erase(0, p);

        p = str.find_last_not_of(" \t");
        if (string::npos != p)
            str.erase(p + 1);
        return str;
    }
};

//a functor is normally (params + function) in this case we just have a function BUT we can still use a functor
class ToLowerCaseFunctor {
private:
 //   int exclLo, exclHi; //dont lowercase from 0 - 4

public:
 //   ToLowerCaseFunctor(int exclLo, int exclHi) : exclLo(exclLo), exclHi(exclHi) {};

    string operator()(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
};

int main()
{
   /*
        Four methods to model a function:
        1. Function pointer - old-school, inflexible, efficient, syntactically complex
        2. STL functions
        3. Functors (Object [params, function]
        4. Lambda functions
    */

    ////create a list of struct instances    
    //list<Bike> bikeList = {
    //    {"raid", 1099, false },
    //     {"carrera vengeance", 1319, false },
    //      {"indur", 360, true }
    //};

    //print(bikeList, "*********************Halfords***********************");


    ///***************************** Function Pointers *****************************/
    //cout << "Function Pointers..." << endl;

    ////we can instanciate a pointer to the print function using the code below and then call print()
    //void (*fPtr)(int, Bike) = &printBike_EU;
    //print(bikeList, fPtr);

    ////or we can just get the address of the printBike_EU function and pass directly into print()
    //print(bikeList, &printBike_EU);

    //cout << endl;

    ///***************************** STL functions *****************************/
    //cout << "STL functions..." << endl;

    //std::function<void(int, Bike)> myPrintFunc = printBike_US;
    ////auto myPrintFunc = printBike_US;
    //print(bikeList, myPrintFunc);

    //std::function<float(float, float, float)> lineFunc = getY;
    ////call the function using lineFunc
    //cout << getY(0.5, 2, 6) << endl;

    ////std::binary_function<float(int, int)> mathFunc = add;
    ////mathFunc(45, 50);

    ////std::unary_function<void(string)> displayFunc = displayMessage;
    ////displayFunc("Hi screen this is the code!");

    //cout << endl;


    ///***************************** List of STL functions *****************************/
    cout << "List of STL functions..." << endl;

    //"   Jane@DKIT.ie   ", "jane@dkit.ie", "jane@dkit.ie", true
    //mona lisa[635x481], mona lisa[1024x768], mona lisa[1024x768, b&w], beautify(mona lisa)

    //instanciate each filter
    string str1 = "   Jane@DKIT.ie                   ";

    //add each filter to a list
    list<function<string(string)>> funcList1 = {trim, toLowerCase};

    //pass the target string and list into a process function
    string strFinal1 = processString(str1, funcList1);

    //show the output
    cout << strFinal1 << endl;

    /***************************** Functors *****************************/
    cout << "Functors..." << endl;

    //instanciate each filter
    string str2 = "           Steve@DKIT.ie ";

    //add each filter to a list
    TrimStringFunctor trFunc;
    ToLowerCaseFunctor tlcFunc;
   // string s = trFunc("      today is thursday     ");

    list<function<string(string)>> funcList2 = { trFunc, tlcFunc };

    //pass the target string and list into a process function
    string strFinal2 = processString(str2, funcList2);

    //show the output
    cout << strFinal2 << endl;


    /***************************** Lambda Functions *****************************/
    cout << "Lambda Functions..." << endl;


    function<string(string)> func1 = [](string str) 
    {
        size_t p = str.find_first_not_of(" \t");
        str.erase(0, p);

        p = str.find_last_not_of(" \t");
        if (string::npos != p)
            str.erase(p + 1);

        return str; 
    };

    //at compile time auto will be replaced with "function<string(string)>"
    auto func2 = [](string s) { return "Processed: " + s; };
    list<function<string(string)>> funcList3 = { func1, func2};

    //continue to call code as above...
}


