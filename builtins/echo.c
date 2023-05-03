/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:34:30 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/03 14:07:19 by ikaismou         ###   ########.fr       */
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
		{
			g_global.g_status = 0;
			return (printf("\n"), 1);
		}
		if (!ft_strncmp(split[1], "-n\0", 3))
		{
			i++;
			flg = 1;
		}
		while (split[i])
		{
			if (split[i + 1])
				printf("%s ", split[i]);
			else
				printf("%s", split[i]);
			i++;
		}
		if (!flg)
			printf("\n");
		g_global.g_status = 0;
		return (1);
	}
	return (0);
}