#include <iostream>

#include "utils/args_handler.cpp"
#include "classes/args.h"

int main(int argc, char const *argv[])
{

    Args args = argsHandler(argc, argv);
    if ((bool)(args.options & Options::exit))
    {
        std::cout << "EARLY EXIT\r\n";      //debug
        return 0;
    }

    std::cout << "\r\n";    // linux compensation
    return 0;
}