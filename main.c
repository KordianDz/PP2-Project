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
#include "wypozyczenia.h"
#include "funkcje_universalne.h"

int main()
{
    //heady
    Klient *head_klienci = wczytaj_baze_klientow();
    Sprzet *head_sprzet = wczytaj_sprzet();
    Wypozyczenie *head_wypozyczenia = wczytaj_baze_ofert();
    Wypozyczenie *head_archiwum = wczytaj_archiwum();
    ElementStosu *historia_wypozyczen = NULL;
    
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
        printf("6. Usun z bazy danych (Klienci/Sprzet).\n");
        printf("7. Wyszukaj klienta.\n");
        printf("8. Wyszukaj sprzęt.\n");
        printf("9. BEZPIECZNE zamkniecie programu.\n");
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
                                int opcja2_1 = 0;
                                printf("1. Wyświetl w kolejnosci dodania.\n");
                                printf("2. Wyświetl w kolejnosci alfabetycznej po imieniu.\n");
                                printf("3. Wyświetl w kolejnosci alfabetycznej po nazwisku.\n");
                                if (scanf("%d", &opcja2_1) != 1)
                                {
                                    while(getchar() != '\n')
                                    opcja2_1 = -1;
                                }
                                switch(opcja2_1)
                                {
                                    case 1:
                                    {
                                        wyswietlanie_klientow(head_klienci);
                                        break;
                                    }
                                    case 2:
                                    {
                                        wyswietlanie_klientow_alfabetycznie_imie(head_klienci);
                                        break;
                                    }
                                    case 3:
                                    {
                                        wyswietlanie_klientow_alfabetycznie_nazwisko(head_klienci);
                                        break;
                                    }
                                    default:
                                    {
                                        break;
                                    }
                                }
                                break;
                            }
                            case 2:
                            {
                                int opcja2_2 = 0;
                                printf("1. Wyświetl w kolejnosci dodania.\n");
                                printf("2. Wyświetl po ID.\n");
                                printf("3. Wyświetl po nazwie.\n");
                                printf("4. Wyświetl po egzemplarzach.\n");
                                printf("5. Wyświetl po wypozyczonych.\n");
                                if (scanf("%d", &opcja2_2) != 1)
                                {
                                    while(getchar() != '\n')
                                    opcja2_2 = -1;
                                }
                                switch(opcja2_2)
                                {
                                    case 1:
                                    {
                                        wyswietlanie_sprzetu(head_sprzet);
                                        break;
                                    }
                                    case 2:
                                    {
                                        int opcja2_1_1 = 0;
                                        printf("1. Wyświetl w kolejnosci rosnącej.\n");
                                        printf("2. Wyświetl w kolejnosci malejącej.\n");
                                        if (scanf("%d", &opcja2_1_1) != 1)
                                        {
                                            while(getchar() != '\n')
                                            opcja2_1_1 = -1;
                                        }
                                        switch(opcja2_1_1)
                                        {
                                            case 1:
                                            {
                                                wyswietlanie_sprzet_po_id(head_sprzet, 1);
                                                break;
                                            }
                                            case 2:
                                            {
                                                wyswietlanie_sprzet_po_id(head_sprzet, 2);
                                                break;
                                            }
                                            default:
                                            {
                                                break;
                                            }
                                        }
                                        
                                        break;
                                    }
                                    case 3:
                                    {
                                        int opcja2_1_2 = 0;
                                        printf("1. Wyświetl w kolejnosci A-Z.\n");
                                        printf("2. Wyświetl w kolejnosci Z-A.\n");
                                        if (scanf("%d", &opcja2_1_2) != 1)
                                        {
                                            while(getchar() != '\n')
                                            opcja2_1_2 = -1;
                                        }
                                        switch(opcja2_1_2)
                                        {
                                            case 1:
                                            {
                                                wyswietlanie_sprzetu_alfabetycznie(head_sprzet, 1);
                                                break;
                                            }
                                            case 2:
                                            {
                                                wyswietlanie_sprzetu_alfabetycznie(head_sprzet, 2);
                                                break;
                                            }
                                            default:
                                            {
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 4:
                                    {
                                        int opcja2_1_3 = 0;
                                        printf("1. Wyświetl w kolejnosci rosnącej.\n");
                                        printf("2. Wyświetl w kolejnosci malejącej.\n");
                                        if (scanf("%d", &opcja2_1_3) != 1)
                                        {
                                            while(getchar() != '\n')
                                            opcja2_1_3 = -1;
                                        }
                                        switch(opcja2_1_3)
                                        {
                                            case 1:
                                            {
                                                wyswietlanie_sprzet_po_egzemplarzach(head_sprzet, 1);
                                                break;
                                            }
                                            case 2:
                                            {
                                                wyswietlanie_sprzet_po_egzemplarzach(head_sprzet, 2);
                                                break;
                                            }
                                            default:
                                            {
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 5:
                                    {
                                        int opcja2_1_4 = 0;
                                        printf("1. Wyświetl w kolejnosci rosnącej.\n");
                                        printf("2. Wyświetl w kolejnosci malejącej.\n");
                                        if (scanf("%d", &opcja2_1_4) != 1)
                                        {
                                            while(getchar() != '\n')
                                            opcja2_1_4 = -1;
                                        }
                                        switch(opcja2_1_4)
                                        {
                                            case 1:
                                            {
                                                wyswietlanie_sprzet_po_wypozyczonych(head_sprzet, 1);
                                                break;
                                            }
                                            case 2:
                                            {
                                                wyswietlanie_sprzet_po_wypozyczonych(head_sprzet, 2);
                                                break;
                                            }
                                            default:
                                            {
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                    {
                                        break;
                                    }
                                }
                                break;
                            }
                            case 3:
                            {
                                int opcja2_3 = 0;
                                printf("1. Wyświetl w kolejnosci dodania.\n");
                                printf("2. Wyświetl w kolejnosci od najdroższej.\n");
                                printf("3. Wyświetl w kolejnosci od najtańszej.\n");
                                printf("4. Wyswietl 5 ostatnich wypozyczen.\n");
                                if (scanf("%d", &opcja2_3) != 1)
                                {
                                    while(getchar() != '\n')
                                    opcja2_3 = -1;
                                }
                                switch(opcja2_3)
                                {
                                    case 1:
                                    {
                                        wyswietlanie_ofert(head_wypozyczenia);
                                        break;
                                    }
                                    case 2:
                                    {
                                        wyswietlanie_ofert_od_najdrozszej(head_wypozyczenia);
                                        break;
                                    }
                                    case 3:
                                    {
                                        wyswietlanie_ofert_od_najtanszej(head_wypozyczenia);
                                        break;
                                    }
                                    case 4:
                                    {
                                        wyswietl_historie(historia_wypozyczen);
                                        break;
                                    }
                                    default:
                                    {
                                        break;
                                    }
                                }
                                break;
                            }
                            case 4:
                            {
                                int opcja2_4 = 0;
                                printf("1. Wyświetl w kolejnosci dodania.\n");
                                printf("2. Wyświetl w kolejnosci od najdroższej.\n");
                                printf("3. Wyświetl w kolejnosci od najtańszej.\n");
                                if (scanf("%d", &opcja2_4) != 1)
                                {
                                    while(getchar() != '\n')
                                    opcja2_4 = -1;
                                }
                                switch(opcja2_4)
                                {
                                    case 1:
                                    {
                                        wyswietlanie_ofert(head_archiwum);
                                        break;
                                    }
                                    case 2:
                                    {
                                        wyswietlanie_ofert_od_najdrozszej(head_archiwum);
                                        break;
                                    }
                                    case 3:
                                    {
                                        wyswietlanie_ofert_od_najtanszej(head_archiwum);
                                        break;
                                    }
                                    default:
                                    {
                                        break;
                                    }
                                }
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
                    Wypozyczenie *stary_head = head_wypozyczenia;
                    dodaj_wypozyczenie(&head_klienci, &head_sprzet, &head_wypozyczenia);
                    if (head_wypozyczenia != stary_head)
                    {
                        push(&historia_wypozyczen, *head_wypozyczenia);
                    }
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
                    int opcja_usun = 0;
                    printf("Wybierz, co chcesz usunac: \n");
                    printf("1. Usun klienta.\n");
                    printf("2. Usun sprzet.\n");
                    printf("3. Powrot.\n");

                    if (scanf("%d", &opcja_usun) != 1)
                    {
                        while(getchar() != '\n');
                        opcja_usun = -1;
                    }
                    else 
                    {
                        switch(opcja_usun)
                        {
                            case 1:
                            {
                                printf("Wybrano usuwanie klienta. \n");
                                Usun_klienta(&head_klienci, head_wypozyczenia);
                                break;
                            }
                            case 2:
                            {
                                printf("Wybrano usuwanie sprzetu. \n");
                                usun_sprzet(&head_sprzet);
                                break;
                            }
                            case 3:
                            {
                                printf("Powrot do glownego menu.\n");
                                break;
                            }
                            default:
                            {
                                printf("Niepoprawna opcja!\n");
                                break;
                            }
                        }
                    }
                    break;
                }
                case 7:
                {
                    printf("Wybierz po czym chcesz wyszukać klienta: \n");
                    printf("1. Po numerze karty klienta. \n");
                    printf("2. Po danych klienta. \n");
                    int opcja3 = 0;
                    if (scanf("%d", &opcja3) != 1)
                    {
                        while(getchar() != '\n');
                        opcja3 = -1;
                    }
                    else
                    {
                        switch(opcja3)
                        {
                            case 1:
                            {
                                wyszukaj_klienta(head_klienci);
                                break;
                            }   
                            case 2:
                            {
                                wyszukaj_klienta_imie_nazwisko(head_klienci);
                                break;
                            }
                            default:
                            {
                                printf("Niepoprawna opcja!\n");
                                break;
                            }
                        }
                    }
                    break;
                }
                case 8:
                {
                    printf("Wybierz po czym chcesz wyszukać sprzęt: \n");
                    printf("1. Po ID sprzętu. \n");
                    printf("2. Po nazwie sprzętu. \n");
                    int opcja4 = 0;
                    if (scanf("%d", &opcja4) != 1)
                    {
                        while(getchar() != '\n');
                        opcja4 = -1;
                    }
                    else
                    {
                        switch(opcja4)
                        {
                            case 1:
                            {
                                wyszukaj_sprzet(head_sprzet);
                                break;
                            }
                            case 2:
                            {
                                wyszukaj_sprzet_nazwa(head_sprzet);
                                break;
                            }
                            default:
                            {
                                printf("Niepoprawna opcja!\n");
                                break;
                            }
                        }
                    }
                    break;
                }
                case 9:
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
//wyswietlanie 5 ostatnich z historii
//szyfrowanie, podzial funkcji na inne pliki
//bugfix zmienna przyjmuje tylko liczby, a liter/znaku nie
//bugfix usuwanie sprzetu po zamknieciu kontraktu z data wczesniejsza niz wypozyczenie

//%%%% JUZ ZROBIONE %%%%%%%%%%%%%%%%
//sortowanie
//wyszukiwanie
//naprawic buffer overflow to dzisiaj
//dodalem usuwanie klientow/sprzetu
//dodalem modularnosc plikow
//menu ma wszystkie wymienione wczesniej funkcje 
