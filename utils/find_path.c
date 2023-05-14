/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:52:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/14 07:52:37 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**refresh_env(t_env **env)
{
	t_env	*head;
	char	**new_env;
	int		i;

	i = 0;
	head = *env;
	new_env = (char **)ft_gc_malloc(sizeof(char *) * (lstsize(*env) + 1));
	while (head)
	{
		new_env[i] = ft_strjoin_gnl(new_env[i], head->key);
		if (!head->value)
		{
			head = head->next;
			i++;
			continue ;
		}
		new_env[i] = ft_strjoin_gnl(new_env[i], "=");
		new_env[i] = ft_strjoin_gnl(new_env[i], head->value);
		head = head->next;
		i++;
	}
	return (new_env[i] = 0, new_env);
}

char	*ft_find_path(t_env **env, char *srch)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (!ft_strncmp(head->key, srch, ft_strlen(srch) + 1))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}
