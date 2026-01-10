#include "complex.h"


Complex::Complex(double real, double imaginary) : real{real}, imaginary{imaginary}{}
Complex::Complex(double real) : real{real}{}
// Complex::Complex(std::string str){}; to implement

const double Complex::abs(){
    return (std::sqrt(real*real + imaginary*imaginary));
}
const double Complex::arg(){
    return std::acos(real/abs());
}

void Complex::printExponential(){
    std::cout << abs() << "e^(" << arg() << "i)\r\n"; 
}
void Complex::printPolar(){
    const double argument = arg();
    std::cout << abs() << "(cos(" << argument << "), sin(" << argument << ")i)\r\n";
    // const double absolute = abs();
    // std::cout << absolute << "(" << real / absolute << ", " << imaginary / absolute <<")\r\n";
}
void Complex::printRectangular(){
    std::cout << real << " + (" << imaginary << ")i\r\n"; 
}


