/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/18 20:00:28 by hel-ouar         ###   ########.fr       */
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
		check_dollar(ms);
		if (!exec_one_pipe(ms, env))
			return (0);
	}
	else
	{
		ms->parsed = dollar_pipe(ms, 0, 0);
		// int i = 0;
		// while (ms->parsed[i])
		// {
		// 	printf("new[%d] = %s\n", i, ms->parsed[i]);
		// 	printf("new[%d][0] = %c\n", i, ms->parsed[i][0]);
		// 	i++;
		// }
		if (!exec_multi_pipe(ms, env, nb_pipe))
			return (0);
	}
	return (1);
}
