/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/04 18:33:07 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_key(char *str)
{
	while (*str)
	{
		if ((*str > 64 && *str < 91) || (*str > 96 && *str < 123) || (*str > 47 && *str < 58) || *str == '_')
		{
			str++;
			continue ;
		}
		return (0);
	}
	return (1);
}

int built_in_export(t_env **env, char **split)
{
	char	**key_value;
	char *add_quote;
	int i = 1;
	t_env	*cell;
	t_env	*print;
	
	if (!ft_strncmp(split[0], "export\0,", 7))
	{
		if (!split[1])
		{
			print = *env;
			while (print)
			{
				if (!print->value)
				{
					printf("declare -x %s\n", print->key);
					print = print->next;
					continue ;
				}
				add_quote = ft_strjoin("\"", print->value);
				add_quote = ft_strjoin(add_quote, "\"");
				printf("declare -x %s=%s\n", print->key, add_quote);
				print = print->next;
			}
			return (1);
		}
		while (split[i])
		{
			if (split[i][0] == '=' || (split[i][0] >= '0' && split[i][0] <= '9'))
			{
				ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"WHITE"", split[i]);
				g_global.g_status = 1;
				i++;
				continue ;
			}
			key_value = ft_split(split[i], '=');
			if (!check_key(key_value[0]))
			{
				ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"WHITE"", split[i]);
				g_global.g_status = 1;
				i++;
				continue ;
			}
			cell = create_cell(key_value[0], key_value[1]);
			if (!cell)
				return (0);
			ft_lstad_back(env, cell);
			i++;
		}
		return (1);
	}
	return (0);
}