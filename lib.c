// #include <stdio.h>
// #include <stdlib.h>
// #include <allegro5/allegro5.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
#include "lib.h"

sprites_t sprite;

void must_init(bool test, const char *description)
{
    if(test)    
        return;

    printf("couldn't initialize %s \n", description);
    exit(1);
}


void inicia_sprites() 
{
    sprite.amarela = al_load_bitmap("joia_amarela.png");
    must_init(sprite.amarela, "image");

    sprite.azul = al_load_bitmap("joia_azul.png");
    must_init(sprite.azul, "image");

    sprite.verde = al_load_bitmap("joia_verde.png");
    must_init(sprite.verde, "image");

    sprite.rosa = al_load_bitmap("joia_rosa.png");
    must_init(sprite.rosa, "image");
}

void desenha_joia(ALLEGRO_BITMAP *imagem, int h, int w, int x, int y, int selected)
{
    if(selected == 0)
        al_draw_scaled_bitmap(imagem,
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);
    else if(selected == 1)
        al_draw_tinted_scaled_bitmap(imagem,
        al_map_rgba_f(500, 0, 500, 0),
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);
    else if(selected == 2)
        al_draw_tinted_scaled_bitmap(imagem,
        al_map_rgba_f(500, 0, 0, 0),
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);

}


void destroi_sprites()
{
    al_destroy_bitmap(sprite.amarela);
    al_destroy_bitmap(sprite.azul);
    al_destroy_bitmap(sprite.verde);
    al_destroy_bitmap(sprite.rosa);
}