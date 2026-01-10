#include "solver.h"


void quadratic_function(const double a, const double b, const double c){


    std::cout << "rozw: "; 
    const double delta = b*b + 4 * a * c;
    if (delta == 0){
        double x0 = (std::sqrt(delta) - b) / 2 / a;
        std::cout << x0;
    }else if(delta > 0){
        double x1 = (-std::sqrt(delta) - b) / 2 / a;
        double x2 = (std::sqrt(delta) - b) / 2 / a;
        std::cout << x1 << " " << x2; 
        
    }else{
        Complex delta_squared(0, std::sqrt(delta));
        Complex x1 = (-delta_squared - b) / 2 / a;
        Complex x2 = (delta_squared - b) / 2 / a;   
    }
    
    std::cout << "\r\n";
    return;
}