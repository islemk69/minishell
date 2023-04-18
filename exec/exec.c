/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/18 17:30:54 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmd(t_minishell *ms, t_env **env)
{
	int		nb_pipe;
	
	unplug_signals();
	check_dollar(ms);
	int i = 0;
	while (ms->parsed[i])
	{
		ft_printf("ms->parsed[%d] : %s\n", i , ms->parsed[i]);
		i++;
	}
	nb_pipe = count_token(ms->line, '|');
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
