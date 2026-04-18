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
//dodalem modularnosc plikow