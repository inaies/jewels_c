#ifndef _LIB_t_H
#define _LIB_t_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>    
#include "lib.h"


enum BOUNCER_TYPE {
    BT_HELLO = 0,
    BT_MYSHA
};

struct sprites
{
    ALLEGRO_BITMAP *verde;
    ALLEGRO_BITMAP *azul;
    ALLEGRO_BITMAP *amarela;
    ALLEGRO_BITMAP *rosa;
};
typedef struct sprites sprites_t;

struct game_addons
{
    ALLEGRO_SAMPLE* som_combinacao;
    ALLEGRO_FONT* font;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_BITMAP* image;
};
typedef struct game_addons game_addons_t;

extern sprites_t sprite;

void must_init(bool test, const char *description);

void inicia_sprites();

void desenha_joia(ALLEGRO_BITMAP *image, int h, int w, int x, int y, int selected);

void destroi_sprites();

void destroi_addons(game_addons_t *addons);

game_addons_t* init_game_addons();

#endif