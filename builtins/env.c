/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:21:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 11:16:33 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_env(t_env **env, char **split)
{
	t_env	*head;

	head = *env;
	if (split[0] && !split[1] && !ft_strncmp(split[0], "env\0", 4))
	{
		while (head)
		{
			if (!head->value)
			{
				head = head->next;
				continue ;
			}
			printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
		return (1);
	}
	return (0);
}
