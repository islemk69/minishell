/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/18 08:39:07 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmd(t_minishell *ms, t_env **env)
{
	int		nb_pipe;

	unplug_signals();
	nb_pipe = count_token(ms->line, '|', false, '\0');
	if (nb_pipe == 0)
	{
		check_dollar(ms, 0);
		if (!exec_one_pipe(ms, env))
			return (0);
	}
	else
	{
		// int i = 0;
		// while (ms->parsed[i])
		// {
		// 	printf("ms->parse[%d] = %s\n", i, ms->parsed[i]);
		// 	i++;
		// }
		// char **realloc = ft_calloc_parent(sizeof(char *), i + 1, "realloc");
		// i = 0;
		// while (ms->parsed[i])
		// {
		// 	realloc[i] = ft_strdup(dollar_here_doc(ms, ms->parsed[i], 0, 0));
		// 	i++;
		// }
		// realloc[i] = 0;
		// i = 0;
		// while (realloc[i])
		// {
		// 	printf("realloc[%d] = %s\n", i, realloc[i]);
		// 	i++;
		// }
		ms->parsed = dollar_pipe(ms, 0, 0);
		// i = 0;
		// while (ms->parsed[i])
		// {
		// 	printf("new[%d] = %s\n", i, ms->parsed[i]);
		// 	i++;
		// }
		//check_dollar(ms, 1);
		if (!exec_multi_pipe(ms, env, nb_pipe))
			return (0);
	}
	return (1);
}
