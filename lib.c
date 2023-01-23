#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "lib.h"

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
