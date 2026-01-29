/// @file display.cpp
/// @brief Obsługa wyświetlania wyników w konsoli
#include "display.h"

/// @brief Wyświetla wyniki w konsoli
/// @param args 
/// @param answers 
void resultDisplay(const Args &args, const std::vector<Complex> &answers){
    if(args.containsFlag(Options::quadratic_function)){
        std::cout << args.equation << " = 0 dla:\r\n";
        for(Complex c : answers){
            std::cout << "x = " << c.getRectangular() << "\r\n";
        }
    }else{
        std::cout << args.equation <<  " =\r\n";
        if(args.containsFlag(Options::rectangular) || (!args.containsFlag(Options::rectangular) && !args.containsFlag(Options::polar) && !args.containsFlag(Options::exponential))){
            std::cout << answers[0].getRectangular() + "\r\n"; 
        }
        if(args.containsFlag(Options::polar)){
            std::cout << answers[0].getPolar() + "\r\n";
        }
        if(args.containsFlag(Options::exponential)){
            std::cout << answers[0].getExponential() + "\r\n"; 
        }
    }
    return;
}