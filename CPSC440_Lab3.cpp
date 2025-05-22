#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5//allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

int main()
{
    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init()) {
        fprintf(stderr, "Allegro Initialization Failed\n");
        return(-1);
    }

    display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Display Creation Failed\n");
        return(-1);
    }

    ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
    ALLEGRO_EVENT Event;

    EventQueue = al_create_event_queue();
    if (!EventQueue) {
        fprintf(stderr, "Event Queue Creation Failed\n");
        return(-1);
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Event Queue Creation Failed\n");
        return(-1);
    }

    //Get events from keyboard
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    al_init_primitives_addon();
    al_register_event_source(EventQueue, al_get_display_event_source(display));

    bool exit = false;
    int x = 400;
    int y = 300;

    while (!exit) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_flip_display();

        al_wait_for_event(EventQueue, &Event);

        if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
    }

    al_destroy_display(display);

    return 0;
}
