#include "color.h"
#include "image.h"
#include "gif.h"

int main() {
    int db = 0;
    char valasz[100];
    char fajlnev[100];
    image kep;
    gif* gif_kepekbol;

    while (db < 3) {
        if (db == 0) {
            printf("Szeretnel-e egy szint kirajzolni? (Igen / Nem) ");
            scanf("%99s", valasz);
            if (strcmp(valasz, "Igen") == 0) {
                printf("Szintabla:\n0 - Fekete\n1 - Piros\n2 - Zold\n3 - Sarga\n4 - Kek\n5 - Magenta\n6 - Cyan\n7 - Feher\n");
                printf("Milyen szint szeretnel kiirni? ");
                int szin;
                scanf("%d", &szin);
                color_print((enum color)szin);
                printf("\n");
            }
	    db++;
        } else if (db == 1) {
            printf("Szeretnel-e egy kepet kirajzolni? (Igen / Nem) ");
            scanf("%99s", valasz);
            if (strcmp(valasz, "Igen") == 0) {
                printf("Add meg a kepnek a fajlnevet, kiterjesztessel egyutt! ");
                scanf("%99s", fajlnev);
                kep = image_fajlbol(fajlnev);
                image_print(kep);
                image_felszabadito(&kep);
            }
	    db++;
        } else if (db == 2) {
            printf("Szeretnel-e egy GIFet kirajzolni? (Igen / Nem) ");
            scanf("%99s", valasz);
            if (strcmp(valasz, "Igen") == 0) {
                printf("Add meg a kepnek a fajlnevet, kiterjesztes nelkul! ");
                scanf("%99s", fajlnev);
                gif_kepekbol = gif_fajlokbol(fajlnev);
                print_gif(gif_kepekbol);
                gif_felszabadito(gif_kepekbol);
            }
	    printf("Szeretned-e, hogy a program ujra lefusson? (Igen / Nem) ");
            scanf("%99s", valasz);
            if (strcmp(valasz, "Igen") == 0) {
                db = 0;
            } else {
                db++;
            }

        }

    }
    printf("Program vege!\n");
    return 0;
}