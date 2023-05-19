/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:49:28 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/19 00:50:34 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_special_dollar(char *tab, char **realloc, int *i, int *k)
{
	char	*tmp;

	if (*i != 0)
	{
		if (tab[0] == '<' && tab[1] == '<')
		{
			realloc[0][*k] = tab[*i];
			*k += 1;
			*i += 1;
			return (0);
		}
	}
	if (tab[*i + 1] == '?')
	{
		tmp = ft_itoa(g_global.g_status);
		while (*tmp)
		{
			realloc[0][*k] = *tmp;
			*k += 1;
			tmp++;
		}
		*i += 2;
		return (0);
	}
	return (1);
}

char	*ft_tmp_dollar(char *tab, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	*i += 1;
	tmp = ft_calloc_parent(sizeof(char), (size_tmp(tab, *i) + 1), "parsing");
	while (tab[*i] && tab[*i] != '"' && tab[*i] != '\''
		&& tab[*i] != ' ' && tab[*i] != '$'
		&& (ft_isalnum(tab[*i]) || tab[*i] == '_'))
	{
		tmp[j] = tab[*i];
		*i += 1;
		j++;
		if (j == 1 && ft_isdigit(tab[(*i) - 1]))
			break ;
	}
	tmp[j] = 0;
	return (tmp);
}

int	check_path_dollar(t_minishell *ms, char **realloc, char *tmp, int *k)
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
			realloc[0][*k] = dollar[j];
			*k += 1;
			j++;
		}
		ms->flg = 1;
		return (1);
	}
	return (0);
}

void	change_dollar(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	char	*tmp;
	int		i;
	int		k;

	init_i_k(&i, &k);
	while (tab[i])
	{
		check_quote_dollar(tab[i], &s_quot, &d_quot);
		if (!is_expandable(tab, i, d_quot, s_quot))
			ms->change_dollar[0][k++] = tab[i++];
		else if (tab[i] == '$')
		{
			if ((ft_strchr(tab, ' ') || d_quot) && tab[i + 1] == '\"')
			{
				ms->change_dollar[0][k++] = tab[i++];
				continue ;
			}
			if (!change_special_dollar(tab, ms->change_dollar, &i, &k))
				continue ;
			tmp = ft_tmp_dollar(tab, &i);
			check_path_dollar(ms, ms->change_dollar, tmp, &k);
		}
		else
			ms->change_dollar[0][k++] = tab[i++];
	}
}

// void	change_dollar(t_minishell *ms, char *tab, int d_quot, int s_quot)
// {
// 	char	*tmp;
// 	int		i;
// 	int		k;

// 	init_i_k(&i, &k);
// 	while (tab[i])
// 	{
// 		check_quote_dollar(tab[i], &s_quot, &d_quot);
// 		if (!is_expandable(tab, i, d_quot, s_quot))
// 		{
// 			ms->change_dollar[0][k++] = tab[i++];
// 			continue ;
// 		}
// 		else if (tab[i] == '$')
// 		{
// 			if ((ft_strchr(tab, ' ') || d_quot) && tab[i + 1] == '\"')
// 			{
// 				ms->change_dollar[0][k++] = tab[i++];
// 				continue ;
// 			}
// 			if (!change_special_dollar(tab, ms->change_dollar, &i, &k))
// 				continue ;
// 			tmp = ft_tmp_dollar(tab, &i);
// 			check_path_dollar(ms, ms->change_dollar, tmp, &k);
// 			continue ;
// 		}
// 		ms->change_dollar[0][k++] = tab[i++];
// 	}
// 	ms->change_dollar[0][k] = 0;
// }

char	**change_parsed_dollar(t_minishell *ms, char *tab, \
	int d_quot, int s_quot)
{
	ms->flg = 0;
	ms->change_dollar = ft_calloc_parent(sizeof(char *), (1 + 1), "parsing");
	ms->change_dollar[0] = ft_calloc_parent(sizeof(char), \
		(countchar(ms, tab, d_quot, s_quot) + 1), "parsing");
	ms->change_dollar[1] = 0;
	change_dollar(ms, tab, d_quot, s_quot);
	ms->change_dollar[0][ft_strlen(ms->change_dollar[0])] = 0;
	if (ms->flg)
	{
		ms->change_dollar = ft_split_space(ms->change_dollar[0]);
		if (!ms->change_dollar)
			exit_parent("parsing");
	}
	return (ms->change_dollar);
}
