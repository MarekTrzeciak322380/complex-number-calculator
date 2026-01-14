#include "solver.h"


std::vector<Complex> solver(Args &args){
    std::vector<Complex> answers{};
    if(args.containsFlag(Options::quadratic_function)){
        answers = quadratic_function(args.equation);
    }else{
        answers = solveRPN(getRPN(args.equation));
    }
    return answers;
}

std::vector<Complex> quadratic_function(std::string equation){

    const double a = 1; 
    const double b = 2;
    const double c = 3;
    std::vector<Complex> res{}; 
    const double delta = b*b + 4 * a * c;
    if (delta == 0){
        const double x0 = (std::sqrt(delta) - b) / 2 / a;
        res.push_back(x0);
    }else if(delta > 0){
        const double x1 = (-std::sqrt(delta) - b) / 2 / a;
        const double x2 = (std::sqrt(delta) - b) / 2 / a;
        res.push_back(x1);
        res.push_back(x2);       
    }else{
        Complex delta_squared(0, std::sqrt(delta));
        Complex x1 = (-delta_squared - b) / 2 / a;
        Complex x2 = (delta_squared - b) / 2 / a;
        res.push_back(x1);
        res.push_back(x2);
    }
    
    return res;
}

std::string getRPN(std::string equation){
    std::stack<std::string> stack{};
    std::string res{};

    while (equation.length() > 0){
        std::string sub = equation.substr(0,1);


        equation = equation.substr(sub.length());
    }
    


    return res;
}

std::vector<Complex> solveRPN(std::string equation){
    std::vector<Complex> res{};
    
    return res;
}
