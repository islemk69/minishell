/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 14:34:30 by hel-ouar         ###   ########.fr       */
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

	i = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			tmp = ms->parsed[i];
			ms->parsed[i] = quote(tmp);
			if (!here_doc(ms, ms->parsed[i] + 2, tmp + 2))
				return (0);
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

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;

	get_path(ms);
	if (parent_builtins(ms, ms->parsed, env, 0))
		return (1);
	id = fork();
	if (id == 0)
	{
		if (!heredoc_simple(ms))
			return (exit(1), 0);
		child_simple_exec(ms, env);
	}
	waitpid(-1, &ms->status, 0);
	g_global.g_status = WEXITSTATUS(ms->status);
	remove_heredoc(ms->parsed);
	return (1);
}
