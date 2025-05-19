#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <stdlib.h>

typedef struct image {
    enum color** adatok;
    int szeles;
    int magas;
} image;

image image_fajlbol(const char* fajlnev);
void image_print(image img);
void image_felszabadito(image* img);

#endif