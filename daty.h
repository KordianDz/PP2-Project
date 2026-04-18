#ifndef DATY_H
#define DATY_H

#include <stdbool.h>

typedef struct Data 
{
    int dzien;
    int miesiac;
    int rok;
} Data;

bool czy_przystepny_rok(int rok);
int oblicz_dni_od_zera(Data d);

#endif