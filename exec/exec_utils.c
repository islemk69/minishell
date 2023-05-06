/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 21:26:36 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_path(t_minishell *ms)
{
	char	*path;

	path = ft_find_path(&ms->head_env, "PATH");
	if (!path)
	{
		ms->path_env = NULL;
		return (0);
	}
	ms->path_env = ft_split(path, ':');
	if (!ms->path_env)
		return (0);
	return (1);
}

int	check_command_special(t_minishell *ms, char *input_cmd)
{
	struct stat	info;

	if (access(input_cmd, F_OK) != 0)
		return (ms->path_cmd = input_cmd, 1);
	if (stat(input_cmd, &info) == 0 && S_ISDIR(info.st_mode))
	{
		print_error(input_cmd, ": Is a directory\n");
		exit(126);
	}
	else
	{
		if (access(input_cmd, F_OK) != 0)
		{
			print_error(input_cmd, ": No such file or directory\n");
			exit(127);
		}
		if (access(input_cmd, X_OK | R_OK) != 0)
		{
			print_error(input_cmd, ": Permission denied\n");
			exit (126);
		}
		return (ms->path_cmd = input_cmd, 1);
	}
	return (0);
}

int	check_cmd_access(t_minishell *ms, char *input_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->path_env[i])
	{
		tmp = ft_strjoin_gnl(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin_gnl(tmp, input_cmd);
		if (access(ms->path_cmd, X_OK) != -1)
			return (1);
		i++;
	}
	return (0);
}

int	check_command(t_minishell *ms, char *input_cmd)
{
	if (input_cmd[0] == '/' || (input_cmd[0] == '.' && input_cmd[1] == '/'))
	{
		if (check_command_special(ms, input_cmd))
			return (1);
		return (0);
	}
	if (is_built_in(input_cmd))
		return (1);
	if (!ms->path_env || !*input_cmd)
	{
		print_error(input_cmd, ": command not found\n");
		exit(127);
	}
	if (check_cmd_access(ms, input_cmd))
		return (1);
	print_error(input_cmd, ": command not found\n");
	exit(127);
	return (0);
}
