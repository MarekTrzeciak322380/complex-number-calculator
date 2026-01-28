#include "args_handler.h"

void displayHelp(){
   std::cout << "Informacje o programie\r\n";
   std::cout << "Sposob uzycia: kalkulator [flagi] <rownanie>\r\n";
   std::cout << "Flagi:\r\n";
   std::cout << "--i <scierzka> - wczytuje dane wejsciowe z pliku\r\n";
   std::cout << "--o <scierzka> - zapisuje wynik do pliku\r\n";
   std::cout << "--a - wyswietla wynik w postaci algebraicznej\r\n";
   std::cout << "--t - wyswietla wynik w postaci trygonometrycznej\r\n";
   std::cout << "--w - wyswietla wynik w postaci wykladniczej\r\n";
   std::cout << "--k - znajduje mniejsca zerowe ownania kwadratowego/liniowego pod postacia: [A]x^2+[B]x+[C])\r\n";
}

bool validateEquationChars(const std::string equation, const Options options){    
    if ((bool) (options & Options::quadratic_function)){
        const std::array<char, 20> chars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '(', ')', '+', '-', '*', '/', '^', '=', 'x'};
        for(char c : equation){
            if(std::find(chars.begin(), chars.end(), c) == chars.end()){
                std::cerr << "Nieobslugiwany znak: " << c << "!\r\n";
                return false;
            }
        }
    }else{
        const std::array<char, 20> chars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '(', ')', '+', '-', '*', '/', '^', '=', 'i'};
        for(char c : equation){
            if(std::find(chars.begin(), chars.end(), c) == chars.end()){
                std::cerr << "Nieobslugiwany znak: " << c << "!\r\n";
                return false;
            }
        }
    }
    return true;
}


Args argsHandler(const int &argc, const char *argv[]){
    // debug
    // for (char i = 0; i < argc; i++){
    //     std::clog << argv[i] << " ";
    // }
    // std::clog << "\r\n";
    
    if (argc < 2){
        displayHelp();
        return Args{Options::exit};
    }

    // Zbieranie argumentów
    Args res{};
    for (int i = 1; i < argc; i++){
        if(std::strlen(argv[i]) >= 3 && argv[i][0] == '-' && argv[i][1] == '-'){
            if (argv[i][2] == 'i'){
                if(std::strlen(argv[i]) > 3){
                    std::cerr << "Bledny argument: " << argv[i] << "!\r\n";
                    return Args{Options::exit};
                }else if (i+1 >= argc){
                    std::cerr << "Brak scierzki na plik wejsciowy!\r\n";
                    return Args{Options::exit};
                }
                res.in_path = argv[++i];    // pomijamy argument w następnym przejściu pętli
            }else if (argv[i][2] == 'o'){
                if(std::strlen(argv[i]) > 3){
                    std::cerr << "Bledny argument: " << argv[i] << "!\r\n";
                    return Args{Options::exit};
                }else if (i+1 >= argc){
                    std::cerr << "Brak scierzki na plik wyjsciowy!\r\n";
                    return Args{Options::exit};
                }
                res.out_path = argv[++i];    // pomijamy argument w następnym przejściu pętli
            }else{
                for(int j = 2; j < std::strlen(argv[i]); j++){
                    switch(argv[i][j]){
                        case 'a':
                            res.options = res.options | Options::rectangular;
                            break;
                        case 't':
                            res.options = res.options | Options::polar;
                            break;
                        case 'w':
                            res.options = res.options | Options::exponential;
                            break;
                        case 'k':
                            res.options = res.options | Options::quadratic_function;
                            break;
                        default:
                            std::cerr << "Bledny argument: " << argv[i] << " !\r\n";
                            return Args{Options::exit};
                    }
                }

            }
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