/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_write_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:03:58 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/19 16:28:53 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_write_exit(t_minishell *ms)
{
	if (!ft_strncmp(ms->line, "exit", 4))
	{
		write(1, "👳‍ <== おはよう\n", ft_strlen("👳‍ <== おはよう\n"));
		exit(0);
	}
	return (0);
}
