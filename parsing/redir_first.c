/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:07:20 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 20:06:01 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**infile_first(char **realloc, char **new_tab, int *j)
{
	int i = 0;
	
	while (realloc[i])
	{
		if (realloc[i][0] != '<' || (realloc[i][0] == '<' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[*j] = ft_strdup(realloc[i]);
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
	new_tab = (char **)ft_gc_malloc(sizeof(char *) * \
		(ft_strlen_dtab(realloc) + 1));
	new_tab = infile_first(realloc, new_tab, &j);
	//printf("%d\n", j);
	while (realloc[i])
	{
		if (realloc[i][0] != '>' || (realloc[i][0] == '>' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
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
