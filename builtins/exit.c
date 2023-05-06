/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:40:24 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 18:01:52 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_code(char **split, int in_pipe, t_minishell *ms)
{
	ms->overflow = false;
	g_global.g_status = ft_atoi2(split[1], ms);
	if (ms->overflow == true)
	{
		print_error(split[1], ": numeric argument required\n");
		g_global.g_status = 2;
	}
	if (!in_pipe)
		return (ft_gc_free_all(), exit(g_global.g_status));
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
			ft_dprintf("exit: %s: numeric argument required\n", split[1]);
			return (ft_gc_free_all(), exit(2));
		}
	}
}

void	ft_built_in_exit(char **split, int in_pipe, t_minishell *ms)
{
	if (!in_pipe)
		printf("exit\n");
	if (!split[1] || !*split[1])
		return (ft_gc_free_all(), exit(g_global.g_status));
	ft_numarg_check(split);
	if (split[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_global.g_status = 1;
	}
	else
		ft_exit_code(split, in_pipe, ms);
}

int	check_write_exit(t_minishell *ms, char **split, int pipe)
{
	if (!ft_strncmp(ms->line, "exit", 4))
	{
		return (ft_built_in_exit(split, pipe, ms), 0);
	}
	return (1);
}
