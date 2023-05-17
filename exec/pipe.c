/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 06:24:06 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_here(t_minishell *ms, int i, int cpt)
{
	int		j;
	char	**split;
	char	*tmp;

	while (ms->parsed[i])
	{
		split = ft_split_space(ms->parsed[i]);
		if (!split)
			exit_child(-1);
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
			{
				tmp = split[j];
				split[j] = quote(tmp);
				here_doc(ms, split[j] + 2, tmp, cpt);
				cpt++;
			}
			j++;
		}
		i++;
	}
}

int	open_heredoc(t_minishell *ms)
{
	int	id2;
	int	status;

	unplug_signals();
	id2 = fork();
	if (id2 == 0)
	{
		child_here(ms, 0, 0);
		ft_gc_free_all();
		exit (0);
	}
	waitpid(id2, &status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(status);
	if (g_global.g_status == 130)
		return (remove_heredoc(ms), 1);
	if (g_global.g_status == -1)
	{
		remove_heredoc(ms);
		exit_parent("heredoc");
	}
	return (0);
}

int	init_exec_pipe(t_minishell *ms, int nb_pipe)
{
	ms->pid = ft_calloc_parent(sizeof(int), (nb_pipe + 1), "tableau pid");
	ms->save_stdin = dup(0);
	if (get_path(ms) == -1)
		exit_parent("get path");
	file_name_pipe(ms, 0, 1);
	if (open_heredoc(ms))
		return (1);
	unplug_signals();
	return (0);
}

int	exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe)
{
	int		id1;
	int		tmp_status;

	if (init_exec_pipe(ms, nb_pipe))
		return (1);
	id1 = fork();
	if (id1 == 0)
		ft_exec_pipe(ms, env, nb_pipe);
	waitpid(id1, &tmp_status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(tmp_status);
	remove_heredoc(ms);
	if (g_global.g_status == -1)
		exit_parent("exec");
	return (1);
}
