# Egzamino (Isankstine) uzduotis

## Aprasymas

Programa suteikia galimybes
1. pasirinkti suskaiciuoti kiek kartu tekste pasikartoja zodziai, taciau tik tie, kurie pasikartoja daugiau nei viena karta
2. kuriose eilutese yra zodziai, pasikartojantys daugiau nei viena karta
3. isrinkti is teksto URL linkus

## Rezultatu isvedimas

Gauti rezultatai pateikiami txt faile "outputas.txt".

## Idegimo instrukcija

Norint sekmingai paleisti sia programa, reikalinga CMake irankio versija 3.14 ar naujesne. Taip pat reikalingas C++ kompiliatorius, palaikantis C++17 standarta.

### Programos kompiliavimas

Atidarykite terminala savo projekto aplankale ir vykdykite sias komandas:

```
mkdir build  
cd build  
cmake ..  
cmake --build .  
cmake --install .  
Savo .exe faila galima rasti Debug aplankale
```