#include <string>
#include <iostream>

#include "real.h"


class Complex{

public:

    Complex(Real real, Real imaginary);
    Complex(std::string str);

    void printRectangular();
    void printPolar();
    void printExponential();

    Complex operator+(const Complex &c){
        return Complex(real + c.real, imaginary + c.imaginary);
    }
    Complex operator-(const Complex &c){
        return Complex(real - c.real, imaginary - c.imaginary);
    }
    Complex operator*(const Complex &c){
        return Complex((real * c.real - imaginary * c.imaginary), (real * c.imaginary + imaginary * c.real));
    }

// private:
    Real real;
    Real imaginary;

};
    