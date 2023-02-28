// #include <stdio.h>
// #include <stdlib.h>
// #include <allegro5/allegro5.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
#include "lib.h"
#define display_size 700

sprites_t sprite;

void must_init(bool test, const char *description)
{
    if(test)    
        return;

    printf("couldn't initialize %s \n", description);
    exit(1);
}

void destroi_addons(game_addons_t *addons)
{
    al_destroy_bitmap(addons->image);
    al_destroy_display(addons->display);
    al_destroy_timer(addons->timer);
    al_destroy_event_queue(addons->queue);
    al_destroy_sample(addons->som_combinacao);
    al_destroy_font(addons->font);
}

game_addons_t* init_game_addons()
{
    game_addons_t *addons = malloc(sizeof(game_addons_t));
        
    addons->font = al_create_builtin_font();//incializa addons->addons->font a ser usada
    must_init(addons->font, "font");

    addons->timer = al_create_timer(1.0 / 60.0); // timer do jogo

    must_init(addons->timer, "timer");

    addons->queue = al_create_event_queue(); // fila de eventos   
    must_init(addons->queue, "queue");

    addons->display = al_create_display(display_size, display_size); //inicializa as configuracoes do display
    must_init(addons->display, "display");

    must_init(al_install_audio(), "áudio");
    must_init(al_init_acodec_addon(), "codec de áudio");
    addons->som_combinacao = al_load_sample("resources/combinacao.opus");

    must_init(al_init_image_addon(), "image addon");

    addons->image = al_load_bitmap("resources/jewels.png");
    must_init(addons->image, "image");

    return(addons);
}

void inicia_sprites() 
{
    sprite.amarela = al_load_bitmap("resources/joia_amarela.png");
    must_init(sprite.amarela, "image");

    sprite.azul = al_load_bitmap("resources/joia_azul.png");
    must_init(sprite.azul, "image");

    sprite.verde = al_load_bitmap("resources/joia_verde.png");
    must_init(sprite.verde, "image");

    sprite.rosa = al_load_bitmap("resources/joia_rosa.png");
    must_init(sprite.rosa, "image");
}

void desenha_joia(ALLEGRO_BITMAP *imagem, int h, int w, int x, int y, int selected)
{
    //0 -> sem mouse sem estar selecionada
    if(selected == 0)
        al_draw_scaled_bitmap(imagem,
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);
    //1 -> passou o mouse
    else if(selected == 1)
        al_draw_tinted_scaled_bitmap(imagem,
        al_map_rgba_f(500, 0, 500, 0),
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);
    //2 - > joia clicada
    else if(selected == 2)
        al_draw_tinted_scaled_bitmap(imagem,
        al_map_rgba_f(500, 0, 0, 0),
        0, 0, 
        al_get_bitmap_width(imagem), 
        al_get_bitmap_height(imagem),
        x, y, 
        h, w, 
        0);
    //3 -> selecionada pra troca com joia.sel = 2
    else if(selected == 3)
        al_draw_tinted_scaled_bitmap(imagem,
        al_map_rgba_f(0, 0, 0, 0),
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