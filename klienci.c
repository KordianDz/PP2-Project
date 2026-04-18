#include "klienci.h"
#include "wypozyczenia.h"

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

bool zapis_klienci(Klient *head)
{
    const char *sciezka = "data";
    Klient *obecny = head;
    #ifdef _WIN32
        _mkdir(sciezka);
    #else 
        mkdir(sciezka, 0777);
    #endif
    FILE *zapis;
    zapis = fopen("data/database_clients.bin", "wb");
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

Klient *wczytaj_baze_klientow()
{
    FILE *plik = fopen("data/database_clients.bin", "rb");
    Klient *head = NULL;
    Klient *ostatni = NULL; //dodalem aby moc "obrocic" liste, bo tak to wczyta sie do ramu do gory nogami
    Klient temp;

    if (plik != NULL)
    {
        while (fread(&temp, sizeof(Klient), 1, plik) == 1)
        {
            Klient *nowy = malloc(sizeof(Klient));
            *nowy = temp;
            nowy->next = NULL;
            
            if(head == NULL)
            {
                head = nowy;
                ostatni = nowy;
            }
            else
            {
                ostatni->next = nowy;
                ostatni = nowy;
            }
        }
        fclose(plik);
    }
    return head;
}

void wyczysc_pamiec_klient(Klient *head)
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

void Usun_klienta(Klient **h_klienci, Wypozyczenie *head_wypozyczenia)
{
    int szukany_nr_karty;
    printf("Podaj numer karty klienta do usuniecia: ");
    scanf("%d", &szukany_nr_karty);
    Wypozyczenie *obecne_wypozyczenie = head_wypozyczenia;

    while (obecne_wypozyczenie != NULL)
    {
        if(obecne_wypozyczenie->numer_karty == szukany_nr_karty)
        {
            printf("Blad! Klient ma wciaz wypozyczony sprzet. Nie mozna usunac.\n");
            return;
        }
        obecne_wypozyczenie = obecne_wypozyczenie->next;
    }
    printf("Klient ma czysta karte. Zaczynam usuwanie...\n");
    Klient *obecny_klient = *h_klienci;
    Klient *poprzedni_klient = NULL;
    while(obecny_klient != NULL && szukany_nr_karty != obecny_klient->numer_karty)
    {
        poprzedni_klient = obecny_klient;
        obecny_klient = obecny_klient->next;
    }
    if(obecny_klient == NULL)
        {
            printf("Nie odnaleziono klienta!");
            return;
        }
    if (poprzedni_klient == NULL)
    {
        *h_klienci = obecny_klient->next;
    }
    else
    {
        poprzedni_klient->next = obecny_klient->next;
    }
    free(obecny_klient);
    printf("Pomyslnie usunieto klienta z bazy.\n");
    return;
}
