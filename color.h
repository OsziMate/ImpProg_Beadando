#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

enum color {
    fekete = 0,
    piros,
    zold,
    sarga,
    kek,
    magenta,
    cian,
    feher
};

const char* szin_valto(enum color szin);
void color_print(enum color szin);

#endif