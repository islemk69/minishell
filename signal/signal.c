/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:12:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/17 17:44:59 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrl_c(int signum, siginfo_t *info, void *context);
void	handle_ctrl_c_heredoc(int signum, siginfo_t *info, void *context);
void	handle_ctrl_c_exec(int signum, siginfo_t *info, void *context);
void	handle_ctrl_d_exec(int signum, siginfo_t *info, void *context);

void	set_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
}

void	set_exec_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c_exec;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_ctrl_d_exec;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	unplug_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
