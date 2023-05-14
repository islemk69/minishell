/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/14 09:30:01 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rm_quote_last(char **cmds)
{
	char	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = quote(tmp);
		cmds++;
	}
}

int	heredoc_simple(t_minishell *ms)
{
	int		i;
	char	*tmp;
	int		count;

	i = 0;
	count = 0;
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
	set_exec_signals();
	if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
		ms->new_parsed = check_redir_simple(ms);
	else
	{
		rm_quote_last(ms->parsed);
		ms->new_parsed = ms->parsed;
	}
	if (child_builtins(ms, ms->new_parsed, env))
	{
		ft_gc_free_all();
		exit(0);
	}
	check_command(ms, ms->new_parsed[0]);
	execve(ms->path_cmd, ms->new_parsed, refresh_env(env));
}

int	first_child(t_minishell *ms)
{
	int	id2;
	int	status;

	id2 = fork();
	if (id2 == 0)
	{
		heredoc_simple(ms);
		exit(0);
	}
	waitpid(id2, &status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(status);
	if (g_global.g_status == 130)
		return (1);
	return (0);
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int	id;

	file_name_simple(ms, 0);
	unplug_signals();
	get_path(ms);
	if (parent_builtins(ms, ms->parsed, env, 0))
		return (1);
	if (first_child(ms))
		return (1);
	id = fork();
	if (id == 0)
		child_simple_exec(ms, env);
	waitpid(-1, &ms->status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(ms->status);
	remove_heredoc(ms);
	return (1);
}
