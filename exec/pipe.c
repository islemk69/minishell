/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/16 19:21:27 by hamza            ###   ########.fr       */
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
		exit (0);
	}
	waitpid(id2, &status, WUNTRACED);
	g_global.g_status = WEXITSTATUS(status);
	if (g_global.g_status == 130)
		return (remove_heredoc(ms), 1);
	return (0);
}

int	init_exec_pipe(t_minishell *ms, int nb_pipe)
{
	ms->pid = ft_gc_malloc(sizeof(int) * (nb_pipe + 1));
	ms->save_stdin = dup(0);
	get_path(ms);
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
	return (1);
}
