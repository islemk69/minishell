/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:53:08 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 05:48:02 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_realloc_from_i(char **tab, int size, int i)
{
	char	**realloc;
	int		j;

	j = 0;
	realloc = ft_calloc_child(sizeof(char *), (size - i));
	i++;
	while (tab[i])
	{
		tab[i] = quote(tab[i]);
		realloc[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	realloc[j] = 0;
	return (realloc);
}
