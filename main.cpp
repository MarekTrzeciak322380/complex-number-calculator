#include <iostream>

#include "utils/args_handler.h"
#include "utils/file_helper.h"
#include "utils/solver.h"
#include "utils/display.h"
#include "classes/args.h"
#include "classes/complex.h"

int main(int argc, char const *argv[]){

    Args args = argsHandler(argc, argv);
    if (args.containsFlag(Options::exit)){
        return 0;
    }
    
    inputFileHandler(args);
    if (args.shouldExit()){
        return 0;
    }

    std::vector<Complex> answers = solver(args);

    savingHandler(args, answers);
    resultDisplay(args, answers);  


    std::cout << "\r\n";    // linux compensation
    return 0;
}