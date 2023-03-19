#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echo(char *str) {
    int i, j = 0, len = strlen(str);
    char c, quote = '\0', *word;

    for (i = 0; i < len; i++) {
        c = str[i];
        if (c == '\'' || c == '\"') {
            if (quote == '\0') {
                quote = c;
            } else if (quote == c) {
                quote = '\0';
            }
        } else if (c == ' ' || c == '\t') {
            if (quote == '\0') {
                word = (char *) malloc(sizeof(char) * (i - j + 1));
                strncpy(word, &str[j], i - j);
                word[i - j] = '\0';
                printf("%s ", word);
                free(word);
                j = i + 1;
            }
        }
    }

    if (j < len) {
        word = (char *) malloc(sizeof(char) * (i - j + 1));
        strncpy(word, &str[j], i - j);
        word[i - j] = '\0';
        printf("%s", word);
        free(word);
    }

    printf("\n");
}

int main(int argc, char **argv) {
    if (argc > 1) {
        echo(argv[1]);
    } else {
        printf("\n");
    }

    return 0;
}