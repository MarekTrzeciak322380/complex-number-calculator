#include <iostream>

#include "utils/args_handler.h"
#include "utils/file_helper.h"
#include "utils/solver.h"
#include "classes/args.h"
#include "classes/complex.h"

int main(int argc, char const *argv[]){

    std::queue<std::string> a = getRPN("3+4*2/(1-5)^2");
    // for (std::string s = a.front(); !a.empty() ; a.pop()){
    //     std::cout << a.front() << " ";
    // }
    solveRPN(a);

    std::cout << "\r\n";
    return 0;

    Args args = argsHandler(argc, argv);
    if (args.containsFlag(Options::exit)){
        std::clog << "EARLY EXIT\r\n";      //debug
        return 0;
    }
    
    inputFileHandler(args);
    if (args.shouldExit()){
        return 0;
    }
    std::cout << "Rownanie na wejsciu: " << args.equation <<"\r\n";     // debug(?)

    std::vector<Complex> answers = solver(args);

    if(args.out_path.length() != 0){
        // savingHandler(args, answers);
    }

    std::cout << "\r\n";    // linux compensation
    return 0;
}