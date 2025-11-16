#include "args_handler.h"

void displayHelp(){
   std::cout << "Informacje o programie\r\n";
   std::cout << "Flagi:\r\n";
   std::cout << "-i <scierzka> - wczytuje dane wejściowe z pliku\r\n";
   std::cout << "-o <scierzka> - zapisuje wynik do pliku\r\n";
}

Args argsHandler(const int &argc, const char *argv[]){
    // debug
    for (char i = 0; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << "\r\n";
    
    if (argc < 2){
        displayHelp();
        return Args{Options::exit};
    }

    Options res{};
    std::string path_in;

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] == "-h"){
            displayHelp();
            return Args{Options::exit};
        }else if(argv[i] == "-i"){
            ;
            path_in = argv[i+1];
        }else if(argv[i] == "-o"){
            path_in = argv[i+1];
        }
        
    }
    
    
    return Args{};
}