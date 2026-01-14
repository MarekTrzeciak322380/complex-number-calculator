#include "complex.h"


Complex::Complex(double real, double imaginary) : real{real}, imaginary{imaginary}{}
Complex::Complex(double real) : real{real}, imaginary{0}{}

const double Complex::abs(){
    return (std::sqrt(real*real + imaginary*imaginary));
}
const double Complex::arg(){
    return std::acos(real/abs());
}

std::string Complex::getExponential(){
    if(imaginary == 0){
        return std::to_string(real); // std::format?
    }
    return std::to_string(abs()) + "*e^(" + std::to_string(arg()) + "*i)"; 
} 
std::string Complex::getPolar(){
    if(imaginary == 0){
        return std::to_string(real);
    }
    const std::string argument = std::to_string(arg());
    return std::to_string(abs()) + "*(cos(" + argument + ") + sin(" + argument + ")*i)";
}
std::string Complex::getRectangular(){
    if(imaginary == 0){
        return std::to_string(real);
    }
    return std::to_string(real) + " + (" + std::to_string(imaginary) + ")*i"; 
}
