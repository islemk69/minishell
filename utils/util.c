/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:37:56 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 05:33:31 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_i_k(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

int	size_file_name_simple(t_minishell *ms)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
			count++;
		i++;
	}
	return (count);
}

int	size_file_name_pipe(t_minishell *ms)
{
	char	**split;
	int		j;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ms->parsed[i])
	{
		split = ft_split_space(ms->parsed[i]);
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	exit_child(int i)
{
	ft_gc_free_all();
	exit(i);
}

void	exit_parent(char *str)
{
	ft_gc_free_all();
	perror(str);
}
