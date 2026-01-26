#include "display.h"

void resultDisplay(const Args &args, const std::vector<Complex> &answers){
    // std::clog << answers[0].real << "\t" << answers[0].imaginary << "\r\n";
    if(args.containsFlag(Options::quadratic_function)){
        std::cout << args.equation << " = 0 dla:\r\n";
        for(Complex c : answers){
            std::cout << c.getRectangular() << "\r\n";
        }
    }else{
        std::cout << "WYNIKI:\r\n";
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