//sprawdzanie obecnego OS
#ifdef _WIN32
    #include <direct.h> // library dla Windows
#else
    #include <sys/stat.h> // library dla Linux/Mac
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "daty.h"
#include "sprzet.h"
#include "klienci.h"

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


//wyswietlanie klientow z RAMu


void wyswietlanie_ofert(Wypozyczenie *head)
{
    Wypozyczenie *obecny = head;
    while (obecny != NULL)
    {
        // Format: data wypozyczenia/id sprzetu/numer karty/ oplacona kwota/przewidywana data oddania/realna data oddania
        printf("%02d.%02d.%d|%d|%d|%.2f|%02d.%02d.%d|%02d.%02d.%d\n", obecny->data_wypozyczenia.dzien, obecny->data_wypozyczenia.miesiac, obecny->data_wypozyczenia.rok, obecny->id_sprzetu, obecny->numer_karty, obecny->oplacona_kwota, obecny->przewidywana_data_oddania.dzien, obecny->przewidywana_data_oddania.miesiac, obecny->przewidywana_data_oddania.rok, obecny->realna_data_oddania.dzien, obecny->realna_data_oddania.miesiac, obecny->realna_data_oddania.rok);
        obecny = obecny->next;
    }
}


//zapis w pliku bazy danych klientow


//zapis w pliku archiwum poprzednich ofert(zakonczonych)
bool zapis_archiwum(Wypozyczenie *head_archiwum)
{
    const char *sciezka = "data";
    Wypozyczenie *obecne = head_archiwum;
    #ifdef _WIN32
        _mkdir(sciezka);
    #else 
        mkdir(sciezka, 0777);
    #endif
    FILE *zapis;
    zapis = fopen("data/database_archive.bin", "wb");
    if (zapis != NULL)
    {
        while(obecne != NULL)
        {    
            fwrite(obecne, sizeof(Wypozyczenie), 1, zapis);
            obecne = obecne->next;
        }
        fclose(zapis);
        return true;
    }
    else
    {
        return false;
    }
}

//zapis w pliku bazy danych aktywnych ofert
bool zapis_oferty(Wypozyczenie *head_wypozyczenia)
{
    const char *sciezka = "data";
    Wypozyczenie *obecny = head_wypozyczenia;
    #ifdef _WIN32
        _mkdir(sciezka);
    #else 
        mkdir(sciezka, 0777);
    #endif
    FILE *zapis;
    zapis = fopen("data/database_offers.bin", "wb");
    if (zapis != NULL)
    {
        while(obecny != NULL)
        {    
            fwrite(obecny, sizeof(Wypozyczenie), 1, zapis);
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

//zapis w pliku bazy danych sprzetu


//wczytywanie bazy danych klientow z pliku do RAM


//wczytywanie bazy danych offert z pliku do RAM
Wypozyczenie *wczytaj_baze_ofert()
{
    FILE *plik = fopen("data/database_offers.bin", "rb");
    Wypozyczenie *head = NULL;
    Wypozyczenie *ostatni = NULL; //dodalem aby moc "obrocic" liste, bo tak to wczyta sie do ramu do gory nogami
    Wypozyczenie temp;

    if (plik != NULL)
    {
        while (fread(&temp, sizeof(Wypozyczenie), 1, plik) == 1)
        {
            Wypozyczenie *nowy = malloc(sizeof(Wypozyczenie));
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

//wczytywanie bazy danych archiwum z pliku archiwum do RAM
Wypozyczenie *wczytaj_archiwum()
{
    FILE *plik = fopen("data/database_archive.bin", "rb");
    Wypozyczenie *head = NULL;
    Wypozyczenie *ostatni = NULL; //dodalem aby moc "obrocic" liste, bo tak to wczyta sie do ramu do gory nogami
    Wypozyczenie temp;

    if (plik != NULL)
    {
        while (fread(&temp, sizeof(Wypozyczenie), 1, plik) == 1)
        {
            Wypozyczenie *nowy = malloc(sizeof(Wypozyczenie));
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

//wzczytywanie bazy danych sprzetu z pliku do RAMu



void dodaj_wypozyczenie(Klient **h_klienci, Sprzet **h_sprzet, Wypozyczenie **h_wypozyczenie)
{
    int szukana_karta, szukany_sprzet;
    printf("Podaj numer karty klienta.\n");
    scanf("%d", &szukana_karta);
    printf("Podaj ID sprzetu do wypozyczenia.\n");
    scanf("%d", &szukany_sprzet);
    

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
    printf("Podaj dzien wypozyczenia.\n");
    scanf("%d", &nowe_wypozyczenie->data_wypozyczenia.dzien);
    printf("Podaj miesiac wypozyczenia.\n");
    scanf("%d", &nowe_wypozyczenie->data_wypozyczenia.miesiac);
    printf("Podaj rok wypozyczenia.\n");
    scanf("%d", &nowe_wypozyczenie->data_wypozyczenia.rok);

    printf("Podaj umowny dzien oddania.\n");
    scanf("%d", &nowe_wypozyczenie->przewidywana_data_oddania.dzien);
    printf("Podaj umowny miesiac oddania.\n");
    scanf("%d", &nowe_wypozyczenie->przewidywana_data_oddania.miesiac);
    printf("Podaj umowny rok oddania.\n");
    scanf("%d", &nowe_wypozyczenie->przewidywana_data_oddania.rok);

    nowe_wypozyczenie->realna_data_oddania.dzien = 0;
    nowe_wypozyczenie->realna_data_oddania.miesiac = 0;
    nowe_wypozyczenie->realna_data_oddania.rok = 0;
    printf("Uwaga! 'realna data oddania' jest automatycznie ustawiana na 0. Nalezy ja edytowac po oddaniu przez klienta sprzetu z powrotem do sklepu. Kara za spoznienie bedzie naliczana pozniej.\n ");

    int dni_wypozyczenia = (oblicz_dni_od_zera(nowe_wypozyczenie->przewidywana_data_oddania) - oblicz_dni_od_zera(nowe_wypozyczenie->data_wypozyczenia));
    nowe_wypozyczenie->oplacona_kwota = dni_wypozyczenia * obecny_sprzet->cena_za_dzien;
    nowe_wypozyczenie -> numer_karty = szukana_karta;
    nowe_wypozyczenie -> id_sprzetu = szukany_sprzet;
    obecny_sprzet -> liczba_wypozyczonych ++;
    nowe_wypozyczenie -> next = *h_wypozyczenie;
    *h_wypozyczenie = nowe_wypozyczenie;
}

void zwroc_sprzet(Klient **hz_klienci, Sprzet **hz_sprzet, Wypozyczenie **hz_wypozyczenie, Wypozyczenie **hz_archiwum)
{
    int szukana_karta, szukany_sprzet;
    printf("Podaj numer karty.\n");
    scanf("%d", &szukana_karta);
    printf("Podaj ID sprzetu.\n");
    scanf("%d", &szukany_sprzet);
    Wypozyczenie *zwrot_obecne_wypozyczenie = *hz_wypozyczenie;
    Sprzet *zwrot_sprzet = *hz_sprzet;
    Wypozyczenie *poprzednie_wypozyczenie = NULL;
    while (zwrot_obecne_wypozyczenie != NULL && (szukana_karta != zwrot_obecne_wypozyczenie->numer_karty || szukany_sprzet != zwrot_obecne_wypozyczenie->id_sprzetu))
    {
        poprzednie_wypozyczenie = zwrot_obecne_wypozyczenie; 
        zwrot_obecne_wypozyczenie = zwrot_obecne_wypozyczenie->next;
    }
    if (zwrot_obecne_wypozyczenie == NULL)
    {
        printf("Umowa o podanych parametrach nie istnieje!\n");
        return;
    }
    if (poprzednie_wypozyczenie == NULL)
    {
        *hz_wypozyczenie = zwrot_obecne_wypozyczenie->next;
    }
    else
    {
        poprzednie_wypozyczenie->next = zwrot_obecne_wypozyczenie->next;
    }
    while (zwrot_sprzet != NULL && szukany_sprzet != zwrot_sprzet->id_sprzetu)
    {
        zwrot_sprzet = zwrot_sprzet->next;
    }
    if (zwrot_sprzet == NULL)
    {
        printf("Blad bazy sprzetu!");
        return;
    }
    zwrot_obecne_wypozyczenie -> next = *hz_archiwum;
    *hz_archiwum = zwrot_obecne_wypozyczenie;

    printf("Kiedy nastapilo oddanie sprzetu? (dzien)");
    scanf("%d", &zwrot_obecne_wypozyczenie->realna_data_oddania.dzien);
    printf("Kiedy nastapilo oddanie sprzetu? (miesiac)");
    scanf("%d", &zwrot_obecne_wypozyczenie->realna_data_oddania.miesiac);
    printf("Kiedy nastapilo oddanie sprzetu? (rok)");
    scanf("%d", &zwrot_obecne_wypozyczenie->realna_data_oddania.rok);

    int dni_spoznienia = oblicz_dni_od_zera(zwrot_obecne_wypozyczenie->realna_data_oddania) - oblicz_dni_od_zera(zwrot_obecne_wypozyczenie->przewidywana_data_oddania);
    double cena_dzienna_opoznienie = zwrot_sprzet->cena_za_dzien;
    double kara_opoznienie = dni_spoznienia*cena_dzienna_opoznienie*0.2;
    if (dni_spoznienia <= 0)
    {
        kara_opoznienie = 0;
        printf("Brak kary za opoznienie. Sprzet oddany na czas.\n");
    }
    else
    {
        printf("Kara za opoznienia wynosi %.2f: \n", kara_opoznienie);
    }
    zwrot_sprzet->liczba_wypozyczonych--;
    return;
}
// czyszczenie pamieci ram
void wyczysc_pamiec_archiwum(Wypozyczenie *head)
{
    Wypozyczenie *obecny = head;
    Wypozyczenie *tmp;
    while (obecny != NULL)
    {
        tmp = obecny -> next;
        free(obecny);
        obecny = tmp;
    }
}

void wyczysc_pamiec_oferty(Wypozyczenie *head)
{
    Wypozyczenie *obecny = head;
    Wypozyczenie *tmp;
    while (obecny != NULL)
    {
        tmp = obecny -> next;
        free(obecny);
        obecny = tmp;
    }
}
///////////////////usuwanie



int main()
{
    //heady
    Klient *head_klienci = wczytaj_baze_klientow();
    Sprzet *head_sprzet = wczytaj_sprzet();
    Wypozyczenie *head_wypozyczenia = wczytaj_baze_ofert();
    Wypozyczenie *head_archiwum = wczytaj_archiwum();
    
    //main sys 
    while(1)
    {
        int opcja = 0;
        printf("Witamy. Wybierz opcje do administracji systemu wypozyczania nart.\n");
        printf("1. Wyswietl baze danych.\n");
        printf("2. Dodaj klienta.\n");
        printf("3. Dodaj sprzet do inwentarza.\n");
        printf("4. Podpisz nowy kontrakt.\n");
        printf("5. Zwrot sprzetu (oddanie).\n");
        printf("6. BEZPIECZNE zamkniecie programu.\n");
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
                    int opcja2 = 0;
                    printf("Submenu. Wybierz ktora baze danych wyswietlic: \n");
                    printf("1. Baza danych - Klienci. \n");
                    printf("2. Baza danych - Sprzet. \n");
                    printf("3. Baza danych - Kontrakty. \n");
                    printf("4. Baza danych - Archiwum. \n");
                    printf("5. Powrot. \n");
                    if (scanf("%d", &opcja2) != 1)
                    {
                        while(getchar() != '\n');
                        opcja2 = -1;
                    }
                    else
                    {
                        switch (opcja2)
                        {
                            case 1:
                            {
                                printf("Wyswietlam baze danych - Klienci\n");
                                wyswietlanie_klientow(head_klienci);
                                break;
                            }
                            case 2:
                            {
                                printf("Wyswietlam baze danych - Sprzet\n");
                                wyswietlanie_sprzetu(head_sprzet);
                                break;
                            }
                            case 3:
                            {
                                printf("Wyswietlam baze danych - Oferty\n");
                                wyswietlanie_ofert(head_wypozyczenia);
                                break;
                            }
                            case 4:
                            {
                                printf("Wyswietlam archiwum\n");
                                wyswietlanie_ofert(head_archiwum);
                                break;
                            }
                        }
                    }
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
                    printf("Dodawanie sprzetu do inwentarza.\n");
                    head_sprzet = dodaj_sprzet(head_sprzet);
                    break;
                }
                case 4:
                {
                    printf("Podpisanie kontraktu (wypozyczenie sprzetu np. nart)\n");
                    dodaj_wypozyczenie(&head_klienci, &head_sprzet, &head_wypozyczenia);
                    break;
                }
                case 5:
                {
                    printf("Zwrot sprzetu(+ew naliczenie kary)\n");
                    zwroc_sprzet(&head_klienci, &head_sprzet, &head_wypozyczenia, &head_archiwum);
                    break;
                }
                case 6:
                {
                    printf("Zamykanie... Zaczekaj do konca aby uniknac utraty danych!\n");
                    zapis_sprzet(head_sprzet);
                    zapis_archiwum(head_archiwum);
                    zapis_klienci(head_klienci);
                    zapis_oferty(head_wypozyczenia);
                    wyczysc_pamiec_archiwum(head_archiwum);
                    wyczysc_pamiec_klient(head_klienci);
                    wyczysc_pamiec_oferty(head_wypozyczenia);
                    wyczysc_pamiec_sprzet(head_sprzet);
                    printf("Bezpiecznie zapisano i zamknieto program.\n");
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

//%%%%%%%%%%%%%%%%%% TO DO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//dodac sortowanie, wyszukiwanie, wyswietlanie 5 ostatnich z historii
//szyfrowanie, podzial funkcji na inne pliki
//naprawic buffer overflow


//dodalem usuwanie klientow/sprzetu