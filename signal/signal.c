/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal..c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:12:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/25 23:12:33 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\b\b\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
