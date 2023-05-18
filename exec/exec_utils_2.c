/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:53:08 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 05:48:02 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_realloc_from_i(char **tab, int size, int i)
{
	char	**realloc;
	int		j;

	j = 0;
	realloc = ft_calloc_child(sizeof(char *), (size - i));
	i++;
	while (tab[i])
	{
		tab[i] = quote(tab[i]);
		realloc[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	realloc[j] = 0;
	return (realloc);
}

int	count_token(char *str, char c, bool in_quotes, char current_quote)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (in_quotes && *str == current_quote)
			{
				in_quotes = false;
				current_quote = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = true;
				current_quote = *str;
			}
		}
		else if (*str == c && !in_quotes)
			count++;
		str++;
	}
	return (count);
}

char	**tab_copy(char **tab)
{
	int		i;
	char	**head;

	i = 0;
	head = ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(tab) + 1));
	while (tab[i])
	{
		head[i] = ft_strdup(tab[i]);
		i++;
	}
	return (head);
}
