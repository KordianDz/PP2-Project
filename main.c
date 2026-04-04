#include <stdio.h>

typedef struct Data 
{
    int dzien;
    int miesiac;
    int rok;
} Data;

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

typedef struct Sprzet
{
    int ID;
    char nazwa_sprzetu[30];
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
    struct Sprzet *next;
} Sprzet;

typedef struct Wypozyczenie
{
    int numer_karty;
    int id;
    Data data_wypozyczenia;
    Data data_oddania;
    struct Wypozyczenie *next;
} Wypozyczenie;


int main()
{
    while(1)
    {
        int opcja = 0;
        printf("Witamy. Wybierz opcję do administracji systemu wypożyczania nart.\n");
        printf("1. Wyświetl bazę danych.\n");
        printf("2. Edytuj bazę danych.\n");
        printf("3. Zamknij program.\n");
        if (scanf("%d", &opcja) != 1)
        {
            while(getchar() != '\n');
            opcja = -1;
        }
        else
        {
            switch (opcja)
            {
            case 1:
                {
                    printf("Wyświetlam bazę danych.\n");
                    break;
                }
            case 2:
                {
                    printf("Rozpoczynam edycję bazy danych.\n");
                    break;
                }
            case 3:
                {
                    printf("Zamykanie...\n");
                    return 0;
                }
            default:
                {
                    printf("Wybrano nieprawidłową opcję. Spróbuj ponownie.");
                    break;   
                }
            }
        }
    }

    return 1;
}
int b;