#ifndef _LIB_t_H
#define _LIB_t_H

enum BOUNCER_TYPE {
    BT_HELLO = 0,
    BT_MYSHA
};

struct piece
{
    float x, y;
    float dx, dy;
    int type;
};
typedef struct piece piece_t;

// void must_init(bool test, const char *description);

void desenha_joia(ALLEGRO_BITMAP *image, int h, int w, int x, int y);

#endif