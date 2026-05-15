#include "sprzet.h"
#include "funkcje_universalne.h"
#include <string.h>

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

void wyswietlanie_sprzet_po_id(Sprzet *head, int kierunek) 
{
    if(head == NULL || head->next == NULL)
    {
        return;
    }

    Sprzet *obecny = head;
    Sprzet *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {

            bool warunek_zamiany = false;

            if (kierunek == 1 && obecny->id_sprzetu > nastepny->id_sprzetu) 
            {
                warunek_zamiany = true; // zamieniamy zeby wiekszy byl pozniej
            }
            else if (kierunek == 2 && obecny->id_sprzetu < nastepny->id_sprzetu) 
            {
                warunek_zamiany = true; // zamieniamy zeby mniejszy byl pozniej
            }

            if(warunek_zamiany == true)
            {
                Sprzet *oryginal_obecny_next = obecny->next;
                Sprzet *oryginal_nastepny_next = nastepny->next;

                Sprzet temp = *obecny;
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
        printf("%d|%.2f|%d|%d|%s\n", obecny->id_sprzetu, obecny->cena_za_dzien, obecny->liczba_egzemplarzy, obecny->liczba_wypozyczonych, obecny->nazwa_sprzetu);
        obecny = obecny->next;
    }
}

void wyswietlanie_sprzetu_alfabetycznie(Sprzet *head, int kierunek)
{
    if(head == NULL || head->next == NULL)
        {
            return;
        }


    Sprzet *obecny = head;
    Sprzet *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {

            bool warunek_zamiany = false;

            if (kierunek == 1 && porownaj_male_litery(obecny->nazwa_sprzetu, nastepny->nazwa_sprzetu) > 0) 
            {
                warunek_zamiany = true; // zamieniamy aby wyswietlał alfabetycznie
            }
            else if (kierunek == 2 && porownaj_male_litery(obecny->nazwa_sprzetu, nastepny->nazwa_sprzetu) < 0) 
            {
                warunek_zamiany = true; // zamieniamy aby wyswietlal od tylu alfabetu
            }
            //

                if(warunek_zamiany == true)
            {
                Sprzet *oryginal_obecny_next = obecny->next;
                Sprzet *oryginal_nastepny_next = nastepny->next;

                Sprzet temp = *obecny;
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
    printf("%d|%.2f|%d|%d|%s\n", obecny->id_sprzetu, obecny->cena_za_dzien, obecny->liczba_egzemplarzy, obecny->liczba_wypozyczonych, obecny->nazwa_sprzetu);
    obecny = obecny->next;
    }
}

void wyswietlanie_sprzet_po_egzemplarzach(Sprzet *head, int kierunek) 
{
    if(head == NULL || head->next == NULL)
    {
        return;
    }

    Sprzet *obecny = head;
    Sprzet *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {

            bool warunek_zamiany = false;

            if (kierunek == 1 && obecny->liczba_egzemplarzy > nastepny->liczba_egzemplarzy) 
            {
                warunek_zamiany = true; // zamieniamy zeby wiekszy byl pozniej
            }
            else if (kierunek == 2 && obecny->liczba_egzemplarzy < nastepny->liczba_egzemplarzy) 
            {
                warunek_zamiany = true; // zamieniamy zeby mniejszy byl pozniej
            }

            if(warunek_zamiany == true)
            {
                Sprzet *oryginal_obecny_next = obecny->next;
                Sprzet *oryginal_nastepny_next = nastepny->next;

                Sprzet temp = *obecny;
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
        printf("%d|%.2f|%d|%d|%s\n", obecny->id_sprzetu, obecny->cena_za_dzien, obecny->liczba_egzemplarzy, obecny->liczba_wypozyczonych, obecny->nazwa_sprzetu);
        obecny = obecny->next;
    }
}

void wyswietlanie_sprzet_po_wypozyczonych(Sprzet *head, int kierunek) 
{
    if(head == NULL || head->next == NULL)
    {
        return;
    }

    Sprzet *obecny = head;
    Sprzet *nastepny = obecny->next;
    bool zamieniono = false;

    do
    {
        zamieniono = false;
        obecny = head;
        nastepny = obecny->next;

        while(nastepny != NULL)
        {

            bool warunek_zamiany = false;

            if (kierunek == 1 && obecny->liczba_wypozyczonych > nastepny->liczba_wypozyczonych) 
            {
                warunek_zamiany = true; // zamieniamy zeby wiekszy byl pozniej
            }
            else if (kierunek == 2 && obecny->liczba_wypozyczonych < nastepny->liczba_wypozyczonych) 
            {
                warunek_zamiany = true; // zamieniamy zeby mniejszy byl pozniej
            }

            if(warunek_zamiany == true)
            {
                Sprzet *oryginal_obecny_next = obecny->next;
                Sprzet *oryginal_nastepny_next = nastepny->next;

                Sprzet temp = *obecny;
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
    getchar();
    fgets(nowy_sprzet->nazwa_sprzetu, 30, stdin);
    nowy_sprzet->nazwa_sprzetu[strlen(nowy_sprzet->nazwa_sprzetu) - 1] = '\0';

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

void wyszukaj_sprzet(Sprzet *head)
{
    int szukaj_po_id;
    Sprzet *szukany = head;

    printf("Podaj id szukanego sprzętu.\n");
    scanf(" %d", &szukaj_po_id);

    while(szukany != NULL && szukaj_po_id != szukany->id_sprzetu)
    {
        szukany = szukany->next;
    }
    if(szukany == NULL)
    {
        printf("Nie znaleziono takiego sprzętu!");
    }
    else
    {
        printf("%d|%s|%ld|%d|%d\n", szukany->id_sprzetu, szukany->nazwa_sprzetu, szukany->cena_za_dzien, szukany->liczba_egzemplarzy, szukany->liczba_wypozyczonych);
    }
}

void wyszukaj_sprzet_nazwa(Sprzet *head)
{
    char temp_nazwa[30];
    Sprzet *obecny = head;
    bool znaleziono = false;

    printf("Podaj nazwe sprzętu którego szukasz.\n");
    scanf("%29s", temp_nazwa);

    while(obecny != NULL)
    {

         if(strcmp(obecny->nazwa_sprzetu, temp_nazwa) == 0)
         {
           printf("%d|%s|%ld|%d|%d\n", obecny->id_sprzetu, obecny->nazwa_sprzetu, obecny->cena_za_dzien, obecny->liczba_egzemplarzy, obecny->liczba_wypozyczonych);
           znaleziono = true;
         }
         obecny = obecny->next;

    }
    if(znaleziono == false)
    {
        printf("Nie znaleziono sprzętu w bazie danych.\n");
    }

}