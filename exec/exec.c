/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/25 03:02:58 by hamzaelouar      ###   ########.fr       */
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

int	here_doc(t_minishell *ms, char *tab)
{
	ms->infile = open(tab, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		ms->line_here = readline(">");
		if (!ms->line_here)
			return (free(ms->line_here), 0);
		if (!ft_strncmp(tab, ms->line_here, ft_strlen(tab))
				&& (ft_strlen(tab) == ft_strlen(ms->line_here)))
			break ;
		write(ms->infile, ms->line_here, ft_strlen(ms->line_here));
		write(ms->infile, "\n", 1);
		free(ms->line_here);
	}
	free(ms->line_here);
	close(ms->infile);
	return (1);
}

void	access_file(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
		{
			if (access(tab[i] + 2, F_OK) != 0)
			{
				ft_dprintf(""RED"bash: %s: No such file or directory\n", tab[i] + 2);
				exit (0);
			}
		}
		else if (access(tab[i] + 1, F_OK) != 0)
		{
			ft_dprintf(""RED"bash: %s: No such file or directory\n", tab[i] + 1);
			exit (0);
		}
		i++;
	}
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
	access_file(tab);
	while (tab[size])
		size++;
	if (tab[i][0] == '<')
	{
		while (tab[i] && tab[i][0] == '<')
			i++;
		i--;
		if (tab[i][1] == '<')
			ms->infile = open(tab[i] + 2, O_RDONLY);
		if (tab[i][1] != '<')
			ms->infile = open(tab[i] + 1, O_RDONLY);
		if (ms->infile < 0)
		{
			ft_dprintf(""RED"bash: %s: No such file or directory\n", ms->parsed[i]);
			exit (0);
		}
		if (dup2(ms->infile, 0) == -1)
			error ("dup");
		i++;
	}
	while (tab[i] && tab[i][0] == '>')
		i++;
	i--;
	if (tab[i][0] == '>')
	{
		ms->outfile_exist = 1;
		if (tab[i][1] == '>')
			ms->outfile = open(tab[i] + 2, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			ms->outfile = open(tab[i] + 1, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(ms->outfile, 1) == -1)
			error ("dup6");
	}
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

void	remove_heredoc(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
			remove(tab[i] + 2);
		i++;
	}
}

int	exec_one_pipe(t_minishell *ms, t_env **env)
{
	int		id;
	char	**str;

	if (input_last_cmd(ms->parsed, ms, env) || inputx_index(ms->parsed, ms))
		check_new_line(ms);
	if (builtins(ms, ms->parsed, env) == 1)
			return (1);
	int i = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
			here_doc(ms, ms->parsed[i] + 2);
		i++;
	}
	id = fork();
	if (id == 0)
	{
		if (ms->parsed[0][0] == '<' || ms->parsed[0][0] == '>')
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
	remove_heredoc(ms->parsed);
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
	int j;

	split = NULL;
	save_stdin = dup(0);
	add_history(ms->line);
	i = 0;
	cpt = 0;
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
				here_doc(ms, split[j] + 2);
			j++;
		}
		i++;
	}
	i = 0;
	while (ms->parsed[i])
	{
		split = ft_split(ms->parsed[i], ' ');
		if (pipe(ms->fd) == -1)
			error("pipe");
		id = fork();
		if (id == 0)
		{
			ms->outfile_exist = 0;
			if (split[0][0] == '<' || split[0][0] == '>')
				str = check_redir(ms, split);
			else
				str = split;
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
			{
				if (ms->outfile_exist == 0)
				{
					if (dup2(ms->fd[1], 1) == -1)
						error ("dup3");
				}
				else
					dup(1);
			}
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
