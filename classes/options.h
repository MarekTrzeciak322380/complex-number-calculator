#pragma once

enum class Options{
    exit = 1 << 0,
    polar = 1 << 1,
    rectangular = 1 << 2,
    exponential = 1 << 3,
    quadratic_function = 1 << 4,
};

inline Options operator|(Options a, Options b){
    return static_cast<Options>(static_cast<int>(a) | static_cast<int>(b));
}
inline Options operator&(const Options a, const Options b){     //get this to be const somehow
    return static_cast<Options>(static_cast<int>(a) & static_cast<int>(b));
}