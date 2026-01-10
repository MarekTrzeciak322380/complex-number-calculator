#include <string>
#include <iostream>
#include <math.h>

#include "real.h"


class Complex{

public:

    Complex(double real, double imaginary);
    Complex(double real);
    Complex(std::string str);

    const double abs();

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
    Complex operator/(const Complex &c){
        if(c.real == 0 && c.imaginary == 0){
            throw "Nie dziel przez zero";
        }
        return Complex((real * c.real + imaginary * c.imaginary)/(c.real*c.real + c.imaginary*c.imaginary), (c.real * imaginary - real * c.imaginary)/(c.real*c.real + c.imaginary*c.imaginary));
    }
    Complex operator-(){
        return Complex(-real, -imaginary);
    }

// private:
    double real;
    double imaginary;

};
    