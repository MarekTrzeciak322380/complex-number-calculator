#include "file_helper.h"

std::string loadFromFile(std::string path){
    std::fstream file(path, std::ios::in);
    if(!file.good()){
        // std::cerr << "Blad otwierania pliku!\r\n";   // jakoś sensownie podzielić na wyświetlanie albo błędu pliku lub braku danych
        return "";
    }
    
    std::string res{};    
    std::string str{};    
    while(file >> str){
        res += str;
    }

    file.close();
    return res;
}

void inputFileHandler(Args &args){
    if (args.in_path.length() == 0){
        return;
    }

    std::cout << "Plik wejściowy: " << args.in_path <<"\r\n";  // debug(?)     

    args.equation = loadFromFile(args.in_path);
    if (args.equation.length() == 0){   // Zamknięcie programu jeśli z pliku nic się nie wczytało
        args.options = Options::exit;
    }
}

void saveToFile(std::string path, std::string equation){
    if(path.length() == 0){
        return;
    }

    std::fstream file(path, std::ios::out);
    if(!file.good()){
        std::cerr << "Blad tworzenia pliku!\r\n";   // jakoś sensownie podzielić na wyświetlanie albo błędu pliku lub braku danych
        return;
    }

    file << equation;
    std::cout << "Wynik zapisano do pliku: " << path <<"\r\n";
    file.close();
}