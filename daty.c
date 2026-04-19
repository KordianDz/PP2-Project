#include "daty.h"

//co 4 lata przestepny, co 100 lat skreslamy przestepny bo dzien trwa ~365,25dni, wyjatek co 400 lat kiedy blad arytmetyczny czasu gregorianskiego sie wyrownuje
//uwaga! jak obliczenia sa ok to strata to 1 dzien co 3300 lat
bool czy_przystepny_rok(int rok)
{
    if ((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int oblicz_dni_od_zera(Data d)
{
    int dni_zwykly[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dni_przestepny[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long suma_dni = 0;

    for (int i = 1; i < d.rok; i++)
    {
        if(czy_przystepny_rok(i))
        {
            suma_dni += 366;
        }
        else
        {
            suma_dni += 365;
        }

    }
    int *dni_miesiaca;
    if (czy_przystepny_rok(d.rok))
    {
        dni_miesiaca = dni_przestepny;
    }
    else
    {
        dni_miesiaca = dni_zwykly;
    }
    for (int m = 0; m < d.miesiac - 1; m++)
    {
        suma_dni = dni_miesiaca[m] + suma_dni;
    }
    suma_dni = suma_dni + d.dzien;
    return suma_dni;
}
