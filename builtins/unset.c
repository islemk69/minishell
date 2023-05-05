/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:47 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/05 14:11:25 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int built_in_unset(t_env** env, char **cmd) 
{
    t_env* current;
    t_env* previous;
	int i = 1;
	
	if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		if (!cmd[1])
			return (1);
		while (cmd[i])
		{
			current = *env;
    		previous = NULL;
			while (current != NULL) 
			{
				if (ft_strncmp(current->key, cmd[i], ft_strlen(current->key)) == 0) 
				{
					if (previous == NULL) 
						*env = current->next;
					else
						previous->next = current->next;
				}
				previous = current;
				current = current->next;
			}
			i++;
		}
		return (1);
	}
	return (0);
}