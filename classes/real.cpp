#include "real.h"

Real::Real(int number) : value{number}{};
Real::Real(std::string str){};

std::ostream &operator<<(std::ostream &out, const Real &r){
    return out << r.value;
}
