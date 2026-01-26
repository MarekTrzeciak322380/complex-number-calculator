#include "solver.h"


std::vector<Complex> solver(const Args &args){
    std::vector<Complex> answers{};
    if(args.containsFlag(Options::quadratic_function)){
        const std::array<double, 3> nums = getQuadraticFunction(args.equation); 
        answers = solveQuadraticFunction(nums[0], nums[1], nums[2]);
    }else{
        answers = solveRPN(getRPN(args.equation));
    }
    return answers;
}

std::array<double, 3> getQuadraticFunction(std::string equation){
    std::array<double, 3> res = {};

    int x2 = equation.find("x^2");
    int x1 = equation.find_last_of("x");

    // std::clog << x2 << " " << x1 << "\r\n";    
    // std::clog << equation.substr(0, x2) << "\r\n";
    // std::clog << equation.substr(x2+3, x1-x2-3) << "\r\n";
    // std::clog << equation.substr(x1+1) << "\r\n";


    res[0] = std::stod(equation.substr(0, x2));
    res[1] = std::stod(equation.substr(x2+3, x1-x2-3));
    res[2] = std::stod(equation.substr(x1+1));

    for (auto a : res){
        std::clog << a << " ";
    }
    std::clog << "\r\n";
    return res;
}

std::vector<Complex> solveQuadraticFunction(const double a, const double b, const double c){
    std::vector<Complex> res{}; 
    const double delta = b*b - 4 * a * c;
    if (delta == 0){
        const double x0 = (std::sqrt(delta) - b) / 2 / a;
        res.push_back(x0);
    }else if(delta > 0){
        const double x1 = (-std::sqrt(delta) - b) / 2 / a;
        const double x2 = (std::sqrt(delta) - b) / 2 / a;
        res.push_back(x1);
        res.push_back(x2);
    }else{
        Complex delta_sqrt(0, std::sqrt(delta));
        Complex x1 = (-delta_sqrt - b) / 2 / a;
        Complex x2 = (delta_sqrt - b) / 2 / a;
        res.push_back(x1);
        res.push_back(x2);
    }
    // std::clog << a << " " << b << " " << c << " " << delta << "\r\n";
    // std::clog << "res:\t\t";
    // for(auto a : res){
    //     std::clog << a.getRectangular() << " ";
    // }
    // std::clog << "\r\n";
    
    return res;
}

std::queue<std::string> getRPN(std::string equation){
    std::stack<std::string> stack{};
    std::queue<std::string> res{};

    const std::array<char, 6> signs = {'-', '+', '*', '/', '^', '='};

    while (equation.length() > 0){
        std::string sub = equation.substr(0,1);

        // std::clog << equation << "\t"<< sub << "\r\n";
        // if(!stack.empty()){
        //     std::clog << stack.top() << "\t" << stack.size() << "\r\n\n";
        // }

        if(std::find(signs.begin(), signs.end(), sub[0]) != signs.end()){   //znak
            if(!stack.empty()){
                std::string top = stack.top(); 
                if(sub[0] == '-'){
                    while(top == "+" || top == "*" || top == "/" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '+'){
                    while(top == "*" || top == "/" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '/'){
                    while(top == "*" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '*'){
                    while(top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else{

                }
            } 
            stack.emplace(sub);
        }else if(sub[0] == '('){
            stack.emplace(sub);
        }else if(sub[0] == ')'){
            while(stack.top() != "("){
                // std::clog << "top: " << stack.top() << "\r\n";
                res.emplace(stack.top());
                stack.pop();
                if (stack.empty()){
                    std::cerr << "Zle!\r\n";
                    throw "bad";
                }               
            }
            stack.pop();
        }else if(sub[0] >= '0' && sub[0] <= '9'){  //liczba
            int i = 1;
            while (equation[i] >= '0' && equation[i] <= '9'){
                sub += equation.substr(i, 1);
                i++;
            }
            res.emplace(sub);
        }else{
            std::cerr << "Blad przy rozwiazywaniu!\r\n";
        }
        

        equation = equation.substr(sub.length());
    }
    
    while(!stack.empty()){
        //check for "(", ")"
        // std::cout << stack.top() << " "; 
        res.emplace(stack.top());
        stack.pop();
    }
    
    return res;
}

std::vector<Complex> solveRPN(std::queue<std::string> equation){
    std::vector<Complex> res{};
    std::stack<double> stack{{}};
    const std::array<char, 6> signs = {'-', '+', '*', '/', '^', '='};

    // sprawdzanie czy minus na początku ale nie na początku :c
    
    while(!equation.empty()){
        if(std::find(signs.begin(), signs.end(), equation.front()[0]) != signs.end()){   //znak
            double a = stack.top();
            stack.pop();
            double b = stack.top();
            stack.pop();
            // std::clog << a << " " << b << "\t" << stack.size() << "\r\n"; 
            double result;
            switch (equation.front()[0]){
                case '+':
                    result = b+a;    
                    break;
                case '-':
                    result = b-a;    
                    break;
                case '/':
                    result = b/a;    
                    break;
                case '*':
                    result = b*a;    
                    break;
                case '^':
                    result = pow(b,a);    
                    break;
                default:
                    std::cerr << "Blad rozwiazywania!\r\n";
                    throw;
            }
            stack.emplace(result);    
            
        }else{
            stack.push(std::stod(equation.front()));
            // std::clog << "added: " << stack.top() << "\r\n";
        }
        equation.pop();
    }

    // std::clog << stack.top();
    res.push_back(stack.top());
    return res;
}
