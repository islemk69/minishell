/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:52:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/08 14:52:05 by ikaismou         ###   ########.fr       */
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
	new_env = (char **)malloc(sizeof(char *) * (lstsize(*env) + 1));
	while (head)
	{
		new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(head->str) + 1));
		j = 0;
		while (head->str[j])
		{
			new_env[i][j] = head->str[j];
			j++;
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
		if (!ft_strncmp(head->str, srch, ft_strlen(srch)))
			return (head->str + (ft_strlen(srch) + 1));
		head = head->next;
	}
	return (NULL);
}