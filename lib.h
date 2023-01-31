#ifndef _LIB_t_H
#define _LIB_t_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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

// extern sprites_t sprites;
void inicia_sprites(sprites_t *sprite);

void desenha_joia(ALLEGRO_BITMAP *image, int h, int w, int x, int y);

void destroi_sprites(sprites_t *sprite);

#endif