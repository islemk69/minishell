/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:18:53 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 06:42:42 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**realloc_redir(char **space)
{
	int		i;
	int		size;
	char	**realloc;

	i = 0;
	size = 0;
	while (space[i])
	{
		if ((is_token_char(space[i][0]) && !space[i][1])
			|| (is_token_char(space[i][0]) && is_token_char(space[i][1]) \
				&& !space[i][2]))
		{
			size++;
			i++;
		}
		else
			size++;
		i++;
	}
	realloc = ft_calloc_parent(sizeof(char *), (size + 1), "parsing");
	if (!realloc)
		return (NULL);
	return (realloc);
}

char	**realloc_stick(char **space)
{
	int		i;
	int		size;
	int		token;
	char	**realloc;

	i = 0;
	size = 0;
	token = 0;
	while (space[i])
	{
		token = is_redir(space[i], false, '\0');
		if (!is_token_char(space[i][0]) && token)
			size += token + 1;
		else if (is_token_char(space[i][0]) && token > 1)
			size += token;
		else
			size++;
		token = 0;
		i++;
	}
	realloc = ft_calloc_parent(sizeof(char *), (size + 1), "parsing");
	return (realloc);
}

int	check_double_token(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((is_token_char(str[i][0]) && !str[i + 1] && !str[i][1])
			|| (is_token_char(str[i][ft_strlen(str[i]) - 1]) && !str[i + 1])
			|| (is_token_char(str[i][ft_strlen(str[i]) - 1]) \
				&& is_token_char(str[i + 1][0])))
			return (0);
		i++;
	}
	return (1);
}

char	*strcpy_token(char *src, int *s_int)
{
	int		j;
	int		size;
	char	*sdup;
	int		save;

	save = *s_int;
	size = 0;
	j = 0;
	while (src[save] && !is_token_char(src[save]))
	{
		size++;
		save ++;
	}
	sdup = ft_calloc_parent(sizeof(char), (size + 1), "parsing");
	while (src[*s_int] && !is_token_char(src[*s_int]))
	{
		sdup[j] = src[*s_int];
		j++;
		*s_int += 1;
	}
	sdup[j] = 0;
	return (sdup);
}

char	*ft_strdup_token(const char *s1, char c)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (s1[i])
		i++;
	ptr = (void *)ft_gc_malloc(sizeof(const char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	ptr[0] = c;
	i = 0;
	while (s1[i])
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
