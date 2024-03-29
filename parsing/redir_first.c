/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:07:20 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 06:48:09 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**infile_first(char **realloc, char **new_tab, int *j)
{
	int	i;

	i = 0;
	while (realloc[i])
	{
		if (realloc[i][0] != '<' || (realloc[i][0] == '<' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[*j] = ft_strdup(realloc[i]);
		if (!new_tab[*j])
			exit_parent("parsing");
		*j += 1;
		i++;
	}
	return (new_tab);
}

char	**outfile_second(char **realloc, char **new_tab, int *j)
{
	int	i;

	i = 0;
	while (realloc[i])
	{
		if (realloc[i][0] != '>' || (realloc[i][0] == '>' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[*j] = ft_strdup(realloc[i]);
		if (!new_tab[*j])
			exit_parent("parsing");
		*j += 1;
		i++;
	}
	return (new_tab);
}

char	**redir_first(char **realloc)
{
	char	**new_tab;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_tab = ft_calloc_parent(sizeof(char *), \
		(ft_strlen_dtab(realloc) + 1), "parsing");
	new_tab = infile_first(realloc, new_tab, &j);
	new_tab = outfile_second(realloc, new_tab, &j);
	i = 0;
	while (realloc[i])
	{
		if ((realloc[i][0] == '<' && realloc[i][1]) || (realloc[i][0] == '>' \
			&& realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	new_tab[j] = 0;
	return (new_tab);
}
