/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/31 16:34:12 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int		id;
	int		i;
	int		save_stdin;
	char	**split;
	int		cpt;
	char	**str;
	char	*tmp;
	int j;

	split = NULL;
	save_stdin = dup(0);
	add_history(ms->line);
	get_path(ms);
	i = 0;
	cpt = 0;
	while (ms->parsed[i])
	{
		split = split_string(ms->parsed[i]);
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
			{
				tmp = split[j];
				split[j] = quote(tmp);
				if (!here_doc(ms, split[j] + 2))
					return (0);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (ms->parsed[i])
	{
		split = split_string(ms->parsed[i]);
		if (pipe(ms->fd) == -1)
			error("pipe");
		id = fork();
		if (id == 0)
		{
			ms->outfile_exist = 0;
			if (split[0][0] == '<' || split[0][0] == '>')
			{
				rm_quote_last(split);
				str = check_redir(ms, split);
			}
			else
			{
				ft_printf("je remove les quote\n");
				rm_quote_last(split);
				str = split;
			}
			check_command(ms, str[0]);
			close(ms->fd[0]);
			if (nb_pipe != 0)
			{
				if (ms->outfile_exist == 0)
				{
					if (dup2(ms->fd[1], 1) == -1)
						error ("dup3");
				}
			}
			else
				dup(1);
			if (builtins(ms, str, env) == 1)
				exit (0);
			if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
			{
				nb_pipe--;
				i++;
				ft_dprintf(""RED"bash: %s: command not found"WHITE"\n", str[0]);
			}
			exit(0);
		}
		close(ms->fd[1]);
		if (nb_pipe != 0)
		{
			if (dup2(ms->fd[0], 0) == -1)
				error ("dup3");
		}
		else
		{
			if (dup2(save_stdin, 0) == -1)
					error ("dup6");
		}
		// if (ms->infile)
		// 	close(ms->infile);
		// if (ms->outfile)
		// 	close(ms->outfile);
		close(ms->fd[0]);
		close(ms->fd[1]);
		i++;
		cpt++;
		nb_pipe--;
	}
	close(save_stdin);
	wait_pid(cpt);
	i = 0;
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		remove_heredoc(split);
		i++;
	}
	return (1);
}