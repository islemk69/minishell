/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/17 16:31:31 by hel-ouar         ###   ########.fr       */
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
	char	**str;
	char	*tmp;

	int i = 0;
	get_path(ms);
	if (builtins(ms, ms->parsed, env))
			return (1);
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
	id = fork();
	if (id == 0)
	{
		if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
		{
			rm_quote_last(ms->parsed);
			str = check_redir(ms, ms->parsed);
		}
		else
		{
			rm_quote_last(ms->parsed);
			str = ms->parsed;
		}
		if (!check_command(ms, str[0]))
			exit (0);
		execve(ms->path_cmd, str, refresh_env(env));
	}
	wait(NULL);
	remove_heredoc(ms->parsed);
	return (1);
}