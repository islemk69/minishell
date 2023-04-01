/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 05:32:39 by ikaismou         ###   ########.fr       */
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
			perror("getcwd()");
		return (1);
	}
	return (0);
}