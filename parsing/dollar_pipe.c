/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 07:59:26 by hamza             #+#    #+#             */
/*   Updated: 2023/05/21 21:42:47 by ikaismou         ###   ########.fr       */
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
			exit_parent("parsing");
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

static int	check_path_pipe(t_minishell *ms, char *real, char *tmp, int *k)
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
	return (1);
}

int	is_heredoc_name(char *tab, int dbl_quot, int single_quot, int j)
{
	if ((tab[j] == '<' && tab[j + 1] == '<' && !dbl_quot)
		|| (tab[j] == '<' && tab[j + 1] == '<' && !single_quot))
		return (1);
	return (0);
}

char	*fill_new(char *str, int single_quot, int dbl_quot, t_minishell *ms)
{
	char	*new;
	int		j;
	int		k;

	init_i_k(&j, &k);
	new = init_m_dollar(ms, str);
	while (check_quote_dollar(str[j], &single_quot, &dbl_quot))
	{
		if (is_heredoc_name(str, dbl_quot, single_quot, j))
		{
			while (str[j] && (str[j] != 32 || (!dbl_quot && !single_quot)))
			{
				new[k++] = str[j++];
				check_quote_dollar(str[j], &single_quot, &dbl_quot);
			}
		}
		else if (!is_expandable(str, j, dbl_quot, single_quot))
			new[k++] = str[j++];
		else if (str[j] == '$' && (!check_dollar_pipe(str, new, &j, &k)
				|| check_path_pipe(ms, new, ft_tmp_dollar(str, &j), &k)))
			j++;
		else
			new[k++] = str[j++];
	}
	return (new[k] = '\0', new);
}

char	**dollar_pipe(t_minishell *ms, int dbl_quot, int single_quot, \
char **new)
{
	int		i;

	i = 0;
	while (ms->parsed[i])
	{
		new[i] = fill_new(ms->parsed[i], dbl_quot, single_quot, ms);
		i++;
	}
	return (new[i] = 0, new);
}
