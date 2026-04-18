#ifndef KLIENCI_H
#define KLIENCI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//forward declaration
struct Wypozyczenie;

typedef struct Klient 
{
    int numer_karty;
    char imie[20];
    char nazwisko[20];
    char ulica[30];
    char miasto[30];
    int nr_domu;
    int nr_mieszkania;
    char nr_telefonu[15];
    struct Klient *next;
} Klient;

Klient *dodaj_klienta(Klient *head);

void wyswietlanie_klientow(Klient *head);

bool zapis_klienci(Klient *head);

Klient *wczytaj_baze_klientow();

void wyczysc_pamiec_klient(Klient *head);

void Usun_klienta(Klient **h_klienci, Wypozyczenie *head_wypozyczenia);

#endif