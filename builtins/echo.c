/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:34:30 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 17:16:43 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_is_nflag(char *string)
{
	int		i;

	i = 0;
	if (string[i] != '-' || !string[1])
		return (0);
	else
		i++;
	while (string[i] && string[i] == 'n')
		i++;
	if (string[i])
		return (0);
	else
		return (1);
}

int	built_in_echo(char **split)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (split[0] && !ft_strncmp(split[0], "echo\0", 4))
	{
		while (split[i] && ft_is_nflag(split[i]))
		{
			n_flag = true;
			i++;
		}
		while (split && split[i])
		{
			printf("%s", split[i]);
			if (split[i + 1])
				printf(" ");
			i++;
		}
		if (n_flag == false)
			printf("\n");
		g_global.g_status = 0;
		return (1);
	}
	return (0);
}