#include <iostream>

#include "utils/args_handler.h"
#include "utils/file_helper.h"
#include "classes/args.h"
#include "classes/complex.h"

int main(int argc, char const *argv[]){

    Args args = argsHandler(argc, argv);
    if (args.containsFlag(Options::exit))
    {
        std::clog << "EARLY EXIT\r\n";      //debug
        return 0;
    }
    
    inputFileHandler(args);
    if (args.shouldExit()){
        std::cerr << "Blad wczytywania danych z pliku\r\n";
        return 0;
    }
    std::cout << "Rownanie na wejsciu: " << args.equation <<"\r\n";  // debug(?)

    saveToFile(args, Complex(1.f,3.f));

    std::cout << "\r\n";    // linux compensation
    return 0;
}