#include "gif.h"

#include <unistd.h>

gif* gif_fajlokbol(const char* fajlnev) {
    gif* kesz_gif = malloc(sizeof(gif));

    for (int i = 0; i < 10; i++) {
        char teljes_fajlnev[100] = "";
        sprintf(teljes_fajlnev, "%s.bg%d", fajlnev, i);
        kesz_gif->kepek[i] = image_fajlbol(teljes_fajlnev);
    }

    return kesz_gif;
}

void print_gif(gif* kesz_gif) {
    int db;
    printf("Hanyszor szeretned, hogy lejatszodjon a GIF? ");
    scanf("%d", &db);
    int j = 0;
    while (j < db) {
        for (int i = 0; i < 10; i++) {
            printf(TERMINAL_CLEAR TERMINAL_HOME);
            image_print(kesz_gif->kepek[i]);
            sleep(1);
        }
        j++;
    }
}

void gif_felszabadito(gif* kesz_gif) {
    if (!kesz_gif) return;

    for (int i = 0; i < 10; i++) {
        image_felszabadito(&kesz_gif->kepek[i]);
    }
    free(kesz_gif);
}