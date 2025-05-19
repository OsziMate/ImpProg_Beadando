#include "color.h"

const char* szin_valto(enum color szin) {
    switch (szin) {
        case fekete: return "\033[40m";
        case piros: return "\033[41m";
        case zold: return "\033[42m";
        case sarga: return "\033[43m";
        case kek: return "\033[44m";
        case magenta: return "\033[45m";
        case cian: return "\033[46m";
        case feher: return "\033[47m";
        default: return "\033[0m";
    }
}

void color_print(enum color szin) {
    printf("%s  \033[0m", szin_valto(szin));
}
