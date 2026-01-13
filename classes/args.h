#pragma once

#include <string>

#include "options.h"

class Args{
    
public:
    Options options;
    std::string in_path = "";
    std::string out_path = "";
    std::string equation = "";

    inline const bool shouldExit(){
        return (bool)(options & Options::exit);
    }
    const inline bool containsFlag(const Options flag){
        return (bool)(options & flag);
    }
};