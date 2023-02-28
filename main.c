#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>    
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
#include "matrix.h"
#include "mouse.h"
#include "pontuacao.h"
#include "animacao.h"

#define linesize 1024
#define display_size 700

void menu(game_addons_t *addons)
{
    al_draw_tinted_scaled_bitmap(addons->image,
        al_map_rgba_f(500, 0, 500, 0),
        0, 0, 
        al_get_bitmap_width(addons->image), 
        al_get_bitmap_height(addons->image),
        -150, -300, 
        1000, 1000, 
        0);
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 300, 400, 0, "space to play");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 300, 450, 0, " f1 to help ");
}

void help(game_addons_t *addons)
{
    al_draw_text(addons->font, al_map_rgb(100, 200, 255), 150, 200, 0, "jogo de combinacoes");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 150, 230, 0, "objetivo: obter a maior pontuacao");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 150, 240, 0, "combinacoes sao conjuntos de tres ou mais joias em sequencia");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 150, 250, 0, "podem ser feitas em linha ou coluna");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 250, 300, 0, "by: inaie");
    al_draw_text(addons->font, al_map_rgb(255, 255, 255), 250, 350, 0, "f2 para sair");
}

enum STATE
{
    MENU,
    HELP,
    JOGO,
    FIM,
    TROCA,
    REFAZ_TROCA,
    GERA_JOIAS
};

int main()
{

    int done = 0, redraw = 1;
    int x = 100, y = 100;
    int estado_do_jogo = MENU;
    int click = 0;
    int pontuacao = 0;
    int nivel = 1;
    char *linha = malloc(sizeof(char)*linesize);

    srand(clock());
    MATRIX_t **m = inicia_matrix(10);
    MATRIX_t *sel1, *sel2;
    combinacao_t *joia;

    sel1 = malloc(sizeof(MATRIX_t));
    sel2 = malloc(sizeof(MATRIX_t));
    joia = malloc(sizeof(combinacao_t));

    must_init(al_init(), "allegro");

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_install_keyboard(), "keyboard");

    must_init(al_install_mouse(), "mouse");

    game_addons_t *addons = init_game_addons();

    inicia_sprites();

    al_register_event_source(addons->queue, al_get_keyboard_event_source());
    al_register_event_source(addons->queue, al_get_display_event_source(addons->display));
    al_register_event_source(addons->queue, al_get_timer_event_source(addons->timer));
    al_register_event_source(addons->queue, al_get_mouse_event_source());

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE tecla;

    #define KEY_SEEN 1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    // zera array que contem todas as teclas que podem ser pressionadas
    memset(key, 0, sizeof(key));

    al_start_timer(addons->timer);
    while (1)
    {

        al_wait_for_event(addons->queue, &event);
        al_get_keyboard_state(&tecla); // pega tecla pressionada;

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = 1;
            if (estado_do_jogo == HELP)
            {
                if (key[ALLEGRO_KEY_F2])
                    estado_do_jogo = MENU;
                if (key[ALLEGRO_KEY_SPACE])
                    estado_do_jogo = JOGO;
            }

            if (estado_do_jogo == MENU)
            {
                if (key[ALLEGRO_KEY_SPACE])
                    estado_do_jogo = JOGO;
                else if (key[ALLEGRO_KEY_F1])
                    estado_do_jogo = HELP;
            }

            if (estado_do_jogo == JOGO)
            {
                if (key[ALLEGRO_KEY_UP])
                    estado_do_jogo = FIM;
            }

            if (estado_do_jogo == FIM)
            {
                if (key[ALLEGRO_KEY_DOWN])
                    estado_do_jogo = MENU;
            }

            if (key[ALLEGRO_KEY_ESCAPE])
                done = 1;

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            x = event.mouse.x;
            y = event.mouse.y;
            click = 1;
            if ((mouse_joia(m, x, y, click, sel1, sel2)))
                estado_do_jogo = TROCA;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            x = event.mouse.x;
            y = event.mouse.y;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && (al_is_event_queue_empty(addons->queue)))
        {
            if (estado_do_jogo == MENU)
            {
                menu(addons);
            }
            if (estado_do_jogo == JOGO)
            {
                mouse_joia(m, x, y, click, sel1, sel2);
                desenha_matrix(m, addons, pontuacao);
            }

            if (estado_do_jogo == HELP)
                help(addons);

            if (estado_do_jogo == TROCA)
            {
                if (troca_animacao(m, sel1, sel2))
                {
                    troca(m, sel1, sel2);
                    if (!(busca_combinacao(m, joia, 0, sel1, sel2)))
                    {
                        sleep(0.8);
                        estado_do_jogo = REFAZ_TROCA;
                    }
                    else
                    {
                        al_play_sample(addons->som_combinacao, 0.2, 0.0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);  
                        pontuacao += calcula_pontuacao(joia, nivel);
                        estado_do_jogo = GERA_JOIAS;
                    }
                }
                else
                    estado_do_jogo = TROCA;

                desenha_matrix(m, addons, pontuacao);
            }

            if (estado_do_jogo == REFAZ_TROCA)
            {
                if (troca_animacao(m, sel1, sel2))
                {
                    troca(m, sel1, sel2);
                    estado_do_jogo = JOGO;
                }
                else
                    estado_do_jogo = REFAZ_TROCA;

                desenha_matrix(m, addons, pontuacao);
            }

            if (estado_do_jogo == GERA_JOIAS)
            {
                if ((joia->i1_inicio == joia->i1_final) && (joia->i1_inicio != -1))
                {
                    if (animacao_combinacao_linha(m, joia))
                    {
                        troca_combinacao_linha(m, joia, 1);
                        gera_novas_joias(m);
                        zera_combinacao(joia);
                        // estado_do_jogo == JOGO;
                    }
                    else
                        estado_do_jogo = GERA_JOIAS;
                }
                if ((joia->j1_inicio == joia->j1_final) && (joia->j1_inicio != -1))
                {
                    if (animacao_combinacao_coluna(m, joia))
                    {
                        troca_combinacao_coluna(m, joia);
                        gera_novas_joias(m);
                        zera_combinacao(joia);
                        estado_do_jogo = JOGO;
                    }
                    else
                        estado_do_jogo = GERA_JOIAS;
                }
                if ((estado_do_jogo == JOGO) && (busca_combinacao(m, joia, 0, sel1, sel2)))
                {
                    pontuacao += calcula_pontuacao(joia, nivel);
                    gera_novas_joias(m);
                    estado_do_jogo = GERA_JOIAS;
                }
                if ((!(busca_combinacao(m, joia, 0, sel1, sel2))) && (estado_do_jogo = JOGO))
                {
                    estado_do_jogo = JOGO;
                    if(pontuacao >= 100)
                        nivel += 1;
                    if(pontuacao >= 200)
                        nivel += 2;
                }
                desenha_matrix(m, addons, pontuacao);
            }

            if (estado_do_jogo == FIM)
                al_draw_text(addons->font, al_map_rgb(255, 255, 255), 250, 300, 0, "fim de jogo \n");
            al_flip_display();

            al_clear_to_color(al_map_rgb(0, 0, 0));
            redraw = 0;
        }

        if (click)
            click = 0;
    }

    free(linha);
    free(m);
    free(sel1);
    free(sel2);
    free(joia);
    destroi_sprites();
    destroi_addons(addons);

    return 0;
}