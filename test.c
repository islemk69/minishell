#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 100

bool is_quote(char c) {
    return (c == '"' || c == '\'');
}

void split_string(char* str) {
    int i = 0, j = 0;
    bool in_quote = false;
    char** words = malloc(MAX_LEN * sizeof(char*));
    if (!words) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    while (str[i] != '\0') {
        if (is_quote(str[i])) {
            in_quote = !in_quote;
        }
        else if (!in_quote && (str[i] == ' ' || str[i] == '\t')) {
            str[i] = '\0';
            words[j] = &str[i+1];
            j++;
        }
        i++;
    }
    words[j] = &str[i];  // pointeur vers la fin de la chaîne
    printf("Les mots dans la chaîne sont : \n");
    for (int k = 0; k <= j; k++) {
        printf("%s\n", words[k]);
    }
    free(words);
}

int main() {
    char str[MAX_LEN] = "Je suis entre guillemet : \"bonjour tout le monde\" et 'comment ça va ?'";
    printf("Chaîne d'origine : %s\n", str);
    split_string(str);
	printf("Chaîne finale : %s\n", str);
    return 0;
}