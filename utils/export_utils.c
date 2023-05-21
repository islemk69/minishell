/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utills.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:28:13 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/22 00:30:37 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_export_spe_parent(char **key_value, char *str)
{
	char	**tmp;

	key_value = ft_calloc_parent(sizeof(char *), 3, "builtins");
	tmp = ft_split(str, '=');
	if (!tmp)
		exit_parent("builtins");
	key_value[0] = ft_strdup(tmp[0]);
	if (!key_value[0])
		exit_parent("builtins");
	key_value[1] = ft_strdup("");
	if (!key_value[1])
		exit_parent("builtins");
	key_value[2] = 0;
	return (key_value);
}

char	**create_export_spe_child(char **key_value, char *str)
{
	char	**tmp;

	key_value = ft_calloc_child(sizeof(char *), 3);
	tmp = ft_split(str, '=');
	if (!tmp)
		exit_child_simple(-1);
	key_value[0] = ft_strdup(tmp[0]);
	if (!key_value[0])
		exit_child_simple(-1);
	key_value[1] = ft_strdup("");
	if (!key_value[1])
		exit_child_simple(-1);
	key_value[2] = 0;
	return (key_value);
}
