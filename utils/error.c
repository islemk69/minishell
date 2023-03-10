/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:20:42 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/09 17:23:44 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		return ;
}

int	is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	if (str[i] == 0)
		return (1);
	return (0);
}