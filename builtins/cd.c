/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:19:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/17 18:04:00 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_cd(char **split, t_env **env)
{
	if (split[0] && !ft_strncmp(split[0], "cd\0", 3))
	{
		ft_printf("CD :%s\n", split[0]);
		if (!split[1])
		{
			if (chdir(ft_find_path(env, "HOME")) == -1)
			{
				g_global.g_status = 1;
				ft_dprintf(""RED"bash: cd: HOME not set\n"WHITE"");
			}
		}
		else if (chdir(split[1]) == -1 && split[1])
		{
			g_global.g_status = 1;
			ft_dprintf(""RED"bash: cd: %s: No such file or directory\n"WHITE"", split[1]);
		}
		return (1);
	}
	return (0);
}