/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:34:30 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/28 13:55:12 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in_echo(char **split)
{
	int	i;
	int	flg;
	
	i = 1;
	flg = 0;
	if (split[0] && !ft_strncmp(split[0], "echo\0", 4))
	{
		if (!split[1] || !split[1][0])
			return (ft_printf("\n"), 1);
		if (!ft_strncmp(split[1], "-n\0", 3))
		{
			i++;
			flg = 1;
		}
		while (split[i])
		{
			if (split[i + 1])
				ft_printf("%s ", split[i]);
			else
				ft_printf("%s", split[i]);
			i++;
		}
		if (!flg)
			ft_printf("\n");
		return (1);
	}
	return (0);
}