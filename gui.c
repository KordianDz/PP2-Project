#include "gui.h"
#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

int uruchom_interfejs() {

    if (al_init() == false) {
        printf("KATASTROFA! Allegro nie dziala.\n");
        return -1; // -1 oznacza błąd
    }


    ALLEGRO_DISPLAY *moje_okno = al_create_display(800, 600);

    if (moje_okno == NULL) {
        printf("KATASTROFA! Nie udalo sie zrobic okna.\n");
        return -1;
    }

    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *kolejka = al_create_event_queue();

    al_register_event_source(kolejka, al_get_mouse_event_source());
    al_register_event_source(kolejka, al_get_display_event_source(moje_okno));
    al_register_event_source(kolejka, al_get_keyboard_event_source());

    bool aplikacja_dziala = true;

    ALLEGRO_FONT *czcionka = al_create_builtin_font();

    char wpisany_tekst[100] = "";
    int dlugosc_tekstu = 0;
    enum StanAplikacji obecny_stan = MENU_GLOWNE;
    while (aplikacja_dziala) {


        ALLEGRO_EVENT event;
        al_wait_for_event(kolejka, &event);


        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            aplikacja_dziala = false; // Przerwij pętlę
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {


            printf("Kliknieto myszka! X: %d, Y: %d\n", event.mouse.x, event.mouse.y);

            if (event.mouse.x > 300 && event.mouse.x < 500 && event.mouse.y > 250 && event.mouse.y < 350 && obecny_stan == MENU_GLOWNE) {
                obecny_stan = MENU_BAZY;
            }
            else if (event.mouse.x > 700 && event.mouse.x < 790 && event.mouse.y > 10 && event.mouse.y < 50 && obecny_stan == MENU_BAZY) {
                obecny_stan = MENU_GLOWNE;
            }else if (event.mouse.x > 300 && event.mouse.x < 500 && event.mouse.y > 400 && event.mouse.y < 500 && obecny_stan == MENU_GLOWNE) {
                obecny_stan = MENU_DODAWANIA;
            }else if (event.mouse.x > 700 && event.mouse.x < 790 && event.mouse.y > 10 && event.mouse.y < 50 && obecny_stan == MENU_DODAWANIA) {
                obecny_stan = MENU_GLOWNE;
            }

        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            aplikacja_dziala = false; // Przerwij pętlę
        } else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (obecny_stan == MENU_DODAWANIA) {
                if (event.keyboard.unichar >= 32 && event.keyboard.unichar <= 126) {
                    if (dlugosc_tekstu< 99) {
                        wpisany_tekst[dlugosc_tekstu] =  event.keyboard.unichar ;
                        dlugosc_tekstu++;
                        wpisany_tekst[dlugosc_tekstu] = '\0';
                        printf("%s\n", wpisany_tekst);
                    }
                }
            }
        }

       // al_clear_to_color(al_map_rgb(255, 192, 203));
        //al_draw_filled_rectangle(300, 250, 500, 350, al_map_rgb(255, 255, 255));

        if (obecny_stan == MENU_GLOWNE) {
            al_clear_to_color(al_map_rgb(255, 192, 100));
            //przycisk 1: bazadanych
            al_draw_filled_rectangle(300, 250, 500, 350, al_map_rgb(255, 255, 255));
            al_draw_text(czcionka, al_map_rgb(0, 0, 0), 400, 295, ALLEGRO_ALIGN_CENTER, "BAZA DANYCH");
            //przycisk 2: dodawanie klienta
            al_draw_filled_rectangle(300, 400, 500, 500, al_map_rgb(255, 255, 255));
            al_draw_text(czcionka, al_map_rgb(0, 0, 0), 400, 445, ALLEGRO_ALIGN_CENTER, "DODAJ KLIENTA");
        }
        else if (obecny_stan == MENU_BAZY) {
            al_clear_to_color(al_map_rgb(0, 0, 255)); // Niebieskie tło bazy
            al_draw_filled_rectangle(700, 10, 790, 50, al_map_rgb(255, 0, 0));
            al_draw_text(czcionka, al_map_rgb(0,0,0), 745, 25, ALLEGRO_ALIGN_CENTER, "POWROT");
        } else if (obecny_stan == MENU_DODAWANIA) {
            al_clear_to_color(al_map_rgb(255, 192, 203));
            al_draw_text(czcionka, al_map_rgb(0,0,0), 400,295, ALLEGRO_ALIGN_CENTER, wpisany_tekst);
            al_draw_filled_rectangle(700, 10, 790, 50, al_map_rgb(255, 0, 0));
            al_draw_text(czcionka, al_map_rgb(0,0,0), 745, 25, ALLEGRO_ALIGN_CENTER, "POWROT");
        }

        al_flip_display();
    }

    al_destroy_event_queue(kolejka);


    al_destroy_display(moje_okno);
    al_destroy_font(czcionka);
    return 0;
}