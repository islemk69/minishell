/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/05/07 23:14:40 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**do_real_null(char **ms_parsed, int count)
{
	char	**new_ms;
	int		j;
	int		i;

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

char	**real_null(char **ms_parsed)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ms_parsed[i])
	{
		if (ms_parsed[i][0])
			count++;
		i++;
	}
	return (do_real_null(ms_parsed, count));
}

int	size_new_parsed(t_minishell *ms)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			j = 0;
			ms->realloc = change_parsed_dollar(ms, ms->parsed[i], 0, 0);
			while (ms->realloc[j])
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
	return (i);
}

char	**realloc_dollar(t_minishell *ms, char **realloc, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ms->parsed[i])
	{
		if (ft_strnstr(ms->parsed[i], "$", ft_strlen(ms->parsed[i])) != 0)
		{
			j = 0;
			ms->realloc = change_parsed_dollar(ms, ms->parsed[i], 0, 0);
			while (ms->realloc[j])
			{
				realloc[size] = ft_strdup(ms->realloc[j]);
				j++;
				size++;
			}
			i++;
			continue ;
		}
		realloc[size] = ft_strdup(ms->parsed[i]);
		size++;
		i++;
	}
	return (realloc[size] = 0, realloc);
}

void	check_dollar(t_minishell *ms)
{
	char	**realloc;

	realloc = ft_gc_malloc(sizeof(char *) * (size_new_parsed(ms) + 1));
	realloc = realloc_dollar(ms, realloc, 0);
	if (realloc[0] && realloc[1])
		realloc = real_null(realloc);
	ms->parsed = realloc;
}
