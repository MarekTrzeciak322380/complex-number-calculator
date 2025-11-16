#pragma once

enum class Options{
    exit = 1 << 0,
    convert_trigonometric = 1 << 1,
    convert_algebraic = 1 << 2,
    // input_file = 1 << 3,
    // output_file = 1 << 4,
};

inline Options operator|(Options a, Options b)
{
    return static_cast<Options>(static_cast<int>(a) | static_cast<int>(b));
}
inline Options operator&(Options a, Options b)
{
    return static_cast<Options>(static_cast<int>(a) & static_cast<int>(b));
}