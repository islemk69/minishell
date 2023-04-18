/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:40:24 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/18 18:50:05 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_code(t_minishell *ms, int in_pipe)
{
	if (ft_atoi(ms->new_parsed[1]) < 2147483648)
		g_global.g_status = ft_atoi(ms->new_parsed[1]);
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(ms->new_parsed[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_global.g_status = 2;
	}
	if (!in_pipe)
		return (exit(g_global.g_status));
}

void	ft_numarg_check(t_minishell *ms)
{
	int		i;

	i = -1;
	while (ms->new_parsed[1][++i])
	{
		if (i == 0 && (ms->new_parsed[1][i] == '-' \
		|| ms->new_parsed[1][i] == '+'))
			i++;
		if (ms->new_parsed[1][i] < '0'
		|| ms->new_parsed[1][i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(ms->new_parsed[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (exit(2));
		}
	}
}

void	ft_built_in_exit(t_minishell *ms, int in_pipe)
{
	//printf("exit\n");
	if (!ms->new_parsed[1] || !*ms->new_parsed[1])
		return (exit(g_global.g_status));
	ft_numarg_check(ms);
	if (ms->new_parsed[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_global.g_status = 1;
	}
	else
		ft_exit_code(ms, in_pipe);
}

int	check_write_exit(t_minishell *ms, int pipe)
{
	if (!ft_strncmp(ms->line, "exit\0", 5))
	{
		write(1, "👳‍ <== SALAM\n", ft_strlen("👳‍ <== SALAM\n"));
		return (free(ms->line), ft_built_in_exit(ms, 0), pipe);
	}
	return (1);
}
