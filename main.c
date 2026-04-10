#include <stdio.h>
#include <stdlib.h>

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

//funkcja do dodawania 
Klient *dodaj_klienta(Klient *head)
{
    Klient *nowy_klient = malloc(sizeof(Klient));
    if (nowy_klient == NULL)
    {
        printf("Blad. Brak pamieci RAM!\n");
        return head;
    }
    // generowanie numeru karty? narazie daje w formie zwyklego wpisania
    printf("Podaj numer karty\n");
    scanf("%d", &nowy_klient->numer_karty);

    printf("Podaj imie.\n");
    scanf("%s", nowy_klient->imie);

    printf("Podaj nazwisko.\n");
    scanf("%s", nowy_klient->nazwisko);

    printf("Podaj ulice.\n");
    scanf("%s", nowy_klient->ulica);

    printf("Podaj miasto.\n");
    scanf("%s", nowy_klient->miasto);

    printf("Podaj numer domu.\n");
    scanf("%d", &nowy_klient->nr_domu);

    printf("Podaj numer mieszkania.\n");
    scanf("%d", &nowy_klient->nr_mieszkania);

    printf("Podaj numer telefonu. Mozna dodac numer kierunkowy.\n");
    scanf("%s", nowy_klient->nr_telefonu);

    nowy_klient->next = head;
    return nowy_klient;
}

//nieskonczone wyswietlanie w formie zwyklego tekstu
void wyswietlanie_klientow(Klient *head)
{
    Klient *obecny = head;
    while (obecny != NULL)
    {
        printf("%s %s\n", obecny->imie, obecny->nazwisko);
        obecny = obecny->next;
    }
}



int main()
{
    //heady
    Klient *head_klienci = NULL;
    Sprzet *head_sprzet = NULL;
    Wypozyczenie *head_wypozyczenia = NULL;
    
    //main sys nieskonczony
    while(1)
    {
        int opcja = 0;
        printf("Witamy. Wybierz opcję do administracji systemu wypożyczania nart.\n");
        printf("1. Wyświetl bazę danych.\n");
        printf("2. Dodaj klienta.\n");
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
                    printf("Rozpoczynam dodawanie klienta do bazy danych.\n");
                    head_klienci = dodaj_klienta(head_klienci);

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