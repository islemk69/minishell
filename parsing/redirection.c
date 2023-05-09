/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:11:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 18:07:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token_char(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
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

char	**redir_first(char **realloc)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_tab = (char **)ft_gc_malloc(sizeof(char *) * \
		(ft_strlen_dtab(realloc) + 1));
	while (realloc[i])
	{
		if (realloc[i][0] != '<' || (realloc[i][0] == '<' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	i = 0;
	while (realloc[i])
	{
		if (realloc[i][0] != '>' || (realloc[i][0] == '>' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	i = 0;
	while (realloc[i])
	{
		if ((realloc[i][0] == '<' && realloc[i][1]) || (realloc[i][0] == '>' \
			&& realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	new_tab[j] = 0;
	return (new_tab);
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

int	is_redir(char *str)
{
	int		count;
	bool	in_quotes;
	char	current_quote;
	int		i;

	i = 0;
	count = 0;
	in_quotes = false;
	current_quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quotes && str[i] == current_quote)
			{
				in_quotes = false;
				current_quote = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = true;
				current_quote = str[i];
			}
		}
		else if ((str[i] == '<' || str[i] == '>') && !in_quotes)
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' \
				&& str[i + 1] == '>'))
				i++;
			count++;
		}
		i++;
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
		token = is_redir(space[i]);
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

char	*strcpy_token_2(char *src, int *s_int, int mod)
{
	int		j;
	int		size;
	char	*sdup;
	int		save;
	int		d_quot;
	int		s_quot;

	(void)mod;
	d_quot = 0;
	s_quot = 0;
	save = *s_int;
	size = 0;
	while (is_token_char(src[save]))
	{
		size++;
		save++;
	}
	while (src[save])
	{
		if (src[save] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (src[save] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (is_token_char(src[save]) && (!d_quot && !s_quot))
			break ;
		size++;
		save++;
	}
	sdup = (char *)ft_gc_malloc(sizeof(char) * (size + 1));
	j = 0;
	while (is_token_char(src[*s_int]))
	{
		sdup[j] = src[*s_int];
		j++;
		*s_int += 1;
	}
	s_quot = 0;
	d_quot = 0;
	while (src[*s_int])
	{
		if (src[*s_int] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (src[*s_int] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (is_token_char(src[*s_int]) && (!d_quot && !s_quot))
			break ;
		sdup[j] = src[*s_int];
		j++;
		*s_int += 1;
	}
	sdup[j] = 0;
	return (sdup);
}

char	*extract_dollard(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*realloc;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] != '$')
		i++;
	if (str[0] == '\"' || str[0] == '\'')
		return (str);
	while (str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '$')
		i++;
	j = i;
	while (str[i])
	{
		size++;
		i++;
	}
	i = 0;
	realloc = ft_gc_malloc(sizeof(char) * (size + 1));
	while (str[j])
	{
		realloc[i] = str[j];
		j++;
		i++;
	}
	realloc[i] = 0;
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
		token = is_redir(str[i]);
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
	return (realloc);
}
