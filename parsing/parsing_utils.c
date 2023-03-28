/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:27:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/28 21:07:07 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char** split_string(char* str) {
    int len = strlen(str);
    char** result = (char**) malloc((len + 1) * sizeof(char*));
    int i = 0;
    int j = 0;
    int in_quotes = 0;
    char quote_type = '\0';
	int result_len = 0;

    while (i < len) {
        if (str[i] == '\'' || str[i] == '\"') {
            if (in_quotes && str[i] == quote_type) {
                in_quotes = 0;
            } else if (!in_quotes) {
                in_quotes = 1;
                quote_type = str[i];
                i++;
            }
        }

        if (!in_quotes && (str[i] == ' ' || str[i] == '\t')) {
            if (i > j) {
                int word_len = i - j;
                char* word = (char*) malloc((word_len + 1) * sizeof(char));
                strncpy(word, str + j, word_len);
                word[word_len] = '\0';
                result[result_len++] = word;
            }
            j = i + 1;
        }

        i++;
    }

    if (i > j) {
        int word_len = i - j;
        char* word = (char*) malloc((word_len + 1) * sizeof(char));
        strncpy(word, str + j, word_len);
        word[word_len] = '\0';
        result[result_len++] = word;
    }

    result[result_len] = NULL;

    return result;
}