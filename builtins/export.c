/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 15:12:01 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int built_in_export(t_env **env, char **split)
{
	if (!ft_strncmp(split[0], "export\0,", 7) && ft_strchr(split[1], '='))
	{
		t_env	*cell;
		t_env	*print;
		
		if (!split[1])
		{
			print = *env;
			while (print)
			{
				ft_printf("declare -x %s=%s\n", print->key, print->value);
				print = print->next;
			}
			return (1);
		}
		char *key = get_key(split[1]);
		char *value = get_value(split[1]);
		cell = create_cell(key, value);
		if (!cell)
		{
			return (0);
		}
		ft_lstad_back(env, cell);
		return (1);
	}
	return (0);
}