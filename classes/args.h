#pragma once

#include <string>

#include "options.h"

class Args{
    
public:
    Options options;
    std::string in_path = "";
    std::string out_path = "";
    std::string equation = "";

    inline bool shouldExit(){
        return (bool)(options & Options::exit);
    }
};