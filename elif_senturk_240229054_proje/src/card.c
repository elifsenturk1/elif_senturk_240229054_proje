#include "card.h"
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <time.h>

/* Kartları 1D diziye al, karıştır, geri koy (Fisher-Yates) */
void card_shuffle(Card grid[GRID_ROWS][GRID_COLS]) {
    /* 2D grid'i 1D diziye çevir */
    Card flat[TOTAL_CARDS];
    int  k = 0;
    for (int r = 0; r < GRID_ROWS; r++)
        for (int c = 0; c < GRID_COLS; c++)
            flat[k++] = grid[r][c];

    /* Fisher-Yates karıştırma algoritması */
    srand((unsigned int)time(NULL));
    for (int i = TOTAL_CARDS - 1; i > 0; i--) {
        int j    = rand() % (i + 1);
        Card tmp = flat[i];
        flat[i]  = flat[j];
        flat[j]  = tmp;
    }

    /* 1D diziyi tekrar 2D grid'e yaz */
    k = 0;
    for (int r = 0; r < GRID_ROWS; r++)
        for (int c = 0; c < GRID_COLS; c++)
            grid[r][c] = flat[k++];
}

/* Grid'i başlat: her değerden 2 tane, konumları hesapla */
void card_init_grid(Card grid[GRID_ROWS][GRID_COLS]) {
    /* Gridi ekrana ortala */
    float total_w = GRID_COLS * CARD_W + (GRID_COLS - 1) * CARD_MARGIN;
    float total_h = GRID_ROWS * CARD_H + (GRID_ROWS - 1) * CARD_MARGIN;
    float start_x = (800.0f - total_w) / 2.0f;
    float start_y = (600.0f - total_h) / 2.0f;

    /* Önce değerleri ata */
    int values[TOTAL_CARDS];
    for (int i = 0; i < TOTAL_CARDS / 2; i++) {
        values[i * 2]     = i + 1;
        values[i * 2 + 1] = i + 1;
    }

    /* Grid'e yerleştir */
    int k = 0;
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            grid[r][c].value  = values[k++];
            grid[r][c].state  = CARD_FACE_DOWN;
            grid[r][c].width  = CARD_W;
            grid[r][c].height = CARD_H;
            grid[r][c].x = start_x + c * (CARD_W + CARD_MARGIN);
            grid[r][c].y = start_y + r * (CARD_H + CARD_MARGIN);
        }
    }

    /* Karıştır */
    card_shuffle(grid);
}

/* Kartı çiz */
void card_draw(const Card *card) {
    ALLEGRO_COLOR bg, text_color;

    if (card->state == CARD_FACE_DOWN) {
        /* Kapalı kart: mavi */
        bg = al_map_rgb(70, 130, 180);
    } else if (card->state == CARD_FACE_UP) {
        /* Açık kart: beyaz */
        bg = al_map_rgb(240, 240, 240);
    } else {
        /* Eşleşti: yeşil */
        bg = al_map_rgb(100, 200, 120);
    }

    text_color = al_map_rgb(30, 30, 46);

    /* Kart arka planı */
    al_draw_filled_rounded_rectangle(
        card->x, card->y,
        card->x + card->width, card->y + card->height,
        10, 10, bg);

    /* Kart çerçevesi */
    al_draw_rounded_rectangle(
        card->x, card->y,
        card->x + card->width, card->y + card->height,
        10, 10, al_map_rgb(30, 30, 46), 2.0f);

    /* Açıksa veya eşleştiyse değeri göster */
    if (card->state != CARD_FACE_DOWN) {
        ALLEGRO_FONT *font = al_create_builtin_font();
        char buf[4];
        sprintf(buf, "%d", card->value);
        al_draw_text(font, text_color,
                     card->x + card->width  / 2,
                     card->y + card->height / 2 - 4,
                     ALLEGRO_ALIGN_CENTRE, buf);
        al_destroy_font(font);
    }
}

/* Mouse tıklaması kart üzerinde mi? */
bool card_is_clicked(const Card *card, int mouse_x, int mouse_y) {
    return mouse_x >= card->x && mouse_x <= card->x + card->width &&
           mouse_y >= card->y && mouse_y <= card->y + card->height;
}