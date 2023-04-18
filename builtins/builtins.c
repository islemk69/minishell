/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:19 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/18 18:40:07 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



int is_built_in(char *str)
{
	if (!*str)
		return (0);
	if (!ft_strncmp(str, "cd\0", ft_strlen(str) + 1) 
		|| !ft_strncmp(str, "export\0", ft_strlen(str) + 1) 
		|| !ft_strncmp(str, "pwd\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "unset\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "env\0", ft_strlen(str) + 1)
		|| !ft_strncmp(str, "exit", ft_strlen(str))
		|| !ft_strncmp(str, "./minishell\0", ft_strlen(str) + 1))
	{
		return (1);
	}
	return (0);
}

int builtins(t_minishell *ms, char **split, t_env **env, int pipe)
{
	(void)ms;
	//rm_quote_last(ms->parsed);
	if (is_built_in(split[0]))
	{
		if (input_env(env, split) 
				|| input_cd(split, env) || built_in_pwd(split) 
				|| built_in_export(env, split) || built_in_unset(env, split)
				|| !check_write_exit(ms, pipe))
		{
			return (1);
		}
	}
	return (0);
}