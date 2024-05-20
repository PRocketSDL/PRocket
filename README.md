## RocketSIM

## *Ce ar trebui sa faca programul?*

Reconstituirea drumului unei nave prin spatiu, acesta fiind afectat de lucruri precum: planete, comete, stele, etc.

## *Cum este structurat proiectul?*

Fiecare pagina(meniu, programul principal, setari, etc.) va avea un header file, unde se vor declara variabile, functii, etc. si un .cpp file, unde se va scrie codul in sine.

## *Compilarea programului (Linux)*

sudo g++ -Wall -lSDL2 -lSDL2_ttf "fisierul principal" -std=c++20 -o RocketSIM

-std=c++20 pentru biblioteca de procesare ini

## *Compilarea programului (Windows)*

g++ menu.cpp -Iext_deps -Lext_deps/lib -lSDL2 -lSDL2_ttf -lcomdlg32 -std=c++20 -o RocketSIM
