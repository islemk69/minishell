/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:52:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/11 00:02:31 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **refresh_env(t_env **env)
{
	t_env *head;
	head = *env;
	char **new_env;
	int i = 0;
	int j = 0;
	int k = 0;
	new_env = (char **)ft_gc_malloc(sizeof(char *) * (lstsize(*env) + 1));
	while (head)
	{
		new_env[i] = (char *)ft_gc_malloc(sizeof(char) * (ft_strlen(head->key) + ft_strlen(head->value) + 2));
		j = 0;
		k = 0;
		while (head->key[k])
		{
			new_env[i][j] = head->key[k];
			j++;
			k++;
		}
		new_env[i][j] = '=';
		j++;
		k = 0;
		while (head->value[k])
		{
			new_env[i][j] = head->value[k];
			j++;
			k++;
		}
		new_env[i][j] = 0;
		head = head->next;
		i++;
	}
	new_env[i] = 0;
	return (new_env);
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