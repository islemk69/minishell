/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/16 16:52:34 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	check_command(t_minishell *ms, char *input_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->path_env[i])
	{
		tmp = ft_strjoin(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin(tmp, input_cmd);
		if (access(ms->path_cmd, X_OK) != -1 || is_built_in(input_cmd))
			return (1);
		i++;
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

char	**redirection_verif(t_minishell *ms, char **tab)
{
	int i;
	char	**realloc;
	int		size;
	int		j;

	j = 0;
	size = 0;
	i = 0;
	while (tab[size])
		size++;
	while (tab[i] && tab[i][0] == '<')
		i++;
	i--;
	//ft_printf("derniere redirection %s\n", tab[i]);
	ms->infile = open(tab[i] + 1, O_RDONLY);
	if (ms->infile < 0)
		ft_printf("error infile");
	if (dup2(ms->infile, 0) == -1)
		error ("dup");
	// int k = size - i;
	// ft_printf("new size = %d\n", k);
	realloc = ft_gc_malloc(sizeof(char *) * (size - i));
	i++;
	//ft_printf("celui la %s\n", tab[i]);
	while (tab[i])
	{
		realloc[j] = ft_strdup(tab[i]);
		//ft_printf("celui la %s\n", realloc[j]);
		j++;
		i++;
	}
	realloc[j] = 0;
	return (realloc);
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;
	char	**str;

	if (input_last_cmd(ms->parsed, ms, env) || inputx_index(ms->parsed, ms))
		check_new_line(ms);
	if (builtins(ms, ms->parsed, env) == 1)
			return (1);
	id = fork();
	if (id == 0)
	{
		if (ms->parsed[0][0] == '<')
			str = redirection_verif(ms, ms->parsed);
		else 
			str = ms->parsed;
		check_command(ms, str[0]);
		if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
			ft_dprintf("bash: %s: command not found\n", str[0]);
	}
	wait(NULL);
	wait(NULL);
	return (1);
}

int	exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int		id;
	int		i;
	int		save_stdin;
	char	**split;
	int		cpt;
	char	**str;

	split = NULL;
	save_stdin = dup(0);
	add_history(ms->line);
	i = 0;
	cpt = 0;
	while (ms->parsed[i])
	{
		//if (ms->parsed[i][0] == '|')
		//{
		//	i++;
		//	continue ;
		//}
		split = ft_split(ms->parsed[i], ' ');
		if (pipe(ms->fd) == -1)
			error("pipe");
		if (split[0][0] == '<')
			str = redirection_verif(ms, split);
		else 
			str = split;
		//if (!check_command(ms, split[0]))
		//{
		//	if (nb_pipe == 0)
		//	{
		//		if (dup2(save_stdin, 0) == -1)
		//			error ("dup");
		//		return (close(save_stdin), error(CMD_ERR), 0);
		//	}
		//	i++;
		//	nb_pipe--;
		//}
		check_command(ms, str[0]);
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
			if (builtins(ms, str, env) == 1 || input_last_cmd(str, ms, env) || inputx_index(str, ms))
				exit (0);
			if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
			{
				nb_pipe--;
				i++;
				ft_dprintf("bash: %s: command not found\n", str[0]);
			}
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

		i++;
		cpt++;
		nb_pipe--;
	}
	close(save_stdin);
	wait_pid(cpt);
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
