/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/18 17:10:56 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in_pwd(char **split)
{
	char *str;
	
	if (split[0] && !split[1] && !ft_strncmp(split[0], "pwd\0", 4))
	{
		str = getcwd(0, 0);
		if (!str)
		{
			perror("getcwd()");
			g_global.g_status = 1;
		}
		ft_printf("%s\n", str);
		return (1);
	}
	return (0);
}