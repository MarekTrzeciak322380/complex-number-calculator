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
        std::clog << argv[i] << " ";
    }
    std::clog << "\r\n";
    
    if (argc < 2){
        displayHelp();
        return Args{Options::exit};
    }

    // Zbieranie argumentów
    Args res{};
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0){
            displayHelp();
            return Args{Options::exit};
        }else if(strcmp(argv[i], "-i") == 0){
            if (i+1 >= argc){
                std::cerr << "Brak scierzki na plik wejsciowy!\r\n";
                return Args{Options::exit};
            }
            res.in_path = argv[++i];    // pomijamy argument w następnym przejściu pętli
        }else if(strcmp(argv[i], "-o") == 0){
            if (i+1 >= argc){
                std::cerr << "Brak scierzki na plik wyjsciowy!\r\n";
                return Args{Options::exit};
            }
            res.out_path = argv[++i];   // pomijamy argument w następnym przejściu pętli
        }else{
            res.equation += argv[i];
        }
    }
    // std::clog << res.in_path.length() << "\t" << res.equation.length();  // debug

    if(res.in_path.length() == 0 && res.equation.length() == 0){    // sprawdzamy czy otrzymaliśmy dane wejściowe
        std::cerr << "Brak danych wejsciowych!\r\n";
    }

    return res;
}