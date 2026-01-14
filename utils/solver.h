#pragma once

#include <string>
#include <queue>
#include <stack>
#include <math.h> 
#include <iostream> //debug

#include "../classes/complex.h"
#include "../classes/args.h"

std::vector<Complex> solver(Args &args);

std::vector<Complex> quadratic_function(std::string equation);
std::string getRPN(std::string equation);
std::vector<Complex> solveRPN(std::string equation);