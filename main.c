#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
#include "matrix.h"
#include "mouse.h"
#include "pontuacao.h"
#include "animacao.h"

#define display_size 700

void menu()
{
    ALLEGRO_FONT* font = al_create_builtin_font();//incializa fonte a ser usada
    must_init(font, "font");

    al_draw_text(font, al_map_rgb(255, 255, 255), 250, 300, 0, "espaço pra jogar \n");                
}

void jogo_principal(int x, int y, MATRIX_t **m)
{

    ALLEGRO_FONT* font = al_create_builtin_font();//incializa fonte a ser usada
    must_init(font, "font");

}

enum STATE
{
    MENU,
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

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // timer do jogo

    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // fila de eventos   
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(display_size, display_size); //inicializa as configuracoes do display
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();//incializa fonte a ser usada
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");

    ALLEGRO_BITMAP* image = al_load_bitmap("image.jpg");
    must_init(image, "image");
    inicia_sprites();

    must_init(al_install_mouse(), "mouse");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());      

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE tecla;

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    //zera array que contem todas as teclas que podem ser pressionadas
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while(1)
    {

        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&tecla);//pega tecla pressionada;

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = 1;
                if (estado_do_jogo == MENU)
                {
                    if(key[ALLEGRO_KEY_SPACE])
                        estado_do_jogo = JOGO;
                }
                if(estado_do_jogo == JOGO)
                {
                    if(key[ALLEGRO_KEY_UP])
                        estado_do_jogo = FIM;
                }

                if(estado_do_jogo == FIM)
                {
                    if (key[ALLEGRO_KEY_DOWN])
                        estado_do_jogo = MENU;
                }
                // if(estado_do_jogo == TROCA)
                //     estado_do_jogo = TROCA;

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = 1;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                x = event.mouse.x;
                y = event.mouse.y;
                click = 1;
                if((mouse_joia(m, x, y, click, sel1, sel2)))
                {
                    estado_do_jogo = TROCA;
                    printf("i %d, j %d \n i %d j %d \n", sel1->px, sel1->py, sel2->px, sel2->py);
                }
                // else
                //     segundo_click = click;
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
            // default:
            //     estado_do_jogo = JOGO;
        }
            
        if(done)
            break;

        if(redraw && (al_is_event_queue_empty(queue)))
        {
            if(estado_do_jogo == MENU)
                menu();
            if(estado_do_jogo == JOGO)
            {
                mouse_joia(m, x, y, click, sel1, sel2);
                desenha_matrix(m);
            }

            if(estado_do_jogo == TROCA)
            {
                if(troca_animacao(m, sel1, sel2))
                {    
                    troca(m, sel1, sel2);
                    if (!(busca_combinacao(m, joia, 0, sel1, sel2)))
                    {
                        sleep(0.8);
                        estado_do_jogo = REFAZ_TROCA;
                    }
                    else
                    {
                        busca_combinacao(m, joia, 1, sel1, sel2);
                        estado_do_jogo = GERA_JOIAS;
                    }
                }
                else
                    estado_do_jogo = TROCA;

                desenha_matrix(m);
            }

            if(estado_do_jogo == REFAZ_TROCA)
            {
                if (troca_animacao(m, sel1, sel2))
                {
                    troca(m, sel1, sel2);
                    estado_do_jogo = JOGO;
                }
                else
                    estado_do_jogo = REFAZ_TROCA;

                desenha_matrix(m);
            }
            
            if(estado_do_jogo == GERA_JOIAS)
            {
                if ((joia->i1_inicio == joia->i1_final)&&(joia->i1_inicio != -1))
                {
                    // printf("combinacao em linha \n");
                    if (animacao_combinacao_linha(m, joia))
                    {
                        //verifica se houve duas combinacoes de linha uma sobre a outra
                        // if((joia->i2_inicio == joia->i2_final)&&(joia->i2_inicio != -1))
                        //     troca_combinacao_linha(m, joia, 2);
                        // else
                            troca_combinacao_linha(m, joia, 1);
                        gera_novas_joias(m);
                        // printf("aaaa porraaa \n");
                        zera_combinacao(joia);
                        estado_do_jogo == JOGO;
                    }   
                    else
                        estado_do_jogo = GERA_JOIAS;
                }
                if((joia->j1_inicio == joia->j1_final)&&(joia->j1_inicio != -1))
                {
                    if(animacao_combinacao_coluna(m, joia))
                    {
                        troca_combinacao_coluna(m, joia);
                        gera_novas_joias(m);
                        zera_combinacao(joia);
                        estado_do_jogo = JOGO;
                    }
                    else
                        estado_do_jogo = GERA_JOIAS;
                }
                if((estado_do_jogo == JOGO)&&(busca_combinacao(m, joia, 0, sel1, sel2)))
                {
                    gera_novas_joias(m);
                    // busca_combinacao(m, joia, 1);
                    estado_do_jogo = GERA_JOIAS;
                }
                if((!(busca_combinacao(m, joia, 0, sel1, sel2)))&&(estado_do_jogo = JOGO))
                    estado_do_jogo = JOGO;                   
                desenha_matrix(m);
            }

            if(estado_do_jogo == FIM)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 250, 300, 0, "fim de jogo \n");                
            }
            al_flip_display();

            al_clear_to_color(al_map_rgb(0, 0, 0));
            redraw = 0;
        }

        if(click)
            click = 0;
        
    }

    destroi_sprites();
    al_destroy_bitmap(image);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}