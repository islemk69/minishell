#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *str)
{
    int num_words = 0;
    int in_quotes = 0;
    char quote_type = '\0';
    char **words;

    // Compte le nombre de mots dans la chaîne
    int i = 0;
    while (str[i])
    {
        char c = str[i];

        if (c == '\'' || c == '\"')
        {
            if (!in_quotes)
            {
                in_quotes = 1;
                quote_type = c;
            }
            else if (c == quote_type && str[i - 1] != '\\')
            {
                in_quotes = 0;
                quote_type = '\0';
            }
        }

        if ((c == ' ' || c == '\t') && !in_quotes)
        {
            num_words++;
        }
        i++;
    }

    // Alloue la mémoire nécessaire pour le tableau de mots
    words = malloc((num_words + 1) * sizeof(char *));
    if (!words)
        return (NULL);

    int word_index = 0;
    int prev_word_end = 0;

    // Construit chaque mot et l'ajoute au tableau
    i = 0;
    while (str[i])
    {
        char c = str[i];

        if (c == '\'' || c == '\"')
        {
            if (!in_quotes)
            {
                in_quotes = 1;
                quote_type = c;
            }
            else if (c == quote_type && str[i - 1] != '\\')
            {
                in_quotes = 0;
                quote_type = '\0';
            }
        }

        if ((c == ' ' || c == '\t') && !in_quotes)
        {
            if (i > prev_word_end)
            {
                int word_len = i - prev_word_end;
                words[word_index] = malloc((word_len + 1) * sizeof(char));
                if (!words[word_index])
                {
                    for (int j = 0; j < word_index; j++)
                    {
                        free(words[j]);
                    }
                    free(words);
                    return (NULL);
                }
                strncpy(words[word_index], &str[prev_word_end], word_len);
                words[word_index][word_len] = '\0';
                word_index++;
            }
            prev_word_end = i + 1;
        }

        i++;
    }

    // Ajoute le dernier mot
    if (i > prev_word_end)
    {
        int word_len = i - prev_word_end;
        words[word_index] = malloc((word_len + 1) * sizeof(char));
        if (!words[word_index])
        {
            for (int j = 0; j < word_index; j++)
            {
                free(words[j]);
            }
            free(words);
            return (NULL);
        }
        strncpy(words[word_index], &str[prev_word_end], word_len);
        words[word_index][word_len] = '\0';
        word_index++;
    }

    words[word_index] = NULL;
    return words;
}
int main() {
    char str[] = "\"salut sa va\" oui et toi";
    char** words = split_string(str);
    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
    }
	int j = 0;
	while (words[j])
	{
		free(words[j]);
		j++;
	}
	free(words);
    return 0;
}
