/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:11:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 19:45:27 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
	sdup = (char *)ft_gc_malloc(sizeof(char) * (size + 1));
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
	realloc = ft_gc_malloc(sizeof(char *) * (size + 1));
	if (!realloc)
		return (NULL);
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

int	is_redir(char *str, bool in_quotes, char current_quote)
{
	int		count;

	count = 0;
	while (*str != '\0')
	{
		if ((*str == '\'' || *str == '\"')
			&& (!in_quotes || *str == current_quote))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				current_quote = *str;
			else
				current_quote = '\0';
		}
		else if ((*str == '<' || *str == '>') && !in_quotes)
		{
			if ((*str == '<' && *(str + 1) == '<')
				|| (*str == '>' && *(str + 1) == '>'))
				str++;
			count++;
		}
		str++;
	}
	return (count);
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
	realloc = ft_gc_malloc(sizeof(char *) * (size + 1));
	return (realloc);
}

char	**fill_stick(char **str, char **realloc2)
{
	int i = 0;
	int k = 0;
	int u = 0;
	int	s_int = 0;
	int token = 0;
	while (str[i])
	{
		s_int = 0;
		token = is_redir(str[i], false, '\0');
		if (!is_token_char(str[i][0]) && token)
		{
			u = 1;
			realloc2[k] = strcpy_token(str[i], &s_int);
			k++;
			while (u <= token)
			{
				realloc2[k] = strcpy_token_2(str[i], &s_int, 0);
				k++;
				u++;
			}
		}
		else if (is_token_char(str[i][0]) && token > 1)
		{
			u = 0;
			while (u < token)
			{
				realloc2[k] = strcpy_token_2(str[i], &s_int, 1);
				k++;
				u++;
			}
		}
		else
		{
			realloc2[k] = ft_strdup(str[i]);
			k++;
		}
		token = 0;
		i++;
	}
	realloc2[k] = 0;
	return (realloc2);
}

char **fill_redir(char **str, char **realloc)
{
	int	i;
	int	k;
	
	i = 0;
	k = 0;
	while (str[i])
	{
		if ((is_token_char(str[i][0]) && !str[i][1]) \
			|| (is_token_char(str[i][0]) && is_token_char(str[i][1]) \
				&& !str[i][2]))
		{
			realloc[k] = ft_strjoin_gnl(str[i], str[i + 1]);
			i += 2;
			k++;
			continue ;
		}
		realloc[k] = ft_strdup(str[i]);
		k++;
		i++;
	}
	realloc[k] = 0;
	return (realloc);
}

char	**redirection(char **space)
{
	char	**realloc;
	char	**realloc2;

	if (!check_double_token(space))
		return (ft_dprintf(""RED"Error token\n"WHITE""), NULL);
	realloc2 = realloc_stick(space);
	realloc2 = fill_stick(space, realloc2);
	realloc = realloc_redir(realloc2);
	realloc = fill_redir(realloc2, realloc);
	realloc = redir_first(realloc);
	return (realloc);
}
