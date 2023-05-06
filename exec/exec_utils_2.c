/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 22:34:56 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rm_quote_last(char **cmds)
{
	char	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = quote(tmp);
		cmds++;
	}
}

int	open_here_doc(t_minishell *ms)
{
	char	**split;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (ms->parsed[i])
	{
		split = ft_split_token(ms->parsed[i], ' ');
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
			{
				tmp = split[j];
				split[j] = quote(tmp);
				if (!here_doc(ms, split[j] + 2, tmp))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_realloc_from_i(char **tab, int size, int i)
{
	char	**realloc;
	int		j;

	j = 0;
	realloc = ft_gc_malloc(sizeof(char *) * (size - i));
	i++;
	while (tab[i])
	{
		realloc[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	realloc[j] = 0;
	return (realloc);
}
