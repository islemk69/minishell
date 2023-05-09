/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:47 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 10:45:30 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	built_in_unset(t_env **env, char **cmd)
// {
//     t_env	*current;
//     t_env	*previous;
// 	int		i;

// 	i = 1;
// 	if (!ft_strncmp(cmd[0], "unset\0", 6))
// 	{
// 		if (!cmd[1])
// 			return (1);
// 		while (cmd[i])
// 		{
// 			if (!check_key(cmd[i]) || (cmd[i][0] >= '0'&& cmd[i][0] <= '9'))
// 			{
// 				ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"
// 					WHITE"", cmd[i]);
// 				g_global.g_status = 1;
// 				i++;
// 				continue ;
// 			}
// 			current = *env;
//     		previous = NULL;
// 			while (current != NULL) 
// 			{
// 				if (ft_strncmp(current->key, cmd[i], 
// 					ft_strlen(current->key)) == 0) 
// 				{
// 					if (previous == NULL) 
// 						*env = current->next;
// 					else
// 						previous->next = current->next;
// 				}
// 				previous = current;
// 				current = current->next;
// 			}
// 			i++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

void	iter_unset(t_env **env, char *cmd)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, cmd, \
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
}

void	do_unset(t_env **env, char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (!check_key(cmd[i]) || (cmd[i][0] >= '0' && cmd[i][0] <= '9'))
		{
			ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"\
				WHITE"", cmd[i]);
			g_global.g_status = 1;
			i++;
			continue ;
		}
		iter_unset(env, cmd[i]);
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
