//sprawdzanie obecnego OS
#ifdef _WIN32
    #include <direct.h> // library dla Windows
#else
    #include <sys/stat.h> // library dla Linux/Mac
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

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
    int id_sprzetu;
    char nazwa_sprzetu[30];
    double cena_za_dzien;
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
    struct Sprzet *next;
} Sprzet;

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



//funkcja do dodawania klienta
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

//wyswietlanie klientow z RAMu
void wyswietlanie_klientow(Klient *head)
{
    Klient *obecny = head;
    while (obecny != NULL)
    {
        // Format: ID_KARTY|IMIE|NAZWISKO|MIASTO
        printf("%d|%s|%s|%s\n", obecny->numer_karty, obecny->imie, obecny->nazwisko, obecny->miasto);
        obecny = obecny->next;
    }
}

//zapis w pliku albo tworzenie jak nie ma go. robie pod windows i unix/mac. do edycji jeszcze, nie skonczone
bool zapis(Klient *head)
{
    const char *sciezka = "data";
    Klient *obecny = head;
    #ifdef _WIN32
        _mkdir(sciezka);
    #else 
        mkdir(sciezka, 0777);
    #endif
    FILE *zapis;
    zapis = fopen("data/database.bin", "wb");
    if (zapis != NULL)
    {
        while(obecny != NULL)
        {    
            fwrite(obecny, sizeof(Klient), 1, zapis);
            obecny = obecny->next;
        }
        fclose(zapis);
        return true;
    }
    else
    {
        return false;
    }
}
//wczytywanie bazy danych z pliku do RAM
Klient *wczytaj_baze()
{
    FILE *plik = fopen("data/database.bin", "rb");
    Klient *head = NULL;
    Klient temp;

    if (plik != NULL)
    {
        while (fread(&temp, sizeof(Klient), 1, plik) == 1)
        {
            Klient *nowy = malloc(sizeof(Klient));
            *nowy = temp;
            nowy->next = head;
            head = nowy;
        }

    }
    return head;
}

void dodaj_wypozyczenie(Klient **h_klienci, Sprzet **h_sprzet, Wypozyczenie **h_wypozyczenie)
{
    int szukana_karta, szukany_sprzet;
    Klient *obecny_klient = *h_klienci;
    while(obecny_klient != NULL && obecny_klient->numer_karty != szukana_karta)
    {
        obecny_klient = obecny_klient->next;

    }
    if (obecny_klient == NULL)
    {
        printf("Blad. Nie znaleziono klienta!\n");
        return;
    }
    Sprzet *obecny_sprzet = *h_sprzet;
    while(obecny_sprzet != NULL && obecny_sprzet->id_sprzetu != szukany_sprzet)
    {
        obecny_sprzet = obecny_sprzet->next;
    }
    if (obecny_sprzet == NULL)
    {
        printf("Blad. Nie znaleziono sprzetu!\n");
        return;
    }
    if (obecny_sprzet->liczba_wypozyczonych >= obecny_sprzet->liczba_egzemplarzy)
    {
        printf("Blad. Brak wolnego egzemplarza do wypozyczenia!\n");
        return;
    }
    Wypozyczenie *nowe_wypozyczenie = malloc(sizeof(Wypozyczenie));
    if (nowe_wypozyczenie == NULL)
    {
        printf("Blad. Brak pamieci RAM!\n");
        return;
    }
    nowe_wypozyczenie -> numer_karty = szukana_karta;
    nowe_wypozyczenie -> id_sprzetu = szukany_sprzet;
    obecny_sprzet -> liczba_wypozyczonych ++;
    nowe_wypozyczenie -> next = *h_wypozyczenie;
    *h_wypozyczenie = nowe_wypozyczenie;
}

void wyczysc_pamiec(Klient *head)
{
    Klient *obecny = head;
    Klient *tmp;
    while (obecny != NULL)
    {
        tmp = obecny -> next;
        free(obecny);
        obecny = tmp;
    }
}

Sprzet *dodaj_sprzet(Sprzet *head)
{
    Sprzet *nowy_sprzet = malloc(sizeof(Sprzet));
    if (nowy_sprzet == NULL)
    {
        printf("Blad. Brak pamieci RAM!\n");
        return head;
    }
    //ponownie, generowanie numeru ID by bylo pomocne, ale zostawiam narazie wpisywanie reczne
    printf("Podaj ID sprzetu.\n");
    scanf("%d", &nowy_sprzet->id_sprzetu);

    printf("Podaj nazwe sprzetu.\n");
    scanf("%s", nowy_sprzet->nazwa_sprzetu);

    printf("Podaj cene sprzetu za dzien.\n");
    scanf("%lf", &nowy_sprzet->cena_za_dzien);

    printf("Podaj liczbe egzemplarzy.\n");
    scanf("%d", &nowy_sprzet->liczba_egzemplarzy);

    printf("Podaj liczbe wypozyczonych egzemplarzy (Domyslnie nowy sprzet - 0)\n");
    scanf("%d", &nowy_sprzet->liczba_wypozyczonych);
    
    nowy_sprzet->next = head;
    return nowy_sprzet;
}

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
    for (int m = 0; m < dni_miesiaca-1; m++)
    {
        
    }
}

int main()
{
    //heady
    Klient *head_klienci = wczytaj_baze();
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
                    wyczysc_baze(head_klienci);
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