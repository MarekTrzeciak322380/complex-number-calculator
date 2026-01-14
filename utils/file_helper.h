#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "../classes/args.h"
#include "../classes/complex.h"

bool loadFromFile(std::string path, std::string &equation);
void inputFileHandler(Args &args);
void saveToFile(const Args &args, std::string str);
void savingHandler(const Args &args, std::vector<Complex> &answers);