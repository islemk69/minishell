/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:45:36 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/04/28 13:13:42 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrl_c(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global.g_status = 1;
}

void	handle_ctrl_d_exec(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	ft_printf("Quit (core dumped)\n");
	//write(1, "\n", 1);
	g_global.g_status = 128 + signum;
	return (exit(g_global.g_status));
}

void	handle_ctrl_c_exec(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	write(1, "\n", 1);
	g_global.g_status = 1;
	return (exit(g_global.g_status));
}

void	handle_ctrl_c_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	write(1, "\n", 1);
	g_global.g_status = 1;
	return (exit(g_global.g_status));
}