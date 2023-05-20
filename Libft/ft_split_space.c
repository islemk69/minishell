/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:05:46 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/20 07:06:47 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *input)
{
	int		count;
	int		in_double_quote;
	int		in_single_quote;
	char	*c;

	count = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	c = input;
	while (*c != '\0')
	{
		if (*c == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*c == ' ' || *c == '\t') \
			&& !in_double_quote && !in_single_quote)
			count++;
		c++;
	}
	return (count + 1);
}

static char	*next_pipe(char *input)
{
	int		in_double_quote;
	int		in_single_quote;
	char	*c;

	in_double_quote = 0;
	in_single_quote = 0;
	c = input;
	while (*c != '\0')
	{
		if (*c == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*c == ' ' || *c == '\t') \
			&& !in_double_quote && !in_single_quote)
			return (c);
		c++;
	}
	return (NULL);
}

static char	**no_null(char **tab, int mod)
{
	char	**tab2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i][0])
			j++;
		i++;
	}
	if (!mod)
		tab2 = ft_calloc_parent(sizeof(char *), (j + 1), "");
	else
		tab2 = ft_calloc_child(sizeof(char *), (j + 1));
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i][0])
			tab2[j++] = ft_strdup(tab[i]);
		i++;
	}
	return (tab2[j] = 0, tab2);
}

char	**init_split(int mod, int count)
{
	char	**split;

	if (!mod)
		split = ft_calloc_parent(sizeof(char *), (count + 1), "");
	else
		split = ft_calloc_child(sizeof(char *), (count + 1));
	return (split);
}

char	**ft_split_space(char *input, int mod)
{
	int		count;
	char	*end;
	int		i;
	char	**split;

	i = 0;
	count = count_words(input);
	split = init_split(mod, count);
	end = next_pipe(input);
	while (end != NULL)
	{
		split[i] = ft_gc_malloc(word_length(input, end) + 1);
		if (!split[i])
			return (NULL);
		ft_strncpy(split[i], input, end - input);
		split[i++][end - input] = '\0';
		input = end + 1;
		end = next_pipe(input);
	}
	split[i] = ft_strdup(input);
	if (!split[i])
		return (NULL);
	return (split[i + 1] = NULL, no_null(split, mod));
}
