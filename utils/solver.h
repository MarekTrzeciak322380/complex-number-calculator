#pragma once

#include <string>
#include <queue>
#include <stack>
#include <array>
#include <algorithm>
#include <math.h> 
#include <iostream> //debug

#include "../classes/complex.h"
#include "../classes/args.h"

std::vector<Complex> solver(const Args &args);

std::array<double, 3> getQuadraticFunction(std::string equation);
std::vector<Complex> solveQuadraticFunction(double a, double b, double c);  // <a>x^2 + <b>x + <c> = 0

std::queue<std::string> getRPN(std::string equation);
std::vector<Complex> solveRPN(std::queue<std::string> equation);