/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 18:11:43 by ikaismou         ###   ########.fr       */
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
	char	*tmp;
	int j;

	save_stdin = dup(0);
	get_path(ms);
	i = 0;
	cpt = 0;
	while (ms->parsed[i])
	{
		split = ft_split_space(ms->parsed[i]);
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
			{
				tmp = split[j];
				split[j] = quote(tmp);
				if (!here_doc(ms, split[j] + 2, tmp))
					return (0);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (ms->parsed[i])
	{
		ms->infile = 0;
		ms->outfile = 0;
		ms->infile_stra = NULL;
		ms->outfile_exist = 0;
		split = ft_split_space(ms->parsed[i]);
		if (split[0][0] == '<' || split[0][0] == '>')
		{
			rm_quote_last(split);
			ms->new_parsed = open_files(ms, split);
		}
		else
		{
			rm_quote_last(split);
			ms->new_parsed = split;
		}
		if (pipe(ms->fd) == -1)
			error("pipe");
		id = fork();
		if (id == 0)
		{
			set_exec_signals();
			check_redir(ms);
			if (!check_command(ms, ms->new_parsed[0]))
				exit (0);
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
			if (pipe_builtins(ms, ms->new_parsed, env, 1) == 1)
				exit(g_global.g_status);
			if (execve(ms->path_cmd, ms->new_parsed, refresh_env(env)) == - 1)
			{
				nb_pipe--;
				i++;
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
	wait_pid(ms, cpt);
	g_global.g_status = WEXITSTATUS(ms->status);
	i = 0;
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		remove_heredoc(split);
		i++;
	}
	return (1);
}

//32 50 53 56 58 101 103 110 113 131 132 140 141