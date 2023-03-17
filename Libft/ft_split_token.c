#include "libft.h"

static int count_words(char *input)
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
        } else if (*c == '|' && !in_double_quote && !in_single_quote) {
            count++;
        }
        c++;
    }
    return count + 1;
}

static char *next_pipe(char *input)
{
    int in_double_quote = 0;
    int in_single_quote = 0;
    char *c = input;
    while (*c != '\0') {
        if (*c == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (*c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (*c == '|' && !in_double_quote && !in_single_quote) {
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


char **ft_split_token(char *input)
{
    int count;
	char *end;
	int i;

	i = 0;
	count = count_words(input);
    char **split = (char **)malloc(sizeof(char *) * (count + 1));
    if (!split)
	{
        return (NULL);
	}
   	end = next_pipe(input);
    while (end != NULL) {
        split[i] = malloc(word_length(input, end) + 1);
        if (!split[i]) {
            return NULL;
        }
        ft_strncpy(split[i], input, end - input);
        split[i][end - input] = '\0';
        i++;
        input = end + 1;
        end = next_pipe(input);
    }
    split[i] = ft_strdup(input);
    if (!split[i])
        return NULL;
    split[i + 1] = NULL;
    return (split);
}