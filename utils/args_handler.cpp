#include "args_handler.h"

void displayHelp(){
   std::cout << "Informacje o programie\r\n";
//    std::cout << "\r\n";
   std::cout << "Flagi:\r\n";
   std::cout << "-i <scierzka> - wczytuje dane wejściowe z pliku\r\n";
   std::cout << "-o <scierzka> - zapisuje wynik do pliku\r\n";
}

Options argsHandler(const int &argc, const char *argv[]){
    // debug
    for (char i = 0; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << "\r\n";
    
    if (argc < 2){
        displayHelp();
        return Options::exit;
    }
    
    return Options{0};
}
