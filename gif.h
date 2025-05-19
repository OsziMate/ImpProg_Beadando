#ifndef GIF_H
#define GIF_H

#include "image.h"
#include <stdlib.h>
#include <string.h>
#define TERMINAL_CLEAR "\033[2J"
#define TERMINAL_HOME "\033[2H"

typedef struct gif {
    image kepek[10];
} gif;

gif* gif_fajlokbol(const char* fajlnev);
void print_gif(gif* kesz_gif);
void gif_felszabadito(gif* kesz_gif);

#endif