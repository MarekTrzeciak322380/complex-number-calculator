#include "complex.h"


Complex::Complex(double real, double imaginary) : real{real}, imaginary{imaginary}{}
Complex::Complex(double real) : real{real}{}
// Complex::Complex(std::string str){}; to implement

const double Complex::abs(){
    return (std::sqrt(real*real + imaginary*imaginary));
}

void Complex::printExponential(){
    
}
void Complex::printPolar(){

}
void Complex::printRectangular(){
    std::cout << real << " + (" << imaginary << ")i\r\n"; 
}


