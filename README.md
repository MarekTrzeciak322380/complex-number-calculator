# Kalkulator liczb zespolonych

## Funkcjonalności
- wykonuje podstawowe operacje arytmetyczne (dodawanie, odejmowanie, mnożenie, dzielenie)
- zamiana między postaciami: algebraiczną, trygonometryczną, wykładniczą
- obliczanie miejsc zerowych funkcji kwadratowej, wraz z zespolonymi

## Obsługa
`kalkulator <flagi> [równanie]`

| Flaga | Opis |
| ----- | ---- |
| --i <ścierzka> | wczytuje dane wejściowe z pliku |
| --o <ścierzka> | zapisuje wynik do pliku | 
| --a (domyślna) | wyświetla wynik w postaci algebraicznej |
| --t | wyświetla wynik w postaci trygonometrycznej |
| --w | wyświetla wynik w postaci wykładniczej |
| --k | rozwiązuje równanie kwadratowe |

Gdy część urojona jest zerowa, wynik jest wyświetlany tylko pod postacią rzeczywistą.

### Przykłady obsługi
input: `kalkulator --awt 1+3i`

output:
```
1 + 3*i
3.162278*(cos(1.249046) + sin(1.249046)*i)
3.162278*e^(1.249046*i)
```
---
input: `kalkulator --t --i input.txt --o output.txt`

wczytuje równanie z pliku wejściowego i zapisuje wyniki do pliku wyjściowego

---
input: `kalkulator --k x^2 + 2x - 8`
```
ROZWIĄZANIA:
-4
2
```
## Działanie aplikacji
Aplikacja zczytuje dane podane przez użytkownika na wejściu, następnie sprawdza ich poprawność i zapisuje w strukturze [Arg](#Args).
Potem, w zależności od wybranego działania rozwiązuje równanie kwadratowe poprzez interpretacje równania, delty i miejsc zerowych, bądź oblicza wynik podanego równania poprzez zamienienie równania na postać Odwróconej Polskiej Notacji i obliczenie jej.
Wyniki obliczeń zapisywane są pod postacią liczb zespolonych i wyświetlone pod postaciami wybranymi przez użytkownika, oraz zapisywane do pliku jeśli użytkownik wybrał taką opcję.


### Struktury danych

#### Options
Przechowuje niektróre argumenty podane przez użytkownika na wejście, oraz informacje o przerwaniu działania programu, przeładowanie operacji bitowych "or" i "and".
```cpp
enum class Options{
    exit
    polar
    rectangular
    exponential
    quadratic_function
};
```

#### Args
Przechowuje argumenty podane przez użytkownika na wejściu.
```cpp
class Args{
    Options options;
    std::string in_path;
    std::string out_path;
    std::string equation;
}
```

#### Complex
Przechowuje liczby zespolone, posiada metody zwracające różne postacii, lub też moduł wartości i argument główny, przeładowane operacje arytmetyczne.
```cpp
class Complex{
  double real;
  double imaginary;
}
```
