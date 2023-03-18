/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/18 18:00:09 by ikaismou         ###   ########.fr       */
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
		if (ms->line[i] == '|' && ms->line[i - 1] != '\"' && ms->line[i + 1] != '\"')
			pipe++;
		i++;
	}
	return (pipe);
}

char	**check_redir(t_minishell *ms, char **tab)
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
	ms->infile = open(tab[i] + 1, O_RDONLY);
	if (ms->infile < 0)
	{
		ft_dprintf(""RED"bash: %s: No such file or directory\n", ms->parsed[i]);
		exit (0);
	}
	if (dup2(ms->infile, 0) == -1)
		error ("dup");
	realloc = ft_gc_malloc(sizeof(char *) * (size - i));
	i++;
	while (tab[i])
	{
		realloc[j] = ft_strdup(tab[i]);
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
			str = check_redir(ms, ms->parsed);
		else 
			str = ms->parsed;
		check_command(ms, str[0]);
		if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
		{
			ft_dprintf(""RED"bash: %s: command not found"WHITE"\n", str[0]);
			exit(0);
		}
	}
	wait(NULL);
	//wait(NULL);
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
		split = ft_split(ms->parsed[i], ' ');
		if (pipe(ms->fd) == -1)
			error("pipe");
	
		id = fork();
		if (id == 0)
		{
			if (split[0][0] == '<')
				str = check_redir(ms, split);
			else 
				str = split;
			check_command(ms, str[0]);
			close(ms->fd[0]);
			if (nb_pipe != 0)
			{
				if (dup2(ms->fd[1], 1) == -1)
					error ("dup");
			}
			else
				dup(1);
			if (builtins(ms, str, env) == 1)
				exit (0);
			input_last_cmd(str, ms, env);
			inputx_index(str, ms);
			if (execve(ms->path_cmd, str, refresh_env(env)) == - 1)
			{
				nb_pipe--;
				i++;
				ft_dprintf(""RED"bash: %s: command not found"CYAN"\n", str[0]);
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
