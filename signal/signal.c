/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:12:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 03:15:22 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		if (g_exit_status == 0)
		{
			ft_putstr_fd("\b\b\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		ft_putstr_fd("\b\b\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

