#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;
    int history_index = 0;

    while ((input = readline("> ")) != NULL) {
        if (strlen(input) > 0) {
            // Si l'entrée n'est pas vide, on l'ajoute à l'historique
            add_history(input);
            // On réinitialise l'index de l'historique
            history_index = 0;
        }

        if (strcmp(input, "history") == 0) {
            // Si l'utilisateur tape "history", on affiche l'historique des commandes
            HIST_ENTRY **history_lists = history_list();
            for (int i = 0; history_lists[i] != NULL; i++) {
                printf("%4d %s\n", i + history_base, history_lists[i]->line);
            }
            continue;
        }

        if (strcmp(input, "!!") == 0) {
            // Si l'utilisateur tape "!!", on réutilise la dernière commande non vide
            HIST_ENTRY *last_entry = history_get(history_length);
            if (last_entry != NULL) {
                input = last_entry->line;
                add_history(input);
            } else {
                printf("No last command in history\n");
                continue;
            }
        }

        if (input[0] == '!') {
            // Si l'utilisateur tape "!n", où n est un entier, on réutilise la n-ième commande non vide de l'historique
            int command_index = atoi(&input[1]);
            HIST_ENTRY *history_entry = history_get(history_base + command_index - 1);
            if (history_entry != NULL) {
                input = history_entry->line;
                add_history(input);
            } else {
                printf("Command not found in history\n");
                continue;
            }
        }

        // Si l'utilisateur appuie sur la touche haut, on remonte dans l'historique
        if (input[0] == '\033' && input[1] == '[' && input[2] == 'A') {
            if (history_index < history_length) {
                // On incrémente l'index de l'historique et on récupère la commande correspondante
                history_index++;
                HIST_ENTRY *history_entry = history_get(history_length - history_index);
                if (history_entry != NULL) {
                    // On modifie l'entrée en cours avec la commande de l'historique
                    replace_history_entry(history_length, history_entry->line, NULL);
                    input = history_entry->line;
                } else {
                    history_index--;
                }
            }
        }

        // Si l'utilisateur appuie sur la touche bas, on descend dans l'historique
        if (input[0] == '\033' && input[1] == '[' && input[2] == 'B') {
            if (history_index > 0) {
                // On décrémente l'index de l'historique et on récupère la commande correspondante
                history_index--;
                if (history_index == 0) {
                    // Si on est revenu à l'entrée en cours, on remplace l'entrée par une chaîne vide
                    replace_history_entry(history_length, "", NULL);
                    input = "";
                } else {
                    HIST_ENTRY *history_entry = history_get(history_length - history_index);
                    if (history_entry != NULL) {
                        // On modifie l'entrée en cours avec la commande de l'historique
                        replace_history_entry(history_length, history_entry->line, NULL);
                        input = history_entry->line;
                    } else {
                        history_index++;
                    }
                }
            }
    }

    // On affiche l'entrée en cours
    printf("Input: %s\n", input);

    free(input);
    
    }
    return 0;
}