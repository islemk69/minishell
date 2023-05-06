/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 22:24:59 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_token_quote(char *str, bool *in_quotes, char current_quote)
{
	if (*in_quotes && *str == current_quote)
	{
		*in_quotes = false;
		current_quote = '\0';
	}
	else if (!in_quotes)
	{
		*in_quotes = true;
		current_quote = *str;
	}
}

int	count_token(char *str, char c)
{
	int		count;
	bool	in_quotes;
	char	current_quote;

	count = 0;
	in_quotes = false;
	current_quote = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			check_token_quote(str, &in_quotes, current_quote);
		}
		else if (*str == c && !in_quotes)
			count++;
		str++;
	}
	return (count);
}

void	access_file2(t_minishell *ms)
{
	int		i;
	char	*tab2;

	i = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			ms->parsed[i] = quote(ms->parsed[i]);
			tab2 = ft_strjoin(".", ms->parsed[i] + 2);
			if (access(tab2, F_OK) != 0)
				error_exit(ms->parsed[i] + 2, \
					": No such file or directory\n", 1);
		}
		else
		{
			ms->parsed[i] = quote(ms->parsed[i]);
			if (access(ms->parsed[i] + 1, F_OK) != 0)
				error_exit(ms->parsed[i] + 1, \
					": No such file or directory\n", 1);
		}
		i++;
	}
}

void	access_file(char **tab, t_minishell *ms)
{
	int		i;
	char	*tab2;

	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
		{
			tab2 = ft_strjoin(".", tab[i] + 2);
			if (access(tab2, F_OK) != 0)
			{
				ms->infile_stra = tab[i] + 2;
				break ;
			}
		}
		else if (access(tab[i] + 1, F_OK) != 0)
		{
			ms->infile_stra = tab[i] + 1;
			break ;
		}
		i++;
	}
}
