#include <iostream>

#include "utils/args_handler.cpp"
#include "classes/options.h"

int main(int argc, char const *argv[])
{

    Options options = argsHandler(argc, argv);
    if ((bool)(options & Options::exit))   // cahnge this 
    {
        std::cout << "EARLY EXIT\r\n";      //debug
        return 0;
    }
    

    std::cout << "\r\n";    // linux compensation
    return 0;
}