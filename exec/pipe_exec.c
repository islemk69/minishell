/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:22:00 by hamza             #+#    #+#             */
/*   Updated: 2023/05/17 06:08:02 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipe(t_minishell *ms, int i, int *cpt)
{
	char	**split;

	ms->infile = 0;
	ms->outfile = 0;
	ms->infile_stra = NULL;
	ms->outfile_str = NULL;
	ms->outfile_exist = 0;
	if (ms->parsed[i][0])
	{
		split = ft_split_space(ms->parsed[i]);
		if (!split)
			exit_child(-1);
		if (split[0][0] == '<' || split[0][0] == '>')
		{
				ms->new_parsed = open_files(ms, split, &*cpt);
		}
		else
		{
			rm_quote_last(split);
			ms->new_parsed = split;
		}
	}
	else
		ms->new_parsed = 0;
	if (pipe(ms->fd) == -1)
		exit_child(-1);
}

void	dup_exec_pipe(t_minishell *ms, int nb_pipe)
{
	close(ms->fd[0]);
	if (nb_pipe != 0)
	{
		if (ms->outfile_exist == 0)
		{
			if (dup2(ms->fd[1], 1) == -1)
				exit_child(-1);
		}
	}
	else
	{
		if (dup(1) == -1)
			exit_child(-1);
	}
}

void	child_exec_pipe(t_minishell *ms, t_env **env, int nb_pipe, int i)
{
	set_exec_signals();
	ms->pid[i] = fork();
	if (ms->pid[i] == 0)
	{
		check_redir(ms);
		if (!check_command(ms, ms->new_parsed[0], -1))
		{
			printf("ok6\n\n\n");
			ft_gc_free_all();
			exit (0);
		}
		dup_exec_pipe(ms, nb_pipe);
		if (pipe_builtins(ms, ms->new_parsed, env, 1) == 1)
		{
			ft_gc_free_all();
			exit(g_global.g_status);
		}
		if (execve(ms->path_cmd, ms->new_parsed, refresh_env(env)))
		{
			ft_gc_free_all();
		}
		ft_gc_free_all();
		exit(g_global.g_status);
	}
}

void	close_redir_pipe(t_minishell *ms, int nb_pipe)
{
	close(ms->fd[1]);
	if (nb_pipe != 0)
	{
		if (dup2(ms->fd[0], 0) == -1)
			exit_child(-1);
	}
	else
	{
		if (dup2(ms->save_stdin, 0) == -1)
			exit_child(-1);
	}
	close(ms->fd[0]);
	close(ms->fd[1]);
}

void	ft_exec_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	int tmp = nb_pipe;
	while (i <= tmp)
	{

		init_pipe(ms, i, &cpt);
		if (!ms->parsed[i][0])
			ms->parsed[i][0] = 't';
		child_exec_pipe(ms, env, nb_pipe, i);
		close_redir_pipe(ms, nb_pipe);
		i++;
		nb_pipe--;
	}
	close(ms->save_stdin);
	wait_pid(ms, i);
	g_global.g_status = WEXITSTATUS(ms->status);
	ft_gc_free_all();
	exit(g_global.g_status);
}
