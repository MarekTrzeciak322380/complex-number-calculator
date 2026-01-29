#include "solver.h"

/// @brief Sprawdza czy liczyć miejsca zerowe czy obliczać wartość równania
/// @param args
/// @return 
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

/// @brief Zwraca liczby przy poszczególnych potęgach 'x' w równaniu kwadratowym
/// @param equation 
/// @return 
std::array<double, 3> getQuadraticFunction(std::string equation){
    std::array<double, 3> res = {};

    const int x2 = equation.find("x^2");
    if(x2 == 0|| equation[x2-1] == '+'){
        res[0] = 1;
    }else if(x2 > 0){
        if(x2 == 1 && equation[x2-1] == '-'){
            res[0] = -1;
        }else{
            res[0] = std::stod(equation.substr(0, x2));
        }
    }
    
    int x1 = equation.find_last_of("x");
    if(x1 == 0 || equation[x1-1] == '+'){
        res[1] = 1;
    }else if(x1 > 0 && x1 != x2){
        if(equation[x1-1] == '-'){
            res[1] = -1;
        }else{
            if (x2 >= 0){
                res[1] = std::stod(equation.substr(x2+3, x1-x2-3));
            }else{
                res[1] = std::stod(equation.substr(0, x1-x2));
            }
            
        }
    }

    if(x1 != equation.length() - 1 && x2 != equation.length() - 1){
        if (x2 == x1){
            res[2] = std::stod(equation.substr(x2+3));
        }else{
            res[2] = std::stod(equation.substr(x1+1));
        }
    }
    
    return res;
}

/// @brief rozwiązuje równanie kwadratowe
/// @param a x^2
/// @param b x
/// @param c wyraz wolny
/// @return 
std::vector<Complex> solveQuadraticFunction(const double a, const double b, const double c){

    if (a == 0){    
        if (b == 0){
            if (c == 0){
                return {{INFINITY}};
            }
            return {{NAN}};
        }
        return {{-c/b}};
    }    

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
        Complex delta_sqrt(0, std::sqrt(-delta));
        Complex x1 = (-delta_sqrt - b) / 2 / a;
        Complex x2 = (delta_sqrt - b) / 2 / a;
        res.push_back(x1);
        res.push_back(x2);
    }
    
    return res;
}

/// @brief Zamienia równanie na postać ONP
/// @param equation 
/// @return 
std::queue<std::string> getRPN(std::string equation){
    std::stack<std::string> stack{};
    std::queue<std::string> res{};

    const std::array<char, 6> signs = {'-', '+', '*', '/', '^', '='};

    while (equation.length() > 0){
        std::string sub = equation.substr(0,1);

        if(std::find(signs.begin(), signs.end(), sub[0]) != signs.end()){   //znak
            if(!stack.empty()){
                std::string top = stack.top(); 
                if(sub[0] == '-'){
                    while(top == "-" ||top == "+" || top == "*" || top == "/" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '+'){
                    while(top == "-" ||top == "+" || top == "*" || top == "/" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '/'){
                    while(top == "/" || top == "*" || top == "^"){
                        res.emplace(top);
                        stack.pop();
                        if(stack.empty()){
                            break;
                        }
                        top = stack.top();
                    }
                }else if(sub[0] == '*'){
                    while(top == "/" || top == "*" || top == "^"){
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
        }else if(sub[0] == 'i'){
            res.emplace("i");
        }else{
            std::cerr << "Blad przy rozwiazywaniu!\r\n";
        }
        

        equation = equation.substr(sub.length());
    }
    
    while(!stack.empty()){
        //check for "(", ")"
        res.emplace(stack.top());
        stack.pop();
    }
    
    return res;
}

/// @brief Rozwiązuje równanie w postaci ONP
/// @param equation 
/// @return 
std::vector<Complex> solveRPN(std::queue<std::string> equation){
    std::vector<Complex> res{};
    std::stack<Complex> stack{{}};
    const std::array<char, 6> signs = {'-', '+', '*', '/', '^', '='};

    // sprawdzanie czy minus na początku ale nie na początku :c
    while(!equation.empty()){
        if(std::find(signs.begin(), signs.end(), equation.front()[0]) != signs.end()){   //znak
            Complex a = stack.top();
            stack.pop();
            Complex b = stack.top();
            stack.pop();
            Complex result(0,0);
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
                    result = pow(b.real, a.real);
                    break;
                default:
                    std::cerr << "Blad rozwiazywania!\r\n";
                    throw;
            }
            stack.emplace(result);    
            
        }else{
            if (equation.front() == "i"){
                stack.push(Complex(0,1));
            }else{
                stack.push(std::stod(equation.front()));
            }
        }

        equation.pop();
    }

    res.push_back(stack.top());
    return res;
}
