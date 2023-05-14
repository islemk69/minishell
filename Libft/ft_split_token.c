/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:17:46 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/14 07:50:25 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *input, char sep)
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
		else if (*c == sep && !in_double_quote && !in_single_quote)
			count++;
		c++;
	}
	return (count + 1);
}

static char	*next_pipe(char *input, char sep)
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
		else if (*c == sep && !in_double_quote && !in_single_quote)
			return (c);
		c++;
	}
	return (NULL);
}

static int	word_length(char *start, char *end)
{
	int		in_quote;
	char	*c;
	int		size;

	in_quote = 0;
	c = start;
	while (c < end)
	{
		if (*c == '\"')
			in_quote = !in_quote;
		c++;
	}
	if (in_quote)
		size = (end - start) - 2 + 1;
	else
		size = (end - start) - 0 + 1;
	return (size);
}

char	**no_null(char **tab)
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
	tab2 = (char **)ft_gc_malloc(sizeof(char *) * (j + 1));
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

char	**ft_split_token(char *input, char sep)
{
	int		count;
	char	*end;
	int		i;
	char	**split;

	i = 0;
	count = count_words(input, sep);
	split = (char **)ft_gc_malloc(sizeof(char *) * (count + 1));
	end = next_pipe(input, sep);
	while (end != NULL)
	{
		split[i] = ft_gc_malloc(word_length(input, end) + 1);
		if (!split[i])
			return (NULL);
		ft_strncpy(split[i], input, end - input);
		split[i][end - input] = '\0';
		i++;
		input = end + 1;
		end = next_pipe(input, sep);
	}
	split[i] = ft_strdup(input);
	if (!split[i])
		return (NULL);
	split[i + 1] = NULL;
	return (no_null(split));
}
