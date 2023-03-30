#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string(char* str) {
    int num_words = 0;
    int in_quotes = 0;
    char quote_type = '\0';

    // Compte le nombre de mots dans la chaîne
    for (int i = 0; i < ft_strlen(str); i++) {
        char c = str[i];

        if (c == '\'' || c == '\"') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_type = c;
            } else if (c == quote_type && str[i - 1] != '\\') {
                in_quotes = 0;
                quote_type = '\0';
            }
        }

        if ((c == ' ' || c == '\t') && !in_quotes) {
            num_words++;
        }
    }

    // Alloue la mémoire nécessaire pour le tableau de mots
    char** words = malloc(sizeof(char*) * (num_words + 1));
    int word_index = 0;

    // Construit chaque mot et l'ajoute au tableau
    char* cur_word = malloc(sizeof(char) * ft_strlen(str));
    int cur_word_len = 0;
    in_quotes = 0;

    for (int i = 0; i < ft_strlen(str); i++) {
        char c = str[i];

        if (c == '\'' || c == '\"') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_type = c;
            } else if (c == quote_type && str[i - 1] != '\\') {
                in_quotes = 0;
                quote_type = '\0';
            }
        }

        if ((c == ' ' || c == '\t') && !in_quotes) {
            if (cur_word_len > 0) {
                cur_word[cur_word_len] = '\0';
                words[word_index++] = cur_word;
                cur_word = malloc(sizeof(char) * ft_strlen(str));
                cur_word_len = 0;
            }
        } else {
            cur_word[cur_word_len++] = c;
        }
    }

    if (cur_word_len > 0) {
        cur_word[cur_word_len] = '\0';
        words[word_index++] = cur_word;
    } else {
        free(cur_word);
    }

    words[word_index] = NULL;
    return words;
}
int main() {
    char str[] = "\"\"   \'\' \'\' \'\'   \"\"";
    char** words = split_string(str);
    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
    }
    return 0;
}
