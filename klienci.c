#include "klienci.h"
#include "wypozyczenia.h"
#include "funkcje_universalne.h"
#include <string.h>

#ifdef _WIN32
    #include <direct.h>
#else 
    #include <sys/stat.h>
#endif


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
    scanf("%19s", nowy_klient->imie);

    printf("Podaj nazwisko.\n");
    scanf("%29s", nowy_klient->nazwisko);

    printf("Podaj ulice.\n");
    getchar();
    fgets(nowy_klient->ulica, 30, stdin);
    // podmienienie pobranego \n na znak konca tekstu
    nowy_klient->ulica[strlen(nowy_klient->ulica) - 1] = '\0';

    printf("Podaj miasto.\n");
    fgets(nowy_klient->miasto, 30, stdin);
    nowy_klient->miasto[strlen(nowy_klient->miasto) - 1] = '\0';

    printf("Podaj numer domu.\n");
    scanf("%d", &nowy_klient->nr_domu);

    printf("Podaj numer mieszkania.\n");
    scanf("%d", &nowy_klient->nr_mieszkania);

    printf("Podaj numer telefonu. Mozna dodac numer kierunkowy.\n");
    getchar();
    fgets(nowy_klient->nr_telefonu, 20, stdin);
    nowy_klient->nr_telefonu[strlen(nowy_klient->nr_telefonu) - 1] = '\0';


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

void wyswietlanie_klientow_alfabetycznie_nazwisko(Klient *head)
{
    if (head == NULL)
        return;
    if (head->next == NULL)
        {
            printf("%d|%s|%s|%s\n", head->numer_karty, head->imie, head->nazwisko, head->miasto);
            return;
        }

    Klient *obecny = head;
    Klient *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {
                if(porownaj_male_litery(obecny->nazwisko, nastepny->nazwisko) > 0)
            {
                Klient *oryginal_obecny_next = obecny->next;
                Klient *oryginal_nastepny_next = nastepny->next;

                Klient temp = *obecny;
                *obecny = *nastepny;
                *nastepny = temp;

                obecny->next = oryginal_obecny_next;
                nastepny->next = oryginal_nastepny_next;

                zamieniono = true;
            }
        obecny = obecny->next;
        nastepny = nastepny->next;
        }
        
    }
    while (zamieniono == true);

    obecny = head;
    while (obecny != NULL)
    {
    printf("%d|%s|%s|%s\n", obecny->numer_karty, obecny->imie, obecny->nazwisko, obecny->miasto);
    obecny = obecny->next;
    }
}

void wyswietlanie_klientow_alfabetycznie_imie(Klient *head)
{
    if (head == NULL)
        return;
    if (head->next == NULL)
        {
            printf("%d|%s|%s|%s\n", head->numer_karty, head->imie, head->nazwisko, head->miasto);
            return;
        }

    Klient *obecny = head;
    Klient *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {
                if(porownaj_male_litery(obecny->imie, nastepny->imie) > 0)
            {
                
                Klient *oryginal_obecny_next = obecny->next;
                Klient *oryginal_nastepny_next = nastepny->next;

                Klient temp = *obecny;
                *obecny = *nastepny;
                *nastepny = temp;

                obecny->next = oryginal_obecny_next;
                nastepny->next = oryginal_nastepny_next;

                zamieniono = true;
            }
        obecny = obecny->next;
        nastepny = nastepny->next;
        }
        
    }
    while (zamieniono == true);

    obecny = head;
    while (obecny != NULL)
    {
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

void Usun_klienta(Klient **h_klienci, struct Wypozyczenie *head_wypozyczenia)
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

void wyszukaj_klienta(Klient *head)
{
    int szukaj_po_karcie;
    Klient *szukany = head;

    printf("Podaj numer karty klienta.\n");
    scanf(" %d", &szukaj_po_karcie);

    while(szukany != NULL && szukaj_po_karcie != szukany->numer_karty)
    {
        szukany = szukany->next;
    }
    if(szukany == NULL)
    {
        printf("Nie znaleziono klienta z takim numerem karty!");
    }
    else
    {
        printf("%d|%s|%s|%s\n", szukany->numer_karty, szukany->imie, szukany->nazwisko, szukany->miasto);
    }
}

void wyszukaj_klienta_imie_nazwisko(Klient *head)
{
    char temp_imie[20];
    char temp_nazwisko[30];
    Klient *obecny = head;
    bool znaleziono = false;

    printf("Podaj imie klienta\n");
    scanf("%19s", temp_imie);

    printf("Podaj nazwisko klienta\n");
    scanf("%29s", temp_nazwisko);

    while(obecny != NULL)
    {

         if(strcmp(obecny->imie, temp_imie) == 0 && strcmp(obecny->nazwisko, temp_nazwisko) == 0)
         {
           printf("%d|%s|%s|%s\n", obecny->numer_karty, obecny->imie, obecny->nazwisko, obecny->miasto);
           znaleziono = true;
         }
         obecny = obecny->next;

    }
    if(znaleziono == false)
    {
        printf("Nie znaleziono klienta w bazie danych.\n");
    }

}
