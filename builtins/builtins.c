/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:19 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/14 20:56:35 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in(char *str)
{
	if (!*str)
		return (0);
	if (!ft_strncmp(str, "cd\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "export\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "pwd\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "unset\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "env\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "exit\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "echo\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "./minishell\0", ft_strlen(str) + 1))
	{
		return (1);
	}
	return (0);
}

int	is_built_in2(char *str, t_env **env)
{
	if (!*str)
		return (0);
	if (!ft_strncmp(str, "cd\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "export\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "unset\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "exit\0", ft_strlen(str) + 1))
	{
		return (1);
	}
	if (iter_shlvl(str, env))
		return (1);
	return (0);
}

int	pipe_builtins(t_minishell *ms, char **split, t_env **env, int pipe)
{
	(void)ms;
	if (is_built_in(split[0]))
	{
		if (input_env(env, split)
			|| input_cd(split, env) || built_in_pwd(split)
			|| built_in_export(env, split) || built_in_unset(env, split)
			|| !check_write_exit(ms, split, pipe)
			|| built_in_echo(split))
		{
			return (1);
		}
	}
	return (0);
}

int	child_builtins(t_minishell *ms, char **split, t_env **env)
{
	(void)ms;
	if (is_built_in(split[0]))
	{
		if (input_env(env, split)
			|| built_in_pwd(split)
			|| built_in_echo(split))
		{
			return (1);
		}
	}
	return (0);
}

int	parent_builtins(t_minishell *ms, char **split, t_env **env, int pipe)
{
	(void)ms;
	if (is_built_in2(split[0], env))
	{
		rm_quote_last(split);
		if (input_cd(split, env)
			|| built_in_export(env, split)
			|| built_in_unset(env, split)
			|| !check_write_exit(ms, split, pipe))
		{
			return (1);
		}
	}
	return (0);
}
