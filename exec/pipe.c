/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 19:48:49 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	init_pipe(t_minishell *ms, int i)
{
	char	**split;

	ms->infile = 0;
	ms->outfile = 0;
	ms->infile_stra = NULL;
	ms->outfile_exist = 0;
	split = ft_split_token(ms->parsed[i], ' ');
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
}

void	child_pipe(t_minishell *ms, t_env **env, int *nb_pipe, int *i)
{
	set_exec_signals();
	check_redir(ms);
	if (!check_command(ms, ms->new_parsed[0]))
		exit (0);
	close(ms->fd[0]);
	if (*nb_pipe != 0)
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
	if (execve(ms->path_cmd, ms->new_parsed, refresh_env(env)) == -1)
	{
		nb_pipe--;
		i++;
	}
	exit(0);
}

void	parent_pipe(t_minishell *ms, int save_stdin, int *nb_pipe)
{
	close(ms->fd[1]);
	if (*nb_pipe != 0)
	{
		if (dup2(ms->fd[0], 0) == -1)
			error ("dup3");
	}
	else
	{
		if (dup2(save_stdin, 0) == -1)
			error ("dup6");
	}
	close(ms->fd[0]);
	close(ms->fd[1]);
}

void	finish_pipe(t_minishell *ms, int save_stdin, int cpt)
{
	int		i;
	char	**split;

	i = 0;
	close(save_stdin);
	wait_pid(ms, cpt);
	g_global.g_status = WEXITSTATUS(ms->status);
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		remove_heredoc(split);
		i++;
	}
}

int	exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int		id;
	int		i;
	int		save_stdin;

	save_stdin = dup(0);
	get_path(ms);
	if (!open_infile(ms))
		return (0);
	i = 0;
	while (ms->parsed[i])
	{
		init_pipe(ms, i);
		if (pipe(ms->fd) == -1)
			error("pipe");
		id = fork();
		if (id == 0)
			child_pipe(ms, env, &nb_pipe, &i);
		parent_pipe(ms, save_stdin, &nb_pipe);
		i++;
		nb_pipe--;
	}
	finish_pipe(ms, save_stdin, i);
	return (1);
}
