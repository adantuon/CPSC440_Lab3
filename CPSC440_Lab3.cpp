#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5//allegro_primitives.h>
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

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_register_event_source(EventQueue, al_get_display_event_source(display));

    if (!al_install_mouse()) {
        fprintf(stderr, "Mouse Initialization failed\n");
        return(-1);
    }

    al_register_event_source(EventQueue, al_get_mouse_event_source());

    bool exit = false;
    bool draw = false;
    bool firstLoop = true;
    int x = 400;
    int y = 300;

    //Color Palette
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR bg = black;
    ALLEGRO_COLOR fg = white;

    //Fonts
    ALLEGRO_FONT *CourierNew_pt24 = al_load_font("cour.ttf", 24, 0);
    ALLEGRO_FONT *BroadwayRegular_pt24 = al_load_font("BROADW.TTF", 24, 0);
    ALLEGRO_FONT *CenturyGothic_pt24 = al_load_font("GOTHIC.TTF", 24, 0);
    ALLEGRO_FONT *OnyxRegular_pt24 = al_load_font("ONYX.TTF", 24, 0);
    ALLEGRO_FONT *font;

    while (!exit) {

        //Draws object at center of screen at start of program
        if (firstLoop) {
            al_clear_to_color(bg);

            al_draw_filled_circle(x, y, 5, fg);

            al_flip_display();

            firstLoop = false;
        }
        al_wait_for_event(EventQueue, &Event);

        if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        else if (Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Event.mouse.button & 1) {
                draw = true;
                x = Event.mouse.x;
                y = Event.mouse.y;
            }
        }

        if (draw) {
            if (x < 400) {
                if (y < 300) {
                    bg = white;
                    fg = black;
                    font = CourierNew_pt24;
                }
                else {
                    bg = blue;
                    fg = yellow;
                    font = BroadwayRegular_pt24;
                }
            }
            else {
                if (y < 300) {
                    bg = black;
                    fg = white;
                    font = CenturyGothic_pt24;
                }
                else {
                    bg = yellow;
                    fg = blue;
                    font = OnyxRegular_pt24;
                }
            }
            al_clear_to_color(bg);

            al_draw_filled_circle(x, y, 5, fg);
            al_draw_textf(font, fg, x, y, ALLEGRO_ALIGN_LEFT, "Coords: (%i, %i)", x, y);

            al_flip_display();

            draw = false;
        }

    }

    al_destroy_display(display);

    return 0;
}
