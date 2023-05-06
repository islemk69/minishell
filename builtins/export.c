/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 14:31:34 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_key(char *str)
{
	while (*str)
	{
		if ((*str > 64 && *str < 91) || (*str > 96 && *str < 123)
			|| (*str > 47 && *str < 58) || *str == '_')
		{
			str++;
			continue ;
		}
		return (0);
	}
	return (1);
}

static void	print_error_export(char *split)
{
	ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"\
				WHITE"", split);
	g_global.g_status = 1;
}

static void	simple_export(t_env **env)
{
	t_env	*print;
	char	*add_quote;

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
}

static int	several_export(t_env **env, char **split, char **key_value, int i)
{
	t_env	*cell;

	while (split[i])
	{
		if (split[i][0] == '=' || (split[i][0] >= '0' && split[i][0] <= '9'))
		{
			print_error_export(split[i]);
			i++;
			continue ;
		}
		key_value = ft_split(split[i], '=');
		if (!check_key(key_value[0]))
		{
			print_error_export(split[i]);
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

int	built_in_export(t_env **env, char **split)
{
	char	**key_value;

	key_value = NULL;
	if (!ft_strncmp(split[0], "export\0,", 7))
	{
		if (!split[1])
		{
			simple_export(env);
			return (1);
		}
		if (!several_export(env, split, key_value, 1))
			return (0);
		return (1);
	}
	return (0);
}
