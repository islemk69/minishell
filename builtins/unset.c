/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:47 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/27 14:23:45 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int built_in_unset(t_env** env, char **cmd) 
{
    t_env* current = *env;
    t_env* previous = NULL;
	
	if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		if (!cmd[1])
			return (1);
		while (current != NULL) 
		{
			if (strcmp(current->key, cmd[1]) == 0) 
			{
				if (previous == NULL) 
					*env = current->next;
				else
					previous->next = current->next;
				return (1);
			}
			previous = current;
			current = current->next;
		}
		return (1);
	}
	return (0);
}