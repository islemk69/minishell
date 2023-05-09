/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:19:41 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/09 11:20:36 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	custom_msg_check_line(char *line, int pos, char c)
{
	char	*npipe;
	int		size;
	int		save;

	save = pos;
	size = 0;
	while (line[save] && line[save] == c)
	{
		size++;
		save++;
	}
	npipe = ft_gc_malloc(sizeof(char) * (size + 1));
	size = 0;
	while (line[pos] && line[pos] == c)
	{
		npipe[size] = line[pos];
		pos++;
		size++;
	}
	npipe[size] = 0;
	ft_dprintf(""RED""SYNT_ERR" `%s'\n"WHITE"", npipe);
	return (0);
}
