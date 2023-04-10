/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/04/10 23:06:17 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	size_tmp(char *tab, int i)
{
	int	count;

	count = 0;
	while (tab[i] && tab[i] != '"' && tab[i] != '\'' && tab[i] != ' ')
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
		if (tab[i] == '$' && s_quot == 0)
		{
			i++;
			tmp = ft_gc_malloc(sizeof(char) * (size_tmp(tab, i) + 1));
			j = 0;
			while (tab[i] && tab[i] != '"' && tab[i] != '\'' && tab[i] != ' ')
			{
				tmp[j] = tab[i];
				i++;
				j++;
			}
			tmp[j] = 0;
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

char	*dollar_exist(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	*tmp;
	char	*dollar;
	char	*realloc;
	
	k = 0;	
	i = 0;
	count = countchar(ms, tab, d_quot, s_quot);
	realloc = ft_gc_malloc(sizeof(char) * (count + 1));
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
		if (tab[i] == '$' && s_quot == 0)
		{
			i++;
			tmp = ft_gc_malloc(sizeof(char) * (size_tmp(tab, i) + 1));
			dollar = NULL;
			j = 0;
			while (tab[i] && tab[i] != '"' && tab[i] != '\'' && tab[i] != ' ')
			{
				tmp[j] = tab[i];
				i++;
				j++;
			}
			tmp[j] = 0;
			dollar = ft_find_path(&ms->head_env, tmp);
			if (dollar != 0)
			{
				j = 0;
				while (dollar[j])
				{
					realloc[k] = dollar[j];
					k++;
					j++;
				}
			}
			continue;
		}
		realloc[k] = tab[i];
		k++;
		i++;
	}
	realloc[k] = 0;
	return (realloc);
}

void	check_dollar(t_minishell *ms)
{
	int	i;
	int	d_quot;
	int	s_quot;
	
	d_quot = 0;
	s_quot = 0;
	i = 0;
	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
			ms->parsed[i] = ft_strdup(dollar_exist(ms, ms->parsed[i], \
			d_quot, s_quot));
		i++;
	}
}