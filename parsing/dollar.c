/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/05/08 15:45:22 by hel-ouar         ###   ########.fr       */
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

int	countchar(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;
	char	*env;

	count = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (tab[i] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (tab[i] == '$' && tab[i + 1] != '"' && tab[i + 1] != '\'' 
			&& tab[i + 1] != ' ' && tab[i + 1] != '$' && tab[i + 1] != 0 && s_quot == 0)
		{
			if (i != 0)
			{
				if (tab[i - 1] == '<')
				{
					count++;
					i++;
					continue;
				}
			}
			if (tab[i + 1] == '?')
			{
				count += ft_strlen(ft_itoa(g_global.g_status));
				i += 2;
				continue ;
			}
			i++;
			env = NULL;
			tmp = ft_gc_malloc(sizeof(char) * (size_tmp(tab, i) + 1));
			j = 0;
			while (tab[i] && tab[i] != '"' && tab[i] != '\''
				&& tab[i] != ' ' && tab[i] != '$'
				&& (ft_isalnum(tab[i]) || tab[i] == '_'))
			{
				tmp[j] = tab[i];
				i++;
				j++;
			}
			tmp[j] = 0;
			if (tmp[0])
				env = ft_find_path(&ms->head_env, tmp);
			if (env)
				count += ft_strlen(env);
			continue;
		}
		count++;
		i++;
	}
	d_quot = 0;
	s_quot = 0;
	return (count);
}

char	**dollar_exist(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	*tmp;
	int		flg = 0;
	char	*dollar;
	char	**realloc;
	//char *case = "$"
	
	k = 0;	
	i = 0;
	count = countchar(ms, tab, d_quot, s_quot);
	realloc = ft_gc_malloc(sizeof(char) * (1 + 1));
	realloc[0] = ft_gc_malloc(sizeof(char) * (count + 1));
	realloc[1] = 0;
	while (tab[i])
	{
		if (tab[i] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (tab[i] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (tab[i] == '$' && tab[i + 1] != '"' && tab[i + 1] != '\'' 
			&& tab[i + 1] != ' ' && tab[i + 1] != '$'  && tab[i + 1] != 0 && s_quot == 0)
		{
			if (i != 0)
			{
				if (tab[i - 1] == '<')
				{
					realloc[0][k] = tab[i];
					k++;
					i++;
					continue;
				}
			}
			if (tab[i + 1] == '?')
			{
				tmp = ft_itoa(g_global.g_status);
				while (*tmp)
				{
					realloc[0][k] = *tmp;
					k++;
					tmp++;
				}
				i += 2;
				continue ;
			}
			i++;
			tmp = ft_gc_malloc(sizeof(char) * (size_tmp(tab, i) + 1));
			dollar = NULL;
			j = 0;
			while (tab[i] && tab[i] != '"' && tab[i] != '\''
				&& tab[i] != ' ' && tab[i] != '$'
				&& (ft_isalnum(tab[i]) || tab[i] == '_'))
			{
				tmp[j] = tab[i];
				i++;
				j++;
			}
			tmp[j] = 0;
			if (tmp[0])
			{	
				dollar = ft_find_path(&ms->head_env, tmp);
			}
			if (dollar != 0)
			{
				flg = 1;
				j = 0;
				while (dollar[j])
				{
					realloc[0][k] = dollar[j];
					k++;
					j++;
				}
			}
			continue;
		}
		realloc[0][k] = tab[i];
		k++;
		i++;
	}
	realloc[0][k] = 0;
	if (flg)
		realloc = ft_split_token(realloc[0], ' ');
	return (realloc);
}

char **real_null(char **ms_parsed)
{
	int i = 0;
	int count = 0;
	char **new_ms;
	int j;
	while (ms_parsed[i])
	{
		if (ms_parsed[i][0])
			count++;
		i++;
	}
	new_ms = ft_gc_malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (ms_parsed[i])
	{
		if (ms_parsed[i][0])
		{
			new_ms[j] = ft_strdup(ms_parsed[i]);
			j++;
		}
		i++;
	}
	new_ms[j] = 0;
	return (new_ms);
}


void	check_dollar(t_minishell *ms)
{
	int	i;
	int	d_quot;
	int	s_quot;
	char **tmp;
	char **realloc;
	int j = 0;
	
	d_quot = 0;
	s_quot = 0;
	i = 0;
	int size = 0;
	j = 0;

	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			tmp = dollar_exist(ms, ms->parsed[i], d_quot, s_quot);
			while (tmp[j])
			{
				size++;
				j++;
			}
			i++;
			continue ;
		}
		size++;
		i++;
	}
	realloc = ft_gc_malloc(sizeof(char *) * (size + 1));
	i = 0;
	j = 0;
	int k =0;
	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			tmp = dollar_exist(ms, ms->parsed[i], d_quot, s_quot);
			while (tmp[j])
			{
				realloc[k] = ft_strdup(tmp[j]);
				j++;
				k++;
			}
			i++;
			continue ;
			//ms->parsed[i] = ft_strdup();
		}
		realloc[k] = ft_strdup(ms->parsed[i]);
		k++;
		i++;
	}
	realloc[k] = 0;
	if (realloc[0] && realloc[1])
		realloc = real_null(realloc);
	ms->parsed = realloc;
}