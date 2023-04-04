/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:55 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/04 18:17:45 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmd(t_minishell *ms, t_env **env)
{
	int		nb_pipe;

	nb_pipe = count_token(ms->line, '|');
	if (nb_pipe == 0)
	{
		//dollar_exist(ms);
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
