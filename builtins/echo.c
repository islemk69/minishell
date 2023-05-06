/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:34:30 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 11:27:15 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_echo(char **split, int i)
{
	while (split[i])
	{
		if (split[i + 1])
			printf("%s ", split[i]);
		else
			printf("%s", split[i]);
		i++;
	}
}

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
		print_echo(split, i);
		if (!flg)
			printf("\n");
		g_global.g_status = 0;
		return (1);
	}
	return (0);
}
