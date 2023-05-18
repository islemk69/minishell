/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:10:02 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/19 01:10:55 by hel-ouar         ###   ########.fr       */
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

void	check_path_count(t_minishell *ms, char *tab, int *i, int *count)
{
	char	*tmp;
	char	*env;
	int		j;

	env = NULL;
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

int	dollar_d_quot(char *tab, int d_quot, int *count, int *i)
{
	if ((ft_strchr(tab, ' ') || d_quot) && tab[*i + 1] == '\"')
	{
		*count += 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	countchar(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		check_quote_dollar(tab[i], &s_quot, &d_quot);
		if (!is_expandable(tab, i, d_quot, s_quot))
		{
			count++;
			i++;
			continue ;
		}
		else if (tab[i] == '$')
		{
			if (dollar_d_quot(tab, d_quot, &count, &i))
				continue ;
			if (!special_dollar_count(tab, &i, &count))
				continue ;
			i++;
			check_path_count(ms, tab, &i, &count);
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}
