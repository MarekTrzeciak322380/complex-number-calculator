#include "file_helper.h"

bool loadFromFile(std::string path, std::string &equation){
    std::fstream file(path, std::ios::in);
    if(!file.good()){
        return false;
    }
        
    equation = "";
    std::string str{};
    while(file >> str){
        equation += str;
    }

    file.close();
    return true;
}

void inputFileHandler(Args &args){
    if (args.in_path.length() == 0){
        return;
    }

    std::cout << "Plik wejsciowy: " << args.in_path <<"\r\n";   

    if(!loadFromFile(args.in_path, args.equation)){
        std::cerr << "Blad otwierania pliku!\r\n";
        args.options = Options::exit;
    }
    if (args.equation.length() == 0){   // Zamknięcie programu jeśli z pliku nic się nie wczytało
        std::cerr << "Blad wczytywania danych z pliku\r\n";
        args.options = Options::exit;
    }
}

void saveToFile(const Args &args, std::string str){
    std::fstream file(args.out_path, std::ios::out);
    if(!file.good()){
        std::cerr << "Blad tworzenia pliku!\r\n";
        return;
    }

    file << str;

    std::cout << "Wynik zapisano do pliku: " << args.out_path <<"\r\n";
    file.close();
}

void savingHandler(const Args &args, const std::vector<Complex> &answers){
    if(args.out_path.length() == 0){
        return;   
    }
    if(answers.size() == 0){
        std::cerr << "Problem z rozwiązaniem\r\n";
        return;   
    }

    std::string to_save = args.equation;
    if(args.containsFlag(Options::quadratic_function)){
        to_save += " = 0 dla:\r\n";
        for(Complex c : answers){
            to_save += "x = " + c.getRectangular() + "\r\n";       
        }
    }else{
        to_save += " =\r\n";
        if(args.containsFlag(Options::rectangular)){
            to_save += answers[0].getRectangular() + "\r\n"; 
        }
        if(args.containsFlag(Options::polar)){
            to_save += answers[0].getPolar() + "\r\n";
        }
        if(args.containsFlag(Options::exponential)){
            to_save += answers[0].getExponential() + "\r\n"; 
        }
    }
    saveToFile(args, to_save);
}
