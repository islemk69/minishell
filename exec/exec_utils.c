/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/18 23:46:26 by hel-ouar         ###   ########.fr       */
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
		return (-1);
	return (1);
}

int	complete_command(char *input_cmd, t_minishell *ms)
{
	struct stat	info;

	if (stat(input_cmd, &info) == 0 && S_ISDIR(info.st_mode))
		error_exit(input_cmd, ": Is a directory\n", 126);
	if (access(input_cmd, F_OK) == 0)
	{
		if (access(input_cmd, X_OK | R_OK) != 0)
			error_exit(input_cmd, ": Permission denied\n", 126);
		ms->path_cmd = input_cmd;
		return (1);
	}
	else
	{
		if (access(input_cmd, F_OK) != 0)
			error_exit(input_cmd, ": No such file or directory\n", 127);
		if (access(input_cmd, X_OK | R_OK) != 0)
			error_exit(input_cmd, ": Permission denied\n", 126);
		ms->path_cmd = input_cmd;
		return (1);
	}
	return (0);
}

int	check_command(t_minishell *ms, char *input_cmd, int i)
{
	char		*tmp;

	if ((input_cmd[0] == '/' || (input_cmd[0] == '.' && input_cmd[1] == '/')) \
		|| (input_cmd[ft_strlen(input_cmd) - 1] == '/'))
	{
		if (complete_command(input_cmd, ms))
			return (1);
	}
	if (is_built_in(input_cmd))
		return (1);
	if (!ms->path_env || !*input_cmd)
		error_exit(input_cmd, ": command not found\n", 127);
	while (ms->path_env[++i])
	{
		tmp = ft_strjoin_gnl(ms->path_env[i], "/");
		if (!tmp)
			exit_child(-1);
		ms->path_cmd = ft_strjoin_gnl(tmp, input_cmd);
		if (!ms->path_cmd)
			exit_child(-1);
		if (access(ms->path_cmd, X_OK) != -1)
			return (1);
	}
	error_exit(input_cmd, ": command not found\n", 127);
	return (0);
}

void	access_file2(t_minishell *ms)
{
	int		i;
	char	**head;

	i = 0;
	head = tab_copy(ms->parsed);
	while (head[i] && head[i][0] == '<')
	{
		if (head[i][1] == '<')
		{
			i++;
			continue ;
		}
		else
		{
			head[i] = quote(head[i]);
			if (access(head[i] + 1, F_OK) != 0)
				error_exit(head[i] + 1, ": No such file or directory\n", 1);
		}
		i++;
	}
}

void	access_file(t_minishell *ms, char **tab)
{
	int		i;
	char	**head;

	i = 0;
	head = tab_copy(tab);
	while (head[i] && head[i][0] == '<')
	{
		if (head[i][1] == '<')
		{
			i++;
			continue ;
		}
		else
		{
			head[i] = quote(head[i]);
			if (access(head[i] + 1, F_OK) != 0)
			{
				ms->infile_stra = head[i] + 1;
				break ;
			}
		}
		i++;
	}
}
