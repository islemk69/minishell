/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:10:02 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/09 21:44:16 by hel-ouar         ###   ########.fr       */
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
	}
	return (count);
}

void	check_path_count(t_minishell *ms, char *tab, int *i, int *count)
{
	char	*tmp;
	char	*env;
	int		j;

	env = NULL;
	tmp = ft_gc_malloc(sizeof(char) * (size_tmp(tab, *i) + 1));
	j = 0;
	while (tab[*i] && tab[*i] != '"' && tab[*i] != '\''
		&& tab[*i] != ' ' && tab[*i] != '$'
		&& (ft_isalnum(tab[*i]) || tab[*i] == '_'))
	{
		tmp[j] = tab[*i];
		*i += 1;
		j++;
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

int	countchar(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		check_quote_dollar(tab[i], &s_quot, &d_quot);
		if (tab[i] == '$' && tab[i + 1] != '$' && tab[i + 1] != 32 \
			&& tab[i + 1] != 0 && s_quot == 0)
		{
			if ((ft_strchr(tab, ' ') || d_quot) && tab[i + 1] == '\"')
			{
				count++;
				i++;
				continue ;
			}
			if (!special_dollar_count(tab, &i, &count))
				continue ;
			i++;
			check_path_count(ms, tab, &i, &count);
			continue ;
		}
		count++;
		i++;
	}
	d_quot = 0;
	s_quot = 0;
	return (count);
}
