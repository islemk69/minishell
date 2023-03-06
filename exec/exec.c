/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/06 18:35:00 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char **refresh_env(t_env **env)
{
	t_env *head;
	head = *env;
	char **new_env;
	int i = 0;
	int j = 0;
	new_env = (char **)malloc(sizeof(char *) * (lstsize(*env) + 1));
	while (head)
	{
		new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(head->str) + 1));
		j = 0;
		while (head->str[j])
		{
			new_env[i][j] = head->str[j];
			j++;
		}
		new_env[i][j] = 0;
		head = head->next;
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

static int	check_command(t_minishell *ms, char *input_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->path_env[i])
	{
		tmp = ft_strjoin(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin(tmp, input_cmd);
		free(tmp);
		if (access(ms->path_cmd, X_OK) != -1)
			return (1);
		i++;
		free(ms->path_cmd);
	}
	return (0);
}

int count_pipe(t_minishell *ms)
{
	int	pipe;
	int i;

	i = 0;
	pipe = 0;
	while (ms->line[i])
	{
		if (ms->line[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;


	if (input_last_cmd(ms->parsed, ms, env) || inputx_index(ms->parsed, ms))
	{
		ft_free_tab(ms->parsed);
		check_new_line(ms);
	}
	add_history(ms->line);
	if (builtins(ms, ms->parsed, env) == 1)
		return (0);
	id = fork();
	if (id == 0)
	{
		if (!check_command(ms, ms->parsed[0]))
			return (error(CMD_ERR), 0);
		if (execve(ms->path_cmd, ms->parsed, refresh_env(env)) == - 1)
			error("error exec");
		exit(0);
	}

	wait(NULL);
	wait(NULL);
	//ft_free_tab(ms->new_env);
	return (1);
}

int	exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int	id;
	int	i;
	int	save_stdin;
	char	**split;

	save_stdin = dup(0);
	i = 0;
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		if (!check_command(ms, split[0]))
		{
			if (dup2(save_stdin, 0) == -1)
				error ("dup");
			return (close(save_stdin), error(CMD_ERR), 0);
		}
		if (pipe(ms->fd) == -1)
			error("pipe");	
		id = fork();
		if (id == 0)
		{
			close(ms->fd[0]);
			if (nb_pipe != 0)
			{
				if (dup2(ms->fd[1], 1) == -1)
					error ("dup");
			}
			else
				dup(1);
			if (execve(ms->path_cmd, split, refresh_env(env)) == - 1)
				error("error exec");
			exit(0);
		}
		if (nb_pipe != 0)
		{
			if (dup2(ms->fd[0], 0) == -1)
				error ("dup");
		}
		else
			if (dup2(save_stdin, 0) == -1)
				error ("dup");
		close(ms->fd[0]);
		close(ms->fd[1]);
		//free(ms->path_cmd);
		i++;
		nb_pipe--;
	}
	close(save_stdin);
	//ft_free_tab(ms->joined); //////////////////seg fault
	//ft_free_tab(split);
	while (i >= 0)
	{
		wait(NULL);
		i--;
	}
	return (1);
}

int	exec_cmd(t_minishell *ms, t_env **env)
{
	int		nb_pipe;

	nb_pipe = count_pipe(ms);
	if (nb_pipe == 0)
	{
		if (!exec_one_pipe(ms, env))
			return (0);
	}
	else
	{
		if (!exec_multi_pipe(ms, env, nb_pipe))
			return (0);
	}
	return (1);
}