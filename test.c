#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_words(char *input, char sep)
{
    int count = 0;
    int in_double_quote = 0;
    int in_single_quote = 0;
    char *c = input;
    while (*c != '\0') {
        if (*c == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (*c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (*c == sep && !in_double_quote && !in_single_quote) {
            count++;
        }
        c++;
    }
    return count + 1;
}

static char *next_pipe(char *input, char sep)
{
    int in_double_quote = 0;
    int in_single_quote = 0;
    char *c = input;
    while (*c != '\0') {
        if (*c == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (*c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (*c == sep && !in_double_quote && !in_single_quote) {
            return c;
        }
        c++;
    }
    return NULL;
}

static int word_length(char *start, char *end)
{
    int in_quote = 0;
    char *c = start;
    while (c < end) {
        if (*c == '\"') {
            in_quote = !in_quote;
        }
        c++;
    }
    return end - start - (in_quote ? 2 : 0);
}


char **ft_split_token(char *input, char sep)
{
    int count;
	char *end;
	int i;

	i = 0;
	count = count_words(input, sep);
    char **split = (char **)malloc(sizeof(char *) * (count + 1));
    if (!split || input[0] == '|' || input[strlen(input) - 1] == '|')
	{
        return (NULL);
	}
   	end = next_pipe(input, sep);
    while (end != NULL) {
        split[i] = malloc(word_length(input, end) + 1);
        if (!split[i]) {
            return NULL;
        }
        strncpy(split[i], input, end - input);
        split[i][end - input] = '\0';
        i++;
        input = end + 1;
        end = next_pipe(input, sep);
    }
    split[i] = strdup(input);
    if (!split[i])
        return NULL;
    split[i + 1] = NULL;
    return (split);
}

int main() {
    char str1[] = "ls wc";
    char **tab = ft_split_token(str1, ' '); // Output: 0
	int i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
	}
    return 0;
}