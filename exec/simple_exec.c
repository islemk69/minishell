/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/29 18:29:18 by ikaismou         ###   ########.fr       */
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

	if (builtins(ms, ms->parsed, env) == 1)
			return (1);
	int i = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			tmp = ms->parsed[i];
			ms->parsed[i] = quote(tmp);
			if (!here_doc(ms, ms->parsed[i] + 2))
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
		check_command(ms, str[0]);
		if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
		{
			ft_dprintf(""RED"bash: %s: command not found"WHITE"\n", str[0]);
			exit(0);
		}
	}
	wait(NULL);
	remove_heredoc(ms->parsed);
	return (1);
}