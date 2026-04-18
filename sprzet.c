#include "sprzet.h"

#ifdef _WIN32
    #include <direct.h>
#else 
    #include <sys/stat.h>
#endif

bool zapis_sprzet(Sprzet *head_sprzet)
{
    const char *sciezka = "data";
    Sprzet *obecny = head_sprzet;
    #ifdef _WIN32
        _mkdir(sciezka);
    #else 
        mkdir(sciezka, 0777);
    #endif
    FILE *zapis;
    zapis = fopen("data/database_sprzet.bin", "wb");
    if (zapis != NULL)
    {
        while(obecny != NULL)
        {    
            fwrite(obecny, sizeof(Sprzet), 1, zapis);
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

Sprzet *wczytaj_sprzet()
{
    FILE *plik = fopen("data/database_sprzet.bin", "rb");
    Sprzet *head = NULL;
    Sprzet *ostatni = NULL; //dodalem aby moc "obrocic" liste, bo tak to wczyta sie do ramu do gory nogami
    Sprzet temp;

    if (plik != NULL)
    {
        while (fread(&temp, sizeof(Sprzet), 1, plik) == 1)
        {
            Sprzet *nowy = malloc(sizeof(Sprzet));
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

void wyswietlanie_sprzetu(Sprzet *head)
{
    Sprzet *obecny = head;
    while (obecny != NULL)
    {
        // Format: ID/Cena za dzien/liczba egzemplarzy/liczba wypozyczonych/nazwa sprzetu
        printf("%d|%.2f|%d|%d|%s\n", obecny->id_sprzetu, obecny->cena_za_dzien, obecny->liczba_egzemplarzy, obecny->liczba_wypozyczonych, obecny->nazwa_sprzetu);
        obecny = obecny->next;
    }
}

void wyczysc_pamiec_sprzet(Sprzet *head)
{
    Sprzet *obecny = head;
    Sprzet *tmp;
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

void usun_sprzet(Sprzet **h_sprzet)
{
    int szukane_id;
    printf("Podaj ID sprzetu do usuniecia: \n");
    scanf("%d", &szukane_id);

    Sprzet *obecny_sprzet = *h_sprzet;
    Sprzet *poprzedni_sprzet = NULL;

    while (obecny_sprzet != NULL && obecny_sprzet->id_sprzetu != szukane_id)
    {
        poprzedni_sprzet = obecny_sprzet;
        obecny_sprzet = obecny_sprzet->next;
    }
    if (obecny_sprzet == NULL)
    {
        printf("Nie odnaleziono sprzetu!\n");
        return;
    }
    if(obecny_sprzet->liczba_wypozyczonych != 0)
    {
        printf("Nie mozna usunac sprzetu, jest dalej w wypozyczeniu!\n");
        return;
    }
    if (poprzedni_sprzet == NULL)
    {
        *h_sprzet = obecny_sprzet->next;
    }
    else
    {
        poprzedni_sprzet->next = obecny_sprzet->next;
    }
    free(obecny_sprzet);
    printf("Pomyslnie usunieto sprzet z bazy.\n");
    return;
}
