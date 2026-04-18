#ifndef WYPOZYCZENIA_H
#define WYPOZYCZENIA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "daty.h"
#include "klienci.h"
#include "sprzet.h"


typedef struct Wypozyczenie
{
    int numer_karty;
    int id_sprzetu;
    Data data_wypozyczenia;
    Data przewidywana_data_oddania;
    Data realna_data_oddania;
    double oplacona_kwota;
    struct Wypozyczenie *next;
} Wypozyczenie;

void wyswietlanie_ofert(Wypozyczenie *head);

bool zapis_archiwum(Wypozyczenie *head_archiwum);

bool zapis_oferty(Wypozyczenie *head_wypozyczenia);

Wypozyczenie *wczytaj_baze_ofert();

Wypozyczenie *wczytaj_archiwum();

void dodaj_wypozyczenie(Klient **h_klienci, Sprzet **h_sprzet, Wypozyczenie **h_wypozyczenie);

void zwroc_sprzet(Klient **hz_klienci, Sprzet **hz_sprzet, Wypozyczenie **hz_wypozyczenie, Wypozyczenie **hz_archiwum);

void wyczysc_pamiec_archiwum(Wypozyczenie *head);

void wyczysc_pamiec_oferty(Wypozyczenie *head);

#endif