/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/10 18:47:33 by hel-ouar         ###   ########.fr       */
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
		add_quote = ft_strjoin(add_quote, "\"");
		printf("declare -x %s=%s\n", print->key, add_quote);
		print = print->next;
	}
}

int	create_export(t_env **env, char **key_value, int flg)
{
	t_env	*cell;
	t_env	*print;

	print = *env;
	while (print)
	{
		if (!ft_strncmp(key_value[0], print->key, \
			ft_strlen(print->key)))
		{
			if (key_value[1])
				print->value = ft_strdup(key_value[1]);
			flg = 1;
			break ;
		}
		print = print->next;
	}
	if (!flg)
	{
		cell = create_cell(key_value[0], key_value[1]);
		if (!cell)
			return (0);
		ft_lstad_back(env, cell);
	}
	return (1);
}

char	**create_export_spe(char **key_value, char *str)
{
	char	**tmp;

	key_value = ft_gc_malloc(sizeof(char *) * 3);
	tmp = ft_split(str, '=');
	key_value[0] = ft_strdup(tmp[0]);
	key_value[1] = ft_strdup("");
	key_value[2] = 0;
	return (key_value);
}

static int	several_export(t_env **env, char **split, char **key_value, int i)
{
	while (split[++i])
	{
		if (split[i][0] == '=' || (split[i][0] >= '0' && split[i][0] <= '9'))
		{
			print_error_export(split[i]);
			continue ;
		}
		if (split[i][ft_strlen(split[i]) - 1] == '=')
			key_value = create_export_spe(key_value, split[i]);
		else
			key_value = ft_split(split[i], '=');
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
		if (!several_export(env, split, key_value, 0))
			return (0);
		return (1);
	}
	return (0);
}
