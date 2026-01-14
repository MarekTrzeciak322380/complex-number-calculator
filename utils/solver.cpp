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

    // if(equation.front() == "-"){
    //     stack.emplace(0);
    // }

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
            stack.push(std::stoi(equation.front()));
            // std::clog << "added: " << stack.top() << "\r\n";
        }
        equation.pop();
    }

    std::clog << stack.top();

    return res;
}
