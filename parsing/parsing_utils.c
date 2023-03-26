/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:27:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/26 23:28:40 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] != ' '
			&& str[i + 1] != '\t' && str[i + 1] != '\0')
			count++;
		i++;
	}
	if (str[0] != '\0')
		count++;
	return (count);
}

static int	word_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if ((str[i] == '\"' || str[i] == '\'') && len == 0)
		{
			len++;
			i++;
			while (str[i] && str[i] != str[i - 1])
			{
				len++;
				i++;
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*copy_word(char *str, int i, int len)
{
	char	*word;

	word = (char*)ft_gc_malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, &str[i], len);
	word[len] = '\0';
	return (word);
}

char	**split_string(char *str)
{
	int		i;
	int		j;
	int		words;
	char	**result;

	words = count_words(str);
	result = (char**)ft_gc_malloc(sizeof(char*) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			result[j] = copy_word(str, i, word_len(str, i));
			if (!result[j])
				return (NULL);
			j++;
			i += word_len(str, i);
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}