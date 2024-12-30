# Egzamino (Išankstinė) užduotis


## Aprašymas

Programa suteikia galimybes
1. pasirinkti suskaiciuoti kiek kartu tekste pasikartoja zodziai, taciau tik tie, kurie pasikartoja daugiau nei viena karta
2. kuriose eilutese yra zodziai, pasikartojantys daugiau nei viena karta
3. isrinkti is teksto URL linkus

## Rezultatų išvedimas

Gauti rezultatai pateikiami txt faile "outputas.txt".

## Įdiegimo instrukcija

Norint sėkmingai paleisti šią programą, reikalinga CMake įrankio versija 3.14 ar naujesnė. Taip pat reikalingas C++ kompiliatorius, palaikantis C++17 standartą.

### Programos kompiliavimas

Atidarykite terminalą savo projekto aplankale ir vykdykite šias komandas:

mkdir build
cd build
cmake ..
cmake --build .
cmake --install .
Savo .exe faila galima rasti Debug aplankale
