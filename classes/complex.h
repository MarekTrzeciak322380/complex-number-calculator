#pragma once

#include <string>
#include <iostream>
#include <math.h>

/// @brief Liczba zespolona
class Complex{

public:

    Complex(double real, double imaginary);
    Complex(double real);
    Complex();

    double abs() const;
    double arg() const;

    std::string getRectangular() const;
    std::string getPolar() const;
    std::string getExponential() const;

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
    