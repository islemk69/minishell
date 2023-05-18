/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 07:59:26 by hamza             #+#    #+#             */
/*   Updated: 2023/05/19 01:01:19 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_dollar_pipe(char *tab, char *realloc, int *i, int *k)
{
	char	*tmp;

	if (tab[*i + 1] == '?')
	{
		tmp = ft_itoa(g_global.g_status);
		if (!tmp)
			exit_child(-1);
		while (*tmp)
		{
			realloc[(*k)++] = (*tmp);
			tmp++;
		}
		*i += 2;
		return (0);
	}
	return (1);
}

static void	check_path_pipe(t_minishell *ms, char *real, char *tmp, int *k)
{
	char	*dollar;
	int		j;

	j = 0;
	dollar = NULL;
	if (tmp[0])
	{	
		dollar = ft_find_path(&ms->head_env, tmp);
	}
	if (dollar != 0)
	{
		j = 0;
		while (dollar[j])
		{
			real[*k] = dollar[j];
			*k += 1;
			j++;
		}
	}
}

int	is_heredoc_name(char *tab, int d_quot, int s_quot, int j)
{
	if ((tab[j] == '<' && tab[j + 1] == '<' && !d_quot)
		|| (tab[j] == '<' && tab[j + 1] == '<' && !s_quot))
		return (1);
	return (0);
}

char	**dollar_pipe(t_minishell *ms, int d_quot, int s_quot)
{
	int		i;
	int		k;
	int		j;
	char	*tmp;
	char	**new;

	i = -1;
	new = ft_calloc_parent(sizeof(char *), \
		ft_strlen_dtab(ms->parsed) + 1, "parsing");
	while (ms->parsed[++i])
	{
		new[i] = ft_calloc_parent(sizeof(char), (countchar_pipe(ms, \
				ms->parsed[i], d_quot, s_quot) + 1), "parsing");
		j = 0;
		k = 0;
		while (ms->parsed[i][j])
		{
			check_quote_dollar(ms->parsed[i][j], &s_quot, &d_quot);
			if (is_heredoc_name(ms->parsed[i], d_quot, s_quot, j))
			{
				while (ms->parsed[i][j] && ((ms->parsed[i][j] != 32 && !d_quot)
					|| (ms->parsed[i][j] != 32 && !s_quot)))
				{
					new[i][k++] = ms->parsed[i][j++];
					check_quote_dollar(ms->parsed[i][j], &s_quot, &d_quot);
				}
				continue ;
			}
			if (!is_expandable(ms->parsed[i], i, d_quot, s_quot))
			{
				new[i][k++] = ms->parsed[i][j];
				continue ;
			}
			else if (ms->parsed[i][j] == '$')
			{
				if (!check_dollar_pipe(ms->parsed[i], new[i], &j, &k))
					continue ;
				tmp = ft_tmp_dollar(ms->parsed[i], &j);
				check_path_pipe(ms, new[i], tmp, &k);
				continue ;
			}
			new[i][k++] = ms->parsed[i][j++];
		}
		new[i][k] = 0;
	}
	return (new[i] = 0, new);
}
