/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:10:02 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/21 21:17:48 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	size_tmp(char *tab, int i)
{
	int	count;

	count = 0;
	while (tab[i] && tab[i] != '"' && tab[i] != '\''
		&& tab[i] != ' ' && tab[i] != '$'
		&& (ft_isalnum(tab[i]) || tab[i] == '_'))
	{
		count++;
		i++;
		if (count == 1 && ft_isdigit(tab[i - 1]))
			break ;
	}
	return (count);
}

int	check_path_count(t_minishell *ms, char *tab, int *i, int *count)
{
	char	*tmp;
	char	*env;
	int		j;

	env = NULL;
	*i += 1;
	tmp = ft_calloc_parent(sizeof(char), (size_tmp(tab, *i) + 1), "parsing");
	j = 0;
	while (tab[*i] && tab[*i] != '"' && tab[*i] != '\'' && tab[*i] != ' ' \
		&& tab[*i] != '$' && (ft_isalnum(tab[*i]) || tab[*i] == '_'))
	{
		tmp[j] = tab[*i];
		*i += 1;
		j++;
		if (j == 1 && ft_isdigit(tab[(*i) - 1]))
			break ;
	}
	tmp[j] = 0;
	if (tmp[0])
		env = ft_find_path(&ms->head_env, tmp);
	if (env)
		*count += ft_strlen(env);
	return (1);
}

int	special_dollar_count(char *tab, int *i, int *count)
{
	if (*i != 0)
	{
		if (tab[0] == '<' && tab[1] == '<')
		{
			*count += 1;
			*i += 1;
			return (0);
		}
	}
	if (tab[*i + 1] == '?')
	{
		*count += ft_strlen(ft_itoa(g_global.g_status));
		*i += 2;
		return (0);
	}
	return (1);
}

int	dollar_d_quot(char *tab, int dbl_quot, int *count, int *i)
{
	if ((ft_strchr(tab, ' ') || dbl_quot) && tab[*i + 1] == '\"')
	{
		*count += 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	countchar(t_minishell *ms, char *tab, int dbl_quot, int single_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		check_quote_dollar(tab[i], &single_quot, &dbl_quot);
		if (!is_expandable(tab, i, dbl_quot, single_quot))
		{
			count++;
			i++;
			continue ;
		}
		else if (tab[i] == '$' && (dollar_d_quot(tab, dbl_quot, &count, &i)
				|| !special_dollar_count(tab, &i, &count)))
			continue ;
		else if (tab[i] == '$' && check_path_count(ms, tab, &i, &count))
			continue ;
		count++;
		i++;
	}
	return (count);
}
