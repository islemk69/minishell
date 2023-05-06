/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:47 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 11:39:03 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_unset(t_env **env, char **cmd)
{
	t_env	*current;
	t_env	*previous;
	int		i;

	i = 1;
	while (cmd[i])
	{
		current = *env;
		previous = NULL;
		while (current != NULL)
		{
			if (ft_strncmp(current->key, cmd[i],
					ft_strlen(current->key)) == 0)
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
}

int	built_in_unset(t_env **env, char **cmd)
{
	if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		if (!cmd[1])
			return (1);
		do_unset(env, cmd);
		return (1);
	}
	return (0);
}
