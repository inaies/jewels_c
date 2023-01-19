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


#endif