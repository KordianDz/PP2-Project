#ifndef SPRZET_H
#define SPRZET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Sprzet
{
    int id_sprzetu;
    char nazwa_sprzetu[30];
    double cena_za_dzien;
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
    struct Sprzet *next;
} Sprzet;

bool zapis_sprzet(Sprzet *head_sprzet);

Sprzet *wczytaj_sprzet();

void wyswietlanie_sprzetu(Sprzet *head);

void wyswietlanie_sprzet_po_id(Sprzet *head, int kierunek);

void wyswietlanie_sprzetu_alfabetycznie(Sprzet *head, int kierunek);

void wyswietlanie_sprzet_po_egzemplarzach(Sprzet *head, int kierunek);

void wyswietlanie_sprzet_po_wypozyczonych(Sprzet *head, int kierunek);

void wyczysc_pamiec_sprzet(Sprzet *head);

Sprzet *dodaj_sprzet(Sprzet *head);

void usun_sprzet(Sprzet **h_sprzet);

void wyszukaj_sprzet(Sprzet *head);

void wyszukaj_sprzet_nazwa(Sprzet *head);


#endif