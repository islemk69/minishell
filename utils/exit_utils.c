/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 06:21:40 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/20 06:24:03 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_child(t_minishell *ms, int i)
{
	ft_close(ms, 0, 0);
	exit(i);
}

void	exit_child_simple(int i)
{
	ft_gc_free_all();
	exit(i);
}

void	exit_parent(char *str)
{
	ft_gc_free_all();
	perror(str);
}
