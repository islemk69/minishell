/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:27:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 03:13:19 by ikaismou         ###   ########.fr       */
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
