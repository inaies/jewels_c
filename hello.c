#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

void must_init(bool test, const char *description)
{
    if(test)    return;

    printf("couldn't initialize %s \n", description);
    exit(1);
}


int main()
{
    int done = 0, menu = 1, jogo = 1;

    must_init(al_init(), "allegro");

    must_init(al_init_primitives_addon(), "primitives");    

    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); // timer do jogo

    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // fila de eventos   
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(700, 480); //inicializa as configuracoes do display
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();//incializa fonte a ser usada
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");

    ALLEGRO_BITMAP* image = al_load_bitmap("image.jpg");
    must_init(image, "image");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    // ALLEGRO_KEYBOARD_STATE tecla;

    al_start_timer(timer);
    while(1)
    {

        al_wait_for_event(queue, &event);
        //al_get_keyboard_state(&tecla);//pega tecla pressionada;

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                menu = 1;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:  
                if(event.keyboard.type != ALLEGRO_KEY_ESCAPE)
                {
                    menu = 0;
                    jogo = 1;
                    done = 0;
                } 
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = 1;
                break;
        }
            
        if(done)
            break;

        if(menu && (al_is_event_queue_empty(queue)))
        {
            al_clear_to_color(al_map_rgb(1, 12, 20));
            al_draw_text(font, al_map_rgb(255, 255, 255), 250, 300, 0, "Hello world!");
            al_draw_bitmap(image, 1, 100, 0);
            al_draw_filled_triangle(35, 350, 85, 375, 35, 400, al_map_rgb(0, 1, 0));
            al_flip_display();
            menu = 0;            
        }
        if(jogo && (al_is_event_queue_empty(queue)))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 250, 300, 0, "jogo");
            jogo = 0;
        }

    }

    al_destroy_bitmap(image);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}