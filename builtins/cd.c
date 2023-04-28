/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:19:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/28 14:17:55 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_cd(char **split, t_env **env)
{
	if (split[0] && !ft_strncmp(split[0], "cd\0", 3))
	{
		if (!split[1])
		{
			if (chdir(ft_find_path(env, "HOME")) == -1)
			{
				g_global.g_status = 1;
				ft_dprintf(""RED"bash: cd: HOME not set\n"WHITE"");
			}
		}
		else if (split[2])
			ft_dprintf(""RED"bash: cd: too many arguments\n"WHITE"");
		else if (chdir(split[1]) == -1 && split[1])
		{
			g_global.g_status = 1;
			ft_dprintf(""RED"bash: cd: %s: No such file or directory\n"WHITE"", split[1]);
		}
		return (1);
	}
	return (0);
}