# Wypożyczalnia rowerów – C++

## 1\. Opis projektu

Program służy do obsługi wypożyczalni rowerów. Umożliwia zarządzanie rowerami, ich dodawanie, wypożyczanie, zwracanie oraz wyświetlanie aktualnej listy.

Program posiada tekstowe menu, za pomocą którego użytkownik wybiera odpowiednie operacje.

Dodatkowo zastosowano obsługę plików tekstowych, dzięki której możliwe jest odczytywanie i zapisywanie danych rowerów w pliku `rowery.txt`.

## 2\. Funkcjonalności programu

Program oferuje następujące opcje:

1. **Dodaj rower** – dodawanie nowego roweru do wypożyczalni.
2. **Wypożycz rower** – wypożyczanie roweru na podstawie jego identyfikatora ID. Możliwość wypożyczenia występuje tylko wtedy, gdy rower jest dostępny.
3. **Zwróć rower** – zwracanie wypożyczonego roweru oraz obliczanie kosztu wypożyczenia.
4. **Wyświetl rowery** – wyświetlanie wszystkich rowerów w formie tabeli tekstowej.
5. **Wyjście** – zakończenie działania programu.
6. **Odczytaj rowery z pliku** – wczytywanie danych rowerów z pliku `rowery.txt`.
7. **Zapisz rowery do pliku** – zapisywanie aktualnej listy rowerów wraz ze statusami do pliku `rowery.txt`.

## 3\. Struktura danych

Do przechowywania informacji o rowerach wykorzystano strukturę `Rower`.

Każdy rower posiada następujące pola:

| Pole | Typ | Opis |
| --- | --- | --- |
| id | int | Unikalny identyfikator roweru |
| opis\_roweru | string | Opis roweru |
| rodzaj | string | Rodzaj roweru |
| cena | double | Cena wypożyczenia za godzinę |
| wypozyczony | bool | Status wypożyczenia roweru |

Status roweru:

- `true` – rower jest wypożyczony.
- `false` – rower jest dostępny.

Wszystkie rowery przechowywane są w dynamicznym wektorze `vector<Rower>`.

## 4\. Obliczanie kosztu wypożyczenia

Koszt wypożyczenia obliczany jest na podstawie liczby godzin oraz ceny za jedną godzinę.

**Wzór:**

`koszt = liczba_godzin * cena_za_godzine`

Przykład:

- Cena za godzinę: 25 zł.
- Liczba godzin: 4.
- Całkowity koszt: 100 zł.

Po wykonaniu zwrotu status roweru zmieniany jest na `false`.

## 5\. Obsługa plików

Program wykorzystuje plik tekstowy `rowery.txt`, w którym przechowywane są dane rowerów.

Dane każdego roweru zapisane są w osobnej linii i oddzielone średnikami.

**Format zapisu:**

`id;opis_roweru;rodzaj;cena;wypozyczony`

Przykładowy rekord:

`1;Kross Hexagon;Gorski;25.00;0`

Oznacza to:

- ID: 1
- Opis: Kross Hexagon
- Rodzaj: Gorski
- Cena za godzinę: 25 zł
- Status: dostępny

Wartość `0` oznacza rower dostępny, natomiast `1` oznacza rower wypożyczony.

### Odczyt danych

Funkcja `odczytajZPliku()` odpowiada za:

- otwarcie pliku `rowery.txt`,
- odczyt danych linia po linii,
- rozdzielenie danych za pomocą średników,
- konwersję danych tekstowych na odpowiednie typy,
- sprawdzenie poprawności danych,
- zapisanie odczytanych rowerów w wektorze.

Odczyt z pliku zastępuje aktualną listę rowerów.

### Zapis danych

Funkcja `zapiszDoPliku()` odpowiada za:

- otwarcie pliku do zapisu,
- zapisanie wszystkich rowerów,
- zapisanie aktualnych statusów wypożyczenia,
- nadpisanie poprzedniej zawartości pliku.

Dzięki temu możliwe jest zachowanie zmian wprowadzonych podczas działania programu.

**Uwaga:** Zapis danych odbywa się po wybraniu opcji 7 w menu. Program nie wykonuje automatycznego zapisu podczas zamykania.

## 6\. Obsługa wyjątków

W programie zastosowano mechanizm `try-catch`, który umożliwia obsługę błędów.

Wykorzystano również instrukcję `throw` do zgłaszania wyjątków.

Obsługiwane błędy obejmują między innymi:

- podanie nieprawidłowego ID,
- próbę dodania roweru z istniejącym ID,
- próbę wypożyczenia już wypożyczonego roweru,
- próbę zwrotu roweru, który nie jest wypożyczony,
- podanie nieprawidłowej ceny lub liczby godzin,
- brak możliwości otwarcia pliku,
- nieprawidłowy format danych w pliku,
- powtarzające się identyfikatory w pliku.

## 7\. Wykorzystane elementy języka C++

W projekcie zastosowano:

- `struct` – struktura przechowująca dane roweru.
- `vector` – dynamiczny kontener przechowujący rowery.
- `string` – przechowywanie tekstowych danych rowerów.
- `bool` – określanie statusu wypożyczenia.
- `double` – przechowywanie ceny i obliczanie kosztu.
- `switch-case` – obsługa wyborów menu.
- `do-while` – wielokrotne wyświetlanie menu.
- `for` – iterowanie po wektorze rowerów.
- `try-catch` – obsługa wyjątków.
- `throw` – zgłaszanie wyjątków.
- `ifstream` – odczyt danych z pliku.
- `ofstream` – zapis danych do pliku.
- `getline()` – odczyt linii tekstowych.
- `stringstream` – rozdzielanie danych tekstowych.
- `stoi()` i `stod()` – konwersja tekstu na liczby.
- `setprecision()` i `setw()` – formatowanie wyświetlanych danych.

## 8\. Struktura projektu

text

```text
WypozyczalniaRowerow/
│
├── main.cpp
│
├── rowery.txt
│
└── README.md
```

- `main.cpp` – kod źródłowy programu.
- `rowery.txt` – plik zawierający początkowe dane 10 rowerów oraz aktualne dane po zapisaniu zmian.
- `README.md` – dokumentacja projektu.

## 9\. Uruchomienie programu

Do uruchomienia projektu wymagany jest kompilator obsługujący standard C++11 lub nowszy.

Przykładowa kompilacja za pomocą kompilatora g++:

bash

```bash
g++ main.cpp -o wypozyczalnia -std=c++11
```

Uruchomienie programu w systemie Windows:

bash

```bash
wypozyczalnia.exe
```

Uruchomienie programu w systemie Linux:

bash

```bash
./wypozyczalnia
```

Plik `rowery.txt` powinien znajdować się w katalogu roboczym programu.

## 10\. Podsumowanie

Projekt przedstawia prosty system obsługi wypożyczalni rowerów napisany w języku C++.

Umożliwia zarządzanie rowerami, kontrolowanie ich dostępności, obliczanie kosztów wypożyczenia oraz przechowywanie danych w pliku tekstowym.

W projekcie wykorzystano podstawowe mechanizmy programowania strukturalnego, kontenery STL, obsługę plików oraz obsługę wyjątków.