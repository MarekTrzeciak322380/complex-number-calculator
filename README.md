# Kalkulator liczb zespolonych

## Funkcjonalności
- Wykonywanie operacji arytmetycznych: dodawanie, odejmowanie mnożenie i dzielenie na liczbach rzeczywistych i zespolonych.
- Zamiana/wyświetlanie liczb zespolonych pod postaciami: algebraiczną, trygonometryczną i wykładniczą.
- Obliczanie miejsc zerowych funkcji kwadratowej, wraz z zespolonymi rozwiązaniami, oraz funkcji liniowych.
- Odczytywanie równań z pliku i zapis wyników do pliku.

## Kompilacja
`g++ main.cpp utils/*.cpp classes/*.cpp -o kalkulator`

## Obsługa programu
`kalkulator [flagi] <równanie>`

| Flaga | Opis |
| ----- | ---- |
| --i <ścieżka> | wczytuje dane wejściowe z pliku |
| --o <ścieżka> | zapisuje wynik do pliku | 
| --a (domyślna) | wyświetla wynik w postaci algebraicznej |
| --t | wyświetla wynik w postaci trygonometrycznej |
| --w | wyświetla wynik w postaci wykładniczej |
| --k | znajduje miejsca zerowe równania kwadratowego/liniowego |

W przypadku szukania miejsc zerowych równanie powinno mieć postać:<br/>
`[A]x^2+[B]x+[C]`

W przypadku obliczania wartości (domyślnie), między każdą liczbą, znakiem urojonym, bądź zewnętrzem pary nawiasów powinien znajdować się operator arytmetyczny. Nie należy stosować odstępów między znakami i nie można rozpocząć równania od minusa/plusa.<br/>
Przykład poprawnego równania:<br/>
`1*(2+3*i)-10*i/2`

## Przykłady użycia
Obliczenie wartości i wyświetlenie pod różnymi postaciami

wejście: <br/>
`kalkulator --awt (2+3*i)-(4-2*i)`<br/>

wyjście:
```
(2+3*i)-(4-2*i) =
-2.000000 + (5.000000)*i
5.385165*(cos(1.951303) + sin(1.951303)*i)
5.385165*e^(1.951303*i)
```
---
Wczytanie równania z pliku wejściowego i zapisanie wyniku do pliku wyjściowego.

wejście:<br/>
`kalkulator --t --i input.txt --o output.txt`<br/>

plik wejściowy <i>input.txt</i>:<br/>
`1*(2+3*i)-10*i/2`<br/>

plik wyjściowy <i>output.txt</i>:
```
1*(2+3*i)-10*i/2 =
2.828427*(cos(0.785398) + sin(0.785398)*i)
```
wyjście:
```
Plik wejsciowy: input.txt
Wynik zapisano do pliku: output.txt
1*(2+3*i)-10*i/2 =
2.828427*(cos(0.785398) + sin(0.785398)*i)
```
---
Rozwiązanie funkcji kwadratowej

wejście: <br/>
`kalkulator --k 3x^2-6x+5`<br/>

wyjście:
```
3x^2-6x+5 = 0 dla:
x = 1.000000 + (-0.816497)*i
x = 1.000000 + (0.816497)*i
```

## Działanie aplikacji
### Obsługa argumentów
Aplikacja odczytuje podane przez użytkownika argumenty przy wywołaniu i sprawdza ich poprawność: zgodność flag, czy plik wejściowy istnieje, czy równanie istnieje i czy posiada obsługiwane znaki. Jeśli argumenty nie są poprawne użytkownik dostaje informacje o tym co jest błędne, w przeciwnym wypadku, argumenty są zapisane do struktury Args i przekazane do funkcji rozwiązującej równanie.

### Obliczanie
W zależności od tego co wybrał użytkownik, aplikacja wybiera obliczanie miejsc zerowych równania bądź liczenie jego przybliżonej wartości w postaci rzeczywistej lub zespolonej. 
W przypadku obliczania miejsc zerowych aplikacja sprawdza czy w równaniu występują łańcuchy znaków “x^2” i “x” ściągając ich indeksy i na tej podstawie pobiera z równania wartości liczbowe przy danych potęgach. Potem rozwiązywane jest ewentualne równanie liniowe, lub liczona jest delta i na jej podstawie obliczane są miejsca zerowe, uwzględniając rozwiązania zespolone.
W przypadku obliczania wartości równania, jest ono zamieniane na postać Odwróconej Polskiej Notacji. 

#### Algorytm zamiany wyrażenia na postać OPN
Zmienne:
string rownanie - równanie podane przez użytkownika na wejściu 
stack<string> stos - pomocniczy stos na przechowywanie operatorów
queue<string> wynik - kolejka z wynikiem w postaci OPN

Algorytm po kolei sprawdza znaki równania wejściowego, jeżeli trafi na:
‘i’ - dodaje je do kolejki na wyjście
cyfrę - sprawdza czy następne znaki też są cyframi, łączy je w liczbę i dodaje na stos
operatorem o1 - dopóki na szczycie stosu jest operator o2, który ma wyższy lub równy priorytet kolejności wykonywania działań, to o2 jest przekładany ze stosu na wyjście. W przeciwnym wypadku o1 jest wkładany na stos.
‘(‘ - odkładamy na stos
‘)’ - dopóki na szczycie stosu nie ma ‘(‘ przekłada znak ze stosu na wyjście. W przeciwnym wypadku usuwa ‘(‘ ze stosu.

Tak przygotowana kolejka jest przekazywana do algorytmu obliczającego na jej podstawie wynik. 

#### Obliczanie wyrażenia ONP
queue<string> wejscie - wejściowa kolejka z wyrażeniem postaci OPN
stack<Complex> stos - pomocniczy stos na liczby
vector<Complex> wynik - zwracany wektor z wynikiem, jest on potrzebny z racji kompatybilności z resztą programu 

Algorytm po kolei ściąga znaki z kolejki wejścia i jeżeli trafi na:
liczbę - dodaje ją na górę stosu
‘i’ - dodaje jednostkę urojoną na górę stosu (Complex(0,1))
operator- ściąga liczby A następnie B ze stosu i wykonuje: A operacja B i odkłada wynik na stos
Kiedy kolejka się skończy to jedyny element ze stosu przekazywany jest do wektora wynikowego.

Wyniki miejsc zerowych bądź równania, przechowywane w instancjach klasy Complex, są przekazywane wektorem do funkcji wyświetlającej wynik.

### Wyświetlanie wyniku
Program rozpoznaje które opcję wybrał użytkownik i odpowiednio formatuje na tej podstawie wyświetlany wynik. Rozwiązania równania kwadratowego wyświetlane są jedna po drugiej, jeżeli rozwiązaniem jest liczba zespolona to jest przedstawiana w postaci algebraicznej.
W przypadku naliczonego równania wyświetlane są wybrane przez użytkownika postaci liczb zespolonych. Jeżeli część urojona jest równa zeru to wyświetlana jest tylko część rzeczywista. Wyniki są wyświetlane w konsoli, a jeśli użytkownik podał ścieżkę do pliku wyjściowego, odpowiedź również będzie tam zapisana.

### Struktury danych

#### Options
Przechowuje w postaci bitów niektóre argumenty podane przez użytkownika na wejście, oraz informacje o czy należy przerwać program. Posiada przeładowania operacji bitowych "or" i "and".
```cpp
enum class Options{
   exit = 1 << 0,
   polar = 1 << 1,
   rectangular = 1 << 2,
   exponential = 1 << 3,
   quadratic_function = 1 << 4,
};
```
---
#### Args
Przechowuje argumenty podane przez użytkownika na wejściu. Posiada metodr na sprawdzanie czy dany argument został podany przez użytkownika.
```cpp
class Args{
    Options options;
    std::string in_path;
    std::string out_path;
    std::string equation;
}
```
---
#### Complex
Przechowuje część rzeczywistą i urojoną liczby zespolonej. Posiada metody zwracające różne postaci, lub też moduł wartości i argument główny. Przeładowane operacje arytmetyczne: dodawania, odejmowania, mnożenia i dzielenia.
```cpp
class Complex{
  double real;
  double imaginary;
}
```

## Podsumowanie
Aplikacja poprawnie realizuje podstawowe założenia: operacje wejścia/wyjścia w konsoli i na plikach, poprawnie oblicza miejsca zerowe funkcji liniowych i kwadratowych, oblicza przybliżone wartości równań z liczbami zespolonymi, oraz oferuje wyświetlanie ich w wybranych postaciach. Modułowa struktura projektu, oraz wykorzystanie klas umożliwia łatwe rozbudowywanie projektu w przyszłości.

## Możliwe poprawy/rozwinięcia funkcjonalności
- Lepsza interpretacja równania wejściowego:
    - Domniemanie mnożenia w tam gdzie jest to poprawne np.: między zewnętrzem nawiasów, między liczbą a jednostką urojoną.
    - Przyzwolenie na zaczynanie równania od minusa
    - Ignorowanie białych znaków
- Wyświetlanie wyników z dynamicznym/podanym przez użytkownika zaokrągleniem, obecnie jest to 6 cyfr po przecinku. 
- Dodanie możliwości wyświetlania wyniku w przyjaznej postaci równania arytmetycznego np. 2+3sqrt(3).
- Użycie innego algorytmu niż ONP, obecnie generuje to dodatkową potrzebę przekształcenia równania z wejścia na postać ONP i dopiero potem obliczenie wyniku. Można od razu przeliczać równanie na wynik.
- Utworzenie struktury opisującej lepiej operatory przy obsłudze ONP

## Zdjęcia
<img width="939" height="247" alt="image" src="https://github.com/user-attachments/assets/69c86341-7edc-43e1-9048-05baf0e0d344" />
<img width="957" height="104" alt="image" src="https://github.com/user-attachments/assets/571e784c-3170-462c-9bf8-2b8169b9572f" />
<img width="994" height="312" alt="image" src="https://github.com/user-attachments/assets/d307e1fc-e210-4a57-94f7-dc97237b3364" />
<img width="893" height="111" alt="image" src="https://github.com/user-attachments/assets/4322a72a-72f2-479f-bf53-ab92cb3a068a" />

