#include "image.h"

image image_fajlbol(const char* fajlnev) {
    FILE* fajl = fopen(fajlnev, "r");
    if (fajl == NULL) {
        printf("Nincs ilyen fajl.\n");
        exit(1);
    }

    image kep;
    fscanf(fajl, "%d", &kep.szeles);
    fscanf(fajl, "%d", &kep.magas);

    if (kep.szeles > 30 || kep.magas > 30) {
        printf("A kep nagyobb mint a megengedett meretek.\n");
        fclose(fajl);
        exit(1);
    }

    kep.adatok = malloc(kep.magas * sizeof(enum color*));
    for (int i = 0; i < kep.magas; i++) {
        kep.adatok[i] = malloc(kep.szeles * sizeof(enum color));
    }

    for (int i = 0; i < kep.magas; i++) {
        for (int j = 0; j < kep.szeles; j++) {
            int szin;
            fscanf(fajl, "%d", &szin);
            kep.adatok[i][j] = (enum color)szin;
        }
    }

    fclose(fajl);
    return kep;
}

void image_print(image img) {
    for (int i = 0; i < img.magas; i++) {
        for (int j = 0; j < img.szeles; j++) {
            color_print(img.adatok[i][j]);
        }
        printf("\033[0m\n");
    }
}

void image_felszabadito(image* img) {
    for (int i = 0; i < img->magas; i++) {
        free(img->adatok[i]);
    }
    free(img->adatok);
    img->adatok = NULL;
}