#pragma once

#include <string>

#include "options.h"

/// @brief Przechowuje argumenty podane przez użytkownika na wejściu
class Args{
    
public:
    Options options;
    std::string in_path = "";   ///< Ścierzka do pliku wejściowego
    std::string out_path = "";  ///< Ścieżka do pliku wyściowego
    std::string equation = "";  ///< Równanie podane przez użytkownika
    
    /// @brief  Sprawdza czy trzeba zakonczyć program 
    inline bool shouldExit(){
        return (bool)(options & Options::exit);
    }
    /// @brief Sprawdza czy dana flaga jest prawdziwa 
    inline bool containsFlag(const Options flag) const {
        return (bool)(options & flag);
    }
};