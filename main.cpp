#include <iostream>

#include "utils/args_handler.h"
#include "classes/args.h"

int main(int argc, char const *argv[])
{

    Args args = argsHandler(argc, argv);
    if (args.shouldExit())
    {
        std::cout << "EARLY EXIT\r\n";      //debug
        return 0;
    }

    std::cout << "Rownanie na wejsciu: " << args.equation <<"\r\n";  // debug(?)
    if (args.in_path.length() > 0){
        std::cout << "Plik wejściowy: " << args.in_path <<"\r\n";  // debug(?)     
        
    }
    if (args.out_path.length() > 0){
        std::cout << "Plik wyjściowy: " << args.out_path <<"\r\n";  // debug(?)
    }

    std::cout << "\r\n";    // linux compensation
    return 0;
}