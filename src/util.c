#include "util.h"

#include <stdio.h>
#include <string.h>

int read_line(char* str) {
    char tmp[256];

    if (fgets(tmp, sizeof(tmp), stdin) == NULL) {
        fprintf(stderr, "fgets() falhou\n");
        str[0] = '\0';
        return 1;
    }

    tmp[strcspn(tmp, "\n")] = '\0';
    strcpy(str, tmp);

    return 0;
}
