/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:02:18 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/22 00:45:57 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (!add_quote)
			exit_parent("builtins");
		add_quote = ft_strjoin(add_quote, "\"");
		if (!add_quote)
			exit_parent("builtins");
		printf("declare -x %s=%s\n", print->key, add_quote);
		print = print->next;
	}
}

static void	do_create_export(t_env **env, char **key_value, int flg)
{
	t_env	*cell;

	if (!flg)
	{
		cell = create_cell(key_value[0], key_value[1]);
		if (!cell)
			exit_parent("builtins");
		ft_lstad_back(env, cell);
	}
}

static int	create_export(t_env **env, char **key_value, int flg)
{
	t_env	*print;

	print = *env;
	while (print)
	{
		if (!ft_strncmp(key_value[0], print->key, ft_strlen(print->key)))
		{
			if (key_value[1])
			{
				print->value = ft_strdup(key_value[1]);
				if (!print->value)
					exit_parent("builtins");
			}
			flg = 1;
			break ;
		}
		print = print->next;
	}
	do_create_export(env, key_value, flg);
	return (1);
}

static int	several_export(t_env **env, char **split, char **key_value, int i)
{
	while (split[++i])
	{
		if ((split[i][0] == '=' || (split[i][0] >= '0' && split[i][0] <= '9')) \
			|| no_key(split[i]))
		{
			print_error_export(split[i]);
			continue ;
		}
		if (split[i][ft_strlen(split[i]) - 1] == '=')
			key_value = create_export_spe_parent(key_value, split[i]);
		else
		{
			key_value = ft_split(split[i], '=');
			if (!key_value)
				exit_parent("builtins");
		}
		if (!check_key(key_value[0]))
		{
			print_error_export(split[i]);
			continue ;
		}
		if (!create_export(env, key_value, 0))
			return (0);
	}
	return (1);
}

int	built_in_export_parent(t_env **env, char **split)
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
		if (!several_export(env, split, key_value, 0))
			return (0);
		return (1);
	}
	return (0);
}
