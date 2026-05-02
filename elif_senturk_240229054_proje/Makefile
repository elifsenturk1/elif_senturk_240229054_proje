CC = gcc

CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)
LIBS = $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)

SRC = src/main.c src/game.c src/card.c
OBJ = $(SRC:.c=.o)
TARGET = elif_senturk_240229054

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)