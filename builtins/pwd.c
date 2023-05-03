/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/02 21:58:03 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in_pwd(char **split)
{
	char *str;
	
	if (split[0] && !ft_strncmp(split[0], "pwd\0", 4))
	{
		str = getcwd(0, 0);
		if (!str)
		{
			g_global.g_status = 1;
			perror("getcwd()");
		}
		printf("%s\n", str);
		g_global.g_status = 0;
		return (1);
	}
	return (0);
}