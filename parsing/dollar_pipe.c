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

int	is_heredoc_name(char *tab, int d_quot, int s_quot, int j)
{
	if ((tab[j] == '<' && tab[j + 1] == '<' && !d_quot)
		|| (tab[j] == '<' && tab[j + 1] == '<' && !s_quot))
		return (1);
	return (0);
}

char	*fill_new(char *str, int s_quot, int d_quot, t_minishell *ms)
{
	char	*new;
	int		j;
	int		k;

	init_i_k(&j, &k);
	new = init_m_dollar(ms, str);
	while (check_quote_dollar(str[j], &s_quot, &d_quot))
	{
		if (is_heredoc_name(str, d_quot, s_quot, j))
		{
			while (str[j] && (str[j] != 32 || (!d_quot && !s_quot)))
			{
				new[k++] = str[j++];
				check_quote_dollar(str[j], &s_quot, &d_quot);
			}
		}
		else if (!is_expandable(str, j, d_quot, s_quot))
			new[k++] = str[j++];
		else if (str[j] == '$' && (!check_dollar_pipe(str, new, &j, &k)
				|| check_path_pipe(ms, new, ft_tmp_dollar(str, &j), &k)))
			j++;
		else
			new[k++] = str[j++];
	}
	return (new[k] = '\0', new);
}

char	**dollar_pipe(t_minishell *ms, int d_quot, int s_quot, char **new)
{
	int		i;

	i = 0;
	while (ms->parsed[i])
	{
		new[i] = fill_new(ms->parsed[i], d_quot, s_quot, ms);
		i++;
	}
	return (new[i] = 0, new);
}

// char *fill_new(char *str, int s_quot, int d_quot, t_minishell *ms)
// {
// 	char	*new;
// 	int		j;
// 	int		k;

// 	j = 0;
// 	k = 0;
// 	new = ft_calloc_parent(sizeof(char), (countchar_pipe(ms, 
// 			str, d_quot, s_quot) + 1), "parsing");
// 	while (check_quote_dollar(str[j], &s_quot, &d_quot))
// 	{
// 		if (is_heredoc_name(str, d_quot, s_quot, j))
// 		{
// 			while (str[j] && ((str[j] != 32 && !d_quot)
// 				|| (str[j] != 32 && !s_quot)))
// 			{
// 				new[k++] = str[j++];
// 				check_quote_dollar(str[j], &s_quot, &d_quot);
// 			}
// 			continue ;
// 		}
// 		else if (!is_expandable(str, j, d_quot, s_quot))
// 		{
// 			new[k++] = str[j++];
// 			continue ;
// 		}
// 		else if (str[j] == '$' && (!check_dollar_pipe(str, new, &j, &k) 
// 			|| check_path_pipe(ms, new, ft_tmp_dollar(str, &j), &k)))
// 			continue ;
// 		new[k++] = str[j++];
// 	}
// 	return (new[k] = 0, new);
// }