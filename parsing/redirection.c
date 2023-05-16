/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:11:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/14 08:15:10 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	**fill_stick(char **str, char **realloc2, int i, int k)
{
	int	u;
	int	p_int;
	int	token;

	while (str[++i])
	{
		p_int = 0;
		token = is_redir(str[i], false, '\0');
		if (!is_token_char(str[i][0]) && token)
		{
			u = 0;
			realloc2[k++] = strcpy_token(str[i], &p_int);
			while (++u <= token)
				realloc2[k++] = strcpy_token_2(str[i], &p_int);
		}
		else if (is_token_char(str[i][0]) && token > 1)
		{
			u = -1;
			while (++u < token)
				realloc2[k++] = strcpy_token_2(str[i], &p_int);
		}
		else
			realloc2[k++] = ft_strdup(str[i]);
	}
	return (realloc2[k] = 0, realloc2);
}

char	**fill_redir(char **str, char **realloc)
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
	realloc2 = fill_stick(space, realloc2, -1, 0);
	realloc = realloc_redir(realloc2);
	realloc = fill_redir(realloc2, realloc);
	realloc = redir_first(realloc);
	return (realloc);
}
