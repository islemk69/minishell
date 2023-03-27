/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:19:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/27 14:23:37 by ikaismou         ###   ########.fr       */
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
				ft_printf("erreur a mettre chdir\n");
		}
		else if (chdir(split[1]) == -1 && split[1]) 
			ft_printf("erreur a mettre chdir\n");
		return (1);
	}
	return (0);
}