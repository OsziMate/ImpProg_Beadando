#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RESET "\033[0m"
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"
#define MAX_MERET 30
#define TERMINAL_CLEAR "\033[2J"
#define TERMINAL_HOME "\033[2H"

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

typedef struct image {
    enum color** adatok;
    int szeles;
    int magas;
} image;

typedef struct gif {
    image kepek[10];
} gif;

const char* szin_valto(enum color szin) {
    switch (szin) {
        case fekete: return BG_BLACK;
        case piros: return BG_RED;
        case zold: return BG_GREEN;
        case sarga: return BG_YELLOW;
        case kek: return BG_BLUE;
        case magenta: return BG_MAGENTA;
        case cian: return BG_CYAN;
        case feher: return BG_WHITE;
        default: return RESET;
    }
}

image image_fajlbol(const char* fajlnev) {
    FILE* fajl = fopen(fajlnev, "r");
    if (fajl == NULL) {
        printf("Nincs ilyen fajl.\n");
        exit(1);
    }

    image kep;
    fscanf(fajl, "%d", &kep.szeles);
    fscanf(fajl, "%d", &kep.magas);

    if (kep.szeles > MAX_MERET || kep.magas > MAX_MERET) {
        printf("A kep nagyobb mint a megengedett meretek.\n");
        fclose(fajl);
        exit(1);
    }

    kep.adatok = (enum color**)malloc(kep.magas * sizeof(enum color*));
    for (int i = 0; i < kep.magas; i++) {
        kep.adatok[i] = (enum color*)malloc(kep.szeles * sizeof(enum color));
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
            const char* colour = szin_valto(img.adatok[i][j]);
            printf("%s  %s", colour, RESET);
        }
        printf("\n");
    }
}

void image_felszabadito(image* img) {
    for (int i = 0; i < img->magas; i++) {
        free(img->adatok[i]);
    }
    free(img->adatok);
    img->adatok = NULL;
}

gif* gif_fajlokbol(const char* fajlnev) {
    gif* kesz_gif = (gif*)malloc(sizeof(gif));

    for (int i = 0; i < 10; i++) {
        char teljes_fajlnev[100] = "";
        char szam[3];
        sprintf(szam, "%d", i);
        strcat(teljes_fajlnev,fajlnev);
        strcat(teljes_fajlnev,".bg");
        strcat(teljes_fajlnev,szam);
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

int igen_nem_kerdes(const char* kerdes) {
    char valasz[100];
    while (1) {
        printf("%s (Igen / Nem): ", kerdes);
        scanf("%99s", valasz);
        if (strcmp(valasz, "Igen") == 0) return 1;
        if (strcmp(valasz, "Nem") == 0) return 0;
        printf("Hibas valasz! Probald ujra.\n");
    }
}

int main() {
    int db = 0;
    char fajlnev[100];
    char teljes_fajlnev[100];
    enum color szin;
    image kep;
    gif* gif_kepekbol;

    while (db < 3) {
        if (db == 0) {
            if (igen_nem_kerdes("Szeretnel-e egy szint kirajzolni?")) {
                printf("Szintabla:\n0 - Fekete\n1 - Piros\n2 - Zold\n3 - Sarga\n4 - Kek\n5 - Magenta\n6 - Cyan\n7 - Feher\nMilyen szint szeretnel kiirni? ");
                scanf("%d", (int*)&szin);
                const char* colour = szin_valto(szin);
                printf("%s  %s\n", colour, RESET);
            }
        }
        if (db == 1) {
            if (igen_nem_kerdes("Szeretnel-e egy kepet kirajzolni?")) {
                printf("Add meg a kepnek a fajlnevet, kiterjesztessel egyutt! ");
                scanf("%99s", teljes_fajlnev);
                kep = image_fajlbol(teljes_fajlnev);
                image_print(kep);
                image_felszabadito(&kep);
            }
        }
        if (db == 2) {
            if (igen_nem_kerdes("Szeretnel-e egy GIFet kirajzolni?")) {
                printf("Add meg a kepnek a fajlnevet, kiterjesztes nelkul! ");
                scanf("%99s", fajlnev);
                gif_kepekbol = gif_fajlokbol(fajlnev);
                print_gif(gif_kepekbol);
                gif_felszabadito(gif_kepekbol);
            }
            if (igen_nem_kerdes("Szeretned-e, hogy a program ujra lefusson?")) {
                db = 0;
                continue;
            }
        }
        db++;
    }

    printf("Program vege\n");
    return 0;
}
