#pragma once

#include <string>

#include "options.h"

/// Przechowuje argumenty podane przez użytkownika na wejściu

class Args{
    
public:
    Options options;
    std::string in_path = "";   //< ścierzka pliku wejściowego
    std::string out_path = "";  //< ścieżka pliku wyściowego
    std::string equation = "";  //< równanie podane przez użytkownika
    
    ///  Sprawdza czy trzeba zakonczyć program 
    inline bool shouldExit(){
        return (bool)(options & Options::exit);
    }
    /// @brief Sprawdza czy dana flaga jest prawdziwa
    /// @param flag 
    /// @return 
    inline bool containsFlag(const Options flag) const {
        return (bool)(options & flag);
    }
};