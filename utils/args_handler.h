#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include <algorithm>

#include "../classes/args.h"

void displayHelp();
bool validateEquationChars(const std::string equation, const Options options);
Args argsHandler(const int &argc, const char *argv[]);