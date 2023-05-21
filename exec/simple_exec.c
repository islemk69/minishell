/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/21 21:45:02 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc_simple(t_minishell *ms)
{
	int		i;
	char	*tmp;
	int		count;

	i = 0;
	count = 0;
	unplug_signals();
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			tmp = ms->parsed[i];
			ms->parsed[i] = quote(tmp);
			here_doc(ms, ms->parsed[i] + 2, tmp + 2, count);
			count++;
		}
		i++;
	}
	return (1);
}

void	child_simple_exec(t_minishell *ms, t_env **env)
{
	if (!ms->parsed[0][0] || !ms->parsed)
	{
		ft_close(ms, 0, 0);
		exit(0);
	}
	if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
		ms->new_parsed = check_redir_simple(ms);
	else
	{
		rm_quote_last(ms->parsed);
		ms->new_parsed = ms->parsed;
	}
	if (!ms->new_parsed)
		ft_close(ms, 1, 0);
	if (child_builtins(ms, ms->new_parsed, env)
		|| !check_command(ms, ms->new_parsed[0], -1))
		ft_close(ms, 1, g_global.g_status);
	if (!ms->path_cmd)
		ft_close(ms, 1, g_global.g_status);
	if (execve(ms->path_cmd, ms->new_parsed, refresh_env(env)) == -1)
	{
		g_global.g_status = 1;
		ft_close(ms, 0, 0);
	}
	ft_close(ms, 1, g_global.g_status);
}

int	first_child(t_minishell *ms)
{
	int	id2;
	int	status;

	id2 = fork();
	if (id2 == 0)
	{
		heredoc_simple(ms);
		ft_close(ms, 1, 0);
	}
	waitpid(id2, &status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(status);
	if (g_global.g_status == 130)
		return (1);
	if (g_global.g_status == -1)
	{
		remove_heredoc(ms);
		exit_parent("heredoc");
	}
	return (0);
}

void	exec_child(t_minishell *ms, t_env **env)
{
	int	id2;
	int	status;

	set_exec_signals();
	id2 = fork();
	if (id2 == 0)
	{
		child_simple_exec(ms, env);
		ft_close(ms, 0, 0);
		exit(g_global.g_status);
	}
	if (!ft_strncmp(ms->parsed[0], "./minishell\0", \
		ft_strlen(ms->parsed[0]) + 1))
		unplug_signals();
	waitpid(id2, &status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(status);
	ft_close(ms, 0, 0);
	exit(g_global.g_status);
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int	id;

	file_exist(ms);
	file_name_simple(ms, 0);
	if (get_path(ms) == -1)
		exit_parent("get path");
	if (parent_builtins(ms, ms->parsed, env, 0))
		return (1);
	if (first_child(ms))
		return (remove_heredoc(ms), 1);
	id = fork();
	if (id == 0)
		exec_child(ms, env);
	waitpid(-1, &ms->status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(ms->status);
	remove_heredoc(ms);
	if (g_global.g_status == -1)
		exit_parent("exec");
	return (1);
}
