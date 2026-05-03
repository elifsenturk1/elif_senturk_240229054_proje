#ifndef CARD_H
#define CARD_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

/* --- Kart durumları --- */
typedef enum {
    CARD_FACE_DOWN,   /* kapalı */
    CARD_FACE_UP,     /* açık   */
    CARD_MATCHED      /* eşleşti */
} CardState;

/* --- Kart yapısı --- */
typedef struct {
    int       value;      /* kartın değeri: 1-8 (4x4 gridde 8 çift) */
    CardState state;      /* kapalı / açık / eşleşti                 */
    float     x, y;       /* ekrandaki piksel konumu                  */
    float     width;      /* kart genişliği                           */
    float     height;     /* kart yüksekliği                          */
} Card;

/* --- Sabitler --- */
#define GRID_ROWS    4
#define GRID_COLS    4
#define TOTAL_CARDS  (GRID_ROWS * GRID_COLS)   /* 16 kart = 8 çift */
#define CARD_W       100.0f
#define CARD_H       120.0f
#define CARD_MARGIN  20.0f

/* --- Fonksiyon bildirimleri --- */
void card_init_grid(Card grid[GRID_ROWS][GRID_COLS]);
void card_shuffle(Card grid[GRID_ROWS][GRID_COLS]);
void card_draw(const Card *card);
bool card_is_clicked(const Card *card, int mouse_x, int mouse_y);

#endif