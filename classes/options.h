#pragma once

/// @brief Przechowuje opcje uruchamiania jakie wybrał użytkownik
enum class Options{
    exit = 1 << 0,
    polar = 1 << 1,
    rectangular = 1 << 2,
    exponential = 1 << 3,
    quadratic_function = 1 << 4,
};
/// @brief Dodaje wybraną flage
inline Options operator|(Options a, Options b){
    return static_cast<Options>(static_cast<int>(a) | static_cast<int>(b));
}
/// @brief Sprawdza czy flaga została wybrana 
inline Options operator&(const Options a, const Options b){     // make it const
    return static_cast<Options>(static_cast<int>(a) & static_cast<int>(b));
}