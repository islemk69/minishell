/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:27:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/31 13:39:18 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
    words = ft_gc_malloc((num_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
    int word_index = 0;

    // Construit chaque mot et l'ajoute au tableau
    i = 0;
    char *cur_word = ft_gc_malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cur_word)
		return (NULL);
    int cur_word_len = 0;
    in_quotes = 0;
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
            if (cur_word_len > 0)
            {
                cur_word[cur_word_len] = '\0';
                words[word_index++] = cur_word;
                cur_word = ft_gc_malloc((ft_strlen(str) + 1) * sizeof(char));
				if (!cur_word)
					return (NULL);
                cur_word_len = 0;
            }
        }
        else
        {
            cur_word[cur_word_len++] = c;
        }
        i++;
    }

    if (cur_word_len > 0)
    {
        cur_word[cur_word_len] = '\0';
        words[word_index++] = cur_word;
    }
    words[word_index] = NULL;
    return words;
}
// char** split_string(char* str) {
//     int len = strlen(str);
//     char** result = (char**) malloc((len + 1) * sizeof(char*));
//     int i = 0;
//     int j = 0;
//     int in_quotes = 0;
//     char quote_type = '\0';
// 	int result_len = 0;

//     while (i < len) {
//         if (str[i] == '\'' || str[i] == '\"') {
//             if (in_quotes && str[i] == quote_type) {
//                 in_quotes = 0;
//             } else if (!in_quotes) {
//                 in_quotes = 1;
//                 quote_type = str[i];
//                 i++;
//             }
//         }

//         if (!in_quotes && (str[i] == ' ' || str[i] == '\t')) {
//             if (i > j) {
//                 int word_len = i - j;
//                 char* word = (char*) malloc((word_len + 1) * sizeof(char));
//                 strncpy(word, str + j, word_len);
//                 word[word_len] = '\0';
//                 result[result_len++] = word;
//             }
//             j = i + 1;
//         }

//         i++;
//     }

//     if (i > j) {
//         int word_len = i - j;
//         char* word = (char*) malloc((word_len + 1) * sizeof(char));
//         strncpy(word, str + j, word_len);
//         word[word_len] = '\0';
//         result[result_len++] = word;
//     }

//     result[result_len] = NULL;

//     return result;
// }