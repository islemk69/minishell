/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:53:08 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/09 14:53:35 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_realloc_from_i(char **tab, int size, int i)
{
	char	**realloc;
	int		j;

	j = 0;
	realloc = ft_gc_malloc(sizeof(char *) * (size - i));
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
