/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/28 18:10:32 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void rm_quote_last(char **cmds)
{
	char *tmp;
	
	while (*cmds)
	{
		tmp = *cmds;
		*cmds = quote(tmp);	
		cmds++;
	}
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;
	char	*tmp;

	int i = 0;
	get_path(ms);
	// while (ms->parsed[i] && ms->parsed[i][0] == '<')
	// {
	// 	if (ms->parsed[i][1] == '<')
	// 	{
	// 		tmp = ms->parsed[i];
	// 		ms->parsed[i] = quote(tmp);
	// 		if (!here_doc(ms, ms->parsed[i] + 2, tmp + 2))
	// 			return (0);
	// 	}
	// 	i++;
	// }
	if (parent_builtins(ms, ms->parsed, env, 0))
		return (1);
	id = fork();
	if (id == 0)
	{
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
		set_exec_signals();
		if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
		{
			rm_quote_last(ms->parsed);
			ms->new_parsed = check_redir(ms, ms->parsed);
		}
		else
		{
			rm_quote_last(ms->parsed);
			ms->new_parsed = ms->parsed;
		}
		if (child_builtins(ms, ms->new_parsed, env))
			exit(0);
		if (!check_command(ms, ms->new_parsed[0]))
			exit (0);
		execve(ms->path_cmd, ms->new_parsed, refresh_env(env));
	}
	waitpid(-1, &ms->status, 0);
	g_global.g_status = WEXITSTATUS(ms->status);
	remove_heredoc(ms->parsed);
	return (1);
}