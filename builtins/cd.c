/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:19:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/21 14:34:22 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cd(char **split, t_env **env)
{
	if (!split[1])
	{
		if (chdir(ft_find_path(env, "HOME")) == -1)
		{
			g_global.g_status = 1;
			ft_dprintf("bash: cd: HOME not set\n");
			return (1);
		}
	}
	else if (split[2])
	{
		g_global.g_status = 1;
		ft_dprintf("bash: cd: too many arguments\n");
		return (1);
	}
	else if (chdir(split[1]) == -1 && split[1])
	{
		g_global.g_status = 1;
		print_error(split[1], ": No such file or directory\n");
		return (1);
	}
	return (0);
}

int	input_cd(char **split, t_env **env)
{
	t_env	*head;
	char	*pwd;
	char	*oldpwd;

	head = *env;
	if (split[0] && !ft_strncmp(split[0], "cd\0", 3))
	{
		oldpwd = getenv("OLDPWD");
		if (check_cd(split, env))
			return (1);
		pwd = getenv("PWD");
		while (head)
		{
			if (!ft_strncmp(head->key, "OLDPWD\0", 7))
				head->value = ft_strdup(oldpwd);
			if (!ft_strncmp(head->key, "PWD\0", 4))
				head->value = ft_strdup(pwd);
			head = head->next;
		}
		return (1);
	}
	return (0);
}
