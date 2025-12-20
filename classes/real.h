#include <string>
#include <iostream>

class Real{

public:

    Real(int number);
    Real(std::string str);

    Real operator+(const Real &r){
        return Real(value + r.value);
    }
    Real operator-(const Real &r){
        return Real(value - r.value);
    }
    Real operator*(const Real &r){
        return Real(value * r.value);
    }
    Real operator/(const Real &r){
        return Real(value / r.value);
    }

    friend std::ostream& operator<<(std::ostream &out, const Real &r);

// private:
    int value;

};

