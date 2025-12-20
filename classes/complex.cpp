#include "complex.h"


Complex::Complex(Real real, Real imaginary) : real{real}, imaginary{imaginary}{}
// Complex::Complex(std::string str){}; to implement

void Complex::printExponential(){
    
}
void Complex::printPolar(){

}
void Complex::printRectangular(){
    std::cout << real << " + (" << imaginary << ")i\r\n"; 
}

