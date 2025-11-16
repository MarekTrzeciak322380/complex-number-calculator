#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "../classes/args.h"

std::string loadFromFile(std::string path);
void inputFileHandler(Args &args);
