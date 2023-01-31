// #include <stdio.h>
// #include <stdlib.h>
// #include <allegro5/allegro5.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
#include "lib.h"

// sprites_t sprites;
void inicia_sprites(sprites_t *sprite)
{
    sprite->amarela = al_load_bitmap("joia_amarela.png");
    must_init(sprite->amarela, "image");

    sprite->azul = al_load_bitmap("joia_azul.png");
    must_init(sprite->azul, "image");

    sprite->verde = al_load_bitmap("joia_verde.png");
    must_init(sprite->verde, "image");

    sprite->rosa = al_load_bitmap("joia_rosa.png");
    must_init(sprite->rosa, "image");
}

void desenha_joia(ALLEGRO_BITMAP *imagem, int h, int w, int x, int y)
{
    al_draw_scaled_bitmap(imagem,
    0, 0, 
    al_get_bitmap_width(imagem), 
    al_get_bitmap_height(imagem),
    x, y, 
    h, w, 
    0);
}


void destroi_sprites(sprites_t *sprite)
{
    al_destroy_bitmap(sprite->amarela);
    al_destroy_bitmap(sprite->azul);
    al_destroy_bitmap(sprite->verde);
    al_destroy_bitmap(sprite->rosa);
}