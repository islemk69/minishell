/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/05/06 17:11:36 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	size_tmp(char *tab, int i)
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

static int	countchar(t_minishell *ms, char *tab, int d_quot, int s_quot)
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
			&& tab[i + 1] != ' ' && tab[i + 1] != '$' && s_quot == 0)
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

char	*dollar_here_doc(t_minishell *ms, char *tab, int d_quot, int s_quot)
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
		if (tab[i] == '$' && tab[i + 1] != '"' && tab[i + 1] != '\'' 
			&& tab[i + 1] != ' ' && tab[i + 1] != '$' && s_quot == 0)
		{
			if (i != 0)
			{
				if (tab[i - 1] == '<')
				{
					realloc[k] = tab[i];
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
					realloc[k] = *tmp;
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
			//ft_printf("tmp : %s\n", tmp);
			if (tmp[0])
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