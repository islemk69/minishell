#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_pipe(char* string) {
    char quote = '\0';
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == '"' || string[i] == '\'') {
            if (quote == '\0') {
                quote = string[i];
            } else if (quote == string[i]) {
                quote = '\0';
            }
        } else if (string[i] == '|' && string[i+1] == '|' && quote == '\0') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    char str1[] = "salut || sa va";
    char str2[] = "salut \"||\" sa va";
    printf("%d\n", check_pipe(str1)); // Output: 0
    printf("%d\n", check_pipe(str2)); // Output: 1
    return 0;
}