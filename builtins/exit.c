/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:40:24 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/27 06:03:50 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_code(char **split, int in_pipe)
{
	g_global.g_status = ft_atoi(split[1]);
	if (!in_pipe)
		return (exit(g_global.g_status));
}

void	ft_numarg_check(char **split)
{
	int		i;

	i = -1;
	while (split[1][++i])
	{
		if (i == 0 && (split[1][i] == '-' \
		|| split[1][i] == '+'))
			i++;
		if (split[1][i] < '0'
		|| split[1][i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(split[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (exit(255));
		}
	}
}

void	ft_built_in_exit(char **split, int in_pipe)
{
	if (!in_pipe)
		ft_printf("exit\n");
	if (!split[1] || !*split[1])
		return (exit(g_global.g_status));
	ft_numarg_check(split);
	if (split[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_global.g_status = 1;
	}
	else
		ft_exit_code(split, in_pipe);
}

int	check_write_exit(t_minishell *ms, char **split, int pipe)
{
	if (!ft_strncmp(ms->line, "exit", 4))
	{
		//write(1, "👳‍ <== SALAM\n", ft_strlen("👳‍ <== SALAM\n"));
		return (ft_built_in_exit(split, pipe), 0);
	}
	return (1);
}
