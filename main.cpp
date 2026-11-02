
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;


// STRUKTURA ROWER
// Przechowywanie wszystkich informacji dotyczacych jednego roweru.
struct Rower {
    int id;                 // Unikalny identyfikator roweru
    string opis_roweru;     // Opis roweru
    string rodzaj;          // Rodzaj roweru
    double cena;            // Cena wypozyczenia za godzine
    bool wypozyczony;       // true - rower wypozyczony
                            // false - rower dostepny
};


// WEKTOR ROWEROW
// Przechowywanie wszystkich rowerow znajdujacych sie w wypozyczalni.
vector<Rower> rowery;


// FUNKCJA ZNAJDZROWER
// Wyszukiwanie roweru na podstawie podanego ID.
// Zwracanie indeksu znalezionego roweru.
// W przypadku braku roweru zwracanie wartosci -1.
int znajdzRower(int id) {

    for (int i = 0; i < rowery.size(); i++) {

        if (rowery[i].id == id) {
            return i;
        }
    }

    return -1;
}


// FUNKCJA DODAJROWER
// Dodawanie nowego roweru do wektora.
// Pobieranie danych roweru od uzytkownika.
// Sprawdzanie poprawnosci ID oraz ceny.
// Ustawianie poczatkowego statusu roweru na dostepny.
void dodajRower() {

    Rower r;

    try {

        cout << "\nPodaj ID roweru: ";

        if (!(cin >> r.id))
            throw invalid_argument("Nieprawidlowe ID!");

        // Sprawdzenie, czy podane ID juz istnieje.
        if (znajdzRower(r.id) != -1)
            throw runtime_error("Rower o takim ID juz istnieje!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Pobieranie opisu roweru.
        cout << "Podaj opis roweru: ";
        getline(cin, r.opis_roweru);

        // Pobieranie rodzaju roweru.
        cout << "Podaj rodzaj roweru: ";
        getline(cin, r.rodzaj);

        // Pobieranie ceny za godzine.
        cout << "Podaj cene za godzine: ";

        if (!(cin >> r.cena))
            throw invalid_argument("Nieprawidlowa cena!");

        // Sprawdzenie poprawnosci ceny.
        if (r.cena < 0)
            throw invalid_argument("Cena nie moze byc ujemna!");

        // Ustawienie statusu nowego roweru na dostepny.
        r.wypozyczony = false;

        // Dodanie roweru do wektora.
        rowery.push_back(r);

        cout << "\nRower zostal dodany!\n";
    }

    // Obsluga wyjatkow i bledow wprowadzania danych.
    catch (const exception& e) {

        cout << "Blad: " << e.what() << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// FUNKCJA WYPOZYCZROWER
// Wypozyczanie roweru na podstawie podanego ID.
// Sprawdzanie istnienia roweru oraz jego dostepnosci.
// Zmiana statusu roweru na wypozyczony.
void wypozyczRower() {

    int id;

    try {

        // Pobieranie ID wypozyczanego roweru.
        cout << "\nPodaj ID roweru do wypozyczenia: ";

        if (!(cin >> id))
            throw invalid_argument("Nieprawidlowe ID!");

        // Wyszukanie roweru w wektorze.
        int indeks = znajdzRower(id);

        // Sprawdzenie istnienia roweru.
        if (indeks == -1)
            throw runtime_error("Nie znaleziono roweru!");

        // Sprawdzenie aktualnego statusu roweru.
        if (rowery[indeks].wypozyczony)
            throw runtime_error("Rower jest juz wypozyczony!");

        // Zmiana statusu roweru na wypozyczony.
        rowery[indeks].wypozyczony = true;

        cout << "Rower zostal wypozyczony!\n";
    }

    // Obsluga wyjatkow.
    catch (const exception& e) {

        cout << "Blad: " << e.what() << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// FUNKCJA ZWROCROWER
// Zwracanie wypozyczonego roweru.
// Pobieranie ID roweru oraz liczby godzin wypozyczenia.
// Obliczanie kosztu wedlug wzoru: liczba godzin * cena.
// Zmiana statusu roweru na dostepny.
void zwrocRower() {

    int id;
    double godziny;

    try {

        // Pobieranie ID zwracanego roweru.
        cout << "\nPodaj ID zwracanego roweru: ";

        if (!(cin >> id))
            throw invalid_argument("Nieprawidlowe ID!");

        // Wyszukanie roweru.
        int indeks = znajdzRower(id);

        // Sprawdzenie istnienia roweru.
        if (indeks == -1)
            throw runtime_error("Nie znaleziono roweru!");

        // Sprawdzenie statusu roweru.
        if (!rowery[indeks].wypozyczony)
            throw runtime_error("Ten rower nie jest wypozyczony!");

        // Pobieranie liczby godzin wypozyczenia.
        cout << "Podaj liczbe godzin wypozyczenia: ";

        if (!(cin >> godziny))
            throw invalid_argument("Nieprawidlowa liczba godzin!");

        // Sprawdzenie poprawnosci liczby godzin.
        if (godziny <= 0)
            throw invalid_argument("Liczba godzin musi byc wieksza od 0!");

        // Obliczanie calkowitego kosztu wypozyczenia.
        double koszt = godziny * rowery[indeks].cena;

        // Zmiana statusu roweru na dostepny.
        rowery[indeks].wypozyczony = false;

        // Ustawienie dokladnosci wyswietlania do dwoch miejsc po przecinku.
        cout << fixed << setprecision(2);

        // Wyswietlanie kosztu wypozyczenia.
        cout << "\nKoszt wypozyczenia: "
             << koszt << " zl\n";

        cout << "Rower zostal zwrocony!\n";
    }

    // Obsluga wyjatkow.
    catch (const exception& e) {

        cout << "Blad: " << e.what() << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// FUNKCJA WYSWIETLROWERY
// Wyswietlanie wszystkich rowerow w postaci tabeli tekstowej.
// Prezentowanie ID, opisu, rodzaju, ceny oraz aktualnego statusu.
void wyswietlRowery() {

    cout << "\n";

    // Gorne obramowanie tabeli.
    cout << "---------------------------------------------------------------------\n";

    // Naglowki poszczegolnych kolumn.
    cout << left
         << setw(6) << "ID"
         << setw(20) << "Opis"
         << setw(15) << "Rodzaj"
         << setw(12) << "Cena"
         << setw(15) << "Status" << endl;

    cout << "---------------------------------------------------------------------\n";

    // Przechodzenie przez wszystkie rowery w wektorze.
    for (const Rower& r : rowery) {

        // Wyswietlanie danych aktualnego roweru.
        cout << left
             << setw(6) << r.id
             << setw(20) << r.opis_roweru
             << setw(15) << r.rodzaj
             << setw(12) << fixed << setprecision(2) << r.cena

             // Wyswietlanie statusu roweru.
             // true - Wypozyczony, false - Dostepny.
             << setw(15) << (r.wypozyczony ? "Wypozyczony" : "Dostepny")

             << endl;
    }

    // Dolne obramowanie tabeli.
    cout << "---------------------------------------------------------------------\n";
}


// FUNKCJA ODCZYTAZZPLIKU
// Odczytywanie danych rowerow z pliku tekstowego rowery.txt.
// Sprawdzanie poprawnosci odczytanych danych.
// Zapisywanie odczytanych rekordow w wektorze.
// Zastepowanie aktualnej listy rowerami z pliku.
void odczytajZPliku() {

    try {

        // Otwarcie pliku do odczytu.
        ifstream plik("rowery.txt");

        // Sprawdzenie poprawnosci otwarcia pliku.
        if (!plik.is_open())
            throw runtime_error("Nie mozna otworzyc pliku rowery.txt!");

        // Tymczasowy wektor na odczytane rowery.
        vector<Rower> noweRowery;

        string linia;
        int numerLinii = 0;

        // Odczytywanie pliku linia po linii.
        while (getline(plik, linia)) {

            numerLinii++;

            // Pomijanie pustych linii.
            if (linia.empty())
                continue;

            // Utworzenie strumienia dla aktualnej linii.
            stringstream ss(linia);

            Rower r;

            string idTekst;
            string cenaTekst;
            string statusTekst;
            string dodatkoweDane;

            // Odczytywanie poszczegolnych pol oddzielonych srednikiem.
            if (!getline(ss, idTekst, ';') ||
                !getline(ss, r.opis_roweru, ';') ||
                !getline(ss, r.rodzaj, ';') ||
                !getline(ss, cenaTekst, ';') ||
                !getline(ss, statusTekst, ';')) {

                throw runtime_error(
                    "Nieprawidlowy format danych w linii " +
                    to_string(numerLinii)
                );
            }

            // Sprawdzenie wystepowania dodatkowych pol.
            if (getline(ss, dodatkoweDane, ';'))
                throw runtime_error("Za duzo danych w linii pliku!");

            // Konwersja danych tekstowych na odpowiednie typy.
            size_t pozycja;

            r.id = stoi(idTekst, &pozycja);

            if (pozycja != idTekst.size())
                throw runtime_error("Nieprawidlowe ID w pliku!");

            r.cena = stod(cenaTekst, &pozycja);

            if (pozycja != cenaTekst.size())
                throw runtime_error("Nieprawidlowa cena w pliku!");

            int status = stoi(statusTekst, &pozycja);

            if (pozycja != statusTekst.size())
                throw runtime_error("Nieprawidlowy status w pliku!");

            // Sprawdzenie poprawnosci ID, ceny i statusu.
            if (r.id <= 0)
                throw runtime_error("ID musi byc wieksze od zera!");

            if (r.cena < 0)
                throw runtime_error("Cena nie moze byc ujemna!");

            if (status != 0 && status != 1)
                throw runtime_error("Status musi wynosic 0 lub 1!");

            if (r.opis_roweru.empty() || r.rodzaj.empty())
                throw runtime_error("Opis i rodzaj nie moga byc puste!");

            // Ustawienie statusu roweru na podstawie danych z pliku.
            r.wypozyczony = (status == 1);

            // Sprawdzenie unikalnosci ID.
            for (const Rower& x : noweRowery) {

                if (x.id == r.id)
                    throw runtime_error("Powtorzone ID roweru w pliku!");
            }

            // Dodanie odczytanego roweru do tymczasowego wektora.
            noweRowery.push_back(r);
        }

        // Zamkniecie pliku.
        plik.close();

        // Sprawdzenie, czy plik zawiera jakiekolwiek rowery.
        if (noweRowery.empty())
            throw runtime_error("Plik nie zawiera rowerow!");

        // Zastapienie aktualnej listy danymi z pliku.
        rowery = noweRowery;

        cout << "\nPomyslnie odczytano "
             << rowery.size()
             << " rowerow z pliku!\n";
    }

    // Obsluga wyjatkow podczas odczytu.
    catch (const exception& e) {

        cout << "Blad odczytu pliku: " << e.what() << endl;
    }
}


// FUNKCJA ZAPISZDOPlIKU
// Zapisywanie wszystkich aktualnych rowerow do pliku rowery.txt.
// Nadpisywanie poprzedniej zawartosci pliku.
// Zapisywanie aktualnych danych i statusow rowerow.
void zapiszDoPliku() {

    try {

        // Otwarcie pliku do zapisu.
        // ios::trunc - nadpisanie poprzedniej zawartosci.
        ofstream plik("rowery.txt", ios::out | ios::trunc);

        // Sprawdzenie poprawnosci otwarcia pliku.
        if (!plik.is_open())
            throw runtime_error("Nie mozna otworzyc pliku do zapisu!");

        // Przechodzenie przez wszystkie rowery.
        for (const Rower& r : rowery) {

            // Zapisywanie danych w formacie oddzielonym srednikami.
            plik << r.id << ";"
                 << r.opis_roweru << ";"
                 << r.rodzaj << ";"
                 << fixed << setprecision(2) << r.cena << ";"
                 << (r.wypozyczony ? 1 : 0)
                 << endl;
        }

        // Sprawdzenie poprawnosci zapisu.
        if (!plik)
            throw runtime_error("Wystapil blad podczas zapisywania!");

        // Zamkniecie pliku.
        plik.close();

        cout << "\nPomyslnie zapisano "
             << rowery.size()
             << " rowerow do pliku rowery.txt!\n";
    }

    // Obsluga wyjatkow podczas zapisu.
    catch (const exception& e) {

        cout << "Blad zapisu pliku: " << e.what() << endl;
    }
}


// FUNKCJA MAIN
// Glowna funkcja programu.
// Wyswietlanie menu i obsluga wyborow uzytkownika.
// Powtarzanie menu do momentu wybrania opcji 5.
int main() {

    int wybor = 0;

    do {

        // Wyswietlanie menu glownego.
        cout << "\n========== WYPOZYCZALNIA ROWEROW ==========\n";

        // OPCJA 1 - DODAWANIE ROWERU.
        cout << "1. Dodaj rower\n";

        // OPCJA 2 - WYPOZYCZANIE ROWERU.
        cout << "2. Wypozycz rower\n";

        // OPCJA 3 - ZWRACANIE ROWERU.
        cout << "3. Zwroc rower\n";

        // OPCJA 4 - WYSWIETLANIE ROWEROW.
        cout << "4. Wyswietl rowery\n";

        // OPCJA 5 - WYJSCIE Z PROGRAMU.
        cout << "5. Wyjscie\n";

        // OPCJA 6 - ODCZYT DANYCH Z PLIKU.
        cout << "6. Odczytaj rowery z pliku\n";

        // OPCJA 7 - ZAPIS DANYCH DO PLIKU.
        cout << "7. Zapisz rowery do pliku\n";

        cout << "===========================================\n";

        // Pobieranie wyboru uzytkownika.
        cout << "Wybierz opcje: ";

        try {

            // Sprawdzenie poprawnosci wprowadzonego wyboru.
            if (!(cin >> wybor))
                throw invalid_argument("Wybor musi byc liczba!");

            // Wybor odpowiedniej funkcji na podstawie numeru opcji.
            switch (wybor) {

                // OPCJA 1 - DODAWANIE ROWERU.
                case 1:
                    dodajRower();
                    break;

                // OPCJA 2 - WYPOZYCZANIE ROWERU.
                case 2:
                    wypozyczRower();
                    break;

                // OPCJA 3 - ZWRACANIE ROWERU.
                case 3:
                    zwrocRower();
                    break;

                // OPCJA 4 - WYSWIETLANIE ROWEROW.
                case 4:
                    wyswietlRowery();
                    break;

                // OPCJA 5 - ZAKONCZENIE PROGRAMU.
                case 5:
                    cout << "Koniec programu.\n";
                    break;

                // OPCJA 6 - ODCZYT Z PLIKU.
                case 6:
                    odczytajZPliku();
                    break;

                // OPCJA 7 - ZAPIS DO PLIKU.
                case 7:
                    zapiszDoPliku();
                    break;

                // OBSLUGA NIEPRAWIDLOWEGO WYBORU.
                default:
                    cout << "Nie ma takiej opcji!\n";
            }
        }

        // Obsluga wyjatkow zwiazanych z wyborem opcji.
        catch (const exception& e) {

            cout << "Blad: " << e.what() << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    // Powtarzanie menu do momentu wybrania opcji 5.
    } while (wybor != 5);

    // Zakonczenie programu.
    return 0;
}
