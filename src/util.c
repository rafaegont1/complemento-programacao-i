#include "util.h"

#include <stdio.h>
#include <string.h>

void clear_buffer()
{
    char c;
    while ((c= getchar()) != '\n' && c != EOF);
}

int read_line(char* str, int str_sz)
{
    if (fgets(str, str_sz, stdin) == NULL) {
        fprintf(stderr, "fgets() falhou\n");
        str[0] = '\0';
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    return 0;
}
