#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define FPS      60.0

int main(int argc, char **argv) {
    if (!al_init()) {
        fprintf(stderr, "Allegro baslatılamadı!\n");
        return 1;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Primitives yuklenemedi!\n");
        return 1;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Mouse yuklenemedi!\n");
        return 1;
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "Klavye yuklenemedi!\n");
        return 1;
    }

    ALLEGRO_DISPLAY     *display = al_create_display(SCREEN_W, SCREEN_H);
    ALLEGRO_EVENT_QUEUE *queue   = al_create_event_queue();
    ALLEGRO_TIMER       *timer   = al_create_timer(1.0 / FPS);

    if (!display || !queue || !timer) {
        fprintf(stderr, "Pencere/queue/timer olusturulamadı!\n");
        return 1;
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_set_window_title(display, "Memory Card - Elif Senturk");
    al_start_timer(timer);

    bool running   = true;
    bool need_draw = true;

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            need_draw = true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                running = false;
        }

        if (need_draw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(30, 30, 46));
            ALLEGRO_FONT *font = al_create_builtin_font();
            al_draw_text(font, al_map_rgb(255, 255, 255),
                         SCREEN_W / 2, SCREEN_H / 2,
                         ALLEGRO_ALIGN_CENTRE,
                         "Memory Card - Hazir!");
            al_destroy_font(font);
            al_flip_display();
            need_draw = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
