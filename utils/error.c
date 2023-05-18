/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:20:42 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 20:09:22 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		return ;
}

int	is_empty(char *str, t_minishell *ms)
{
	int	i;

	i = 0;
	if (ft_strlen(str))
		add_history(ms->line);
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	if (str[i] == 0)
		return (1);
	return (0);
}

size_t	ft_strlen_dtab(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
