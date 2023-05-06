/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:54:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 15:43:56 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	size_get_value(char *line)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*get_value(char *line)
{
	int		size;
	int		i;
	char	*new_line;

	new_line = ft_gc_malloc(sizeof(char) * (size_get_value(line) + 1));
	i = 0;
	size = 0;
	while (line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		new_line[size] = line[i];
		size++;
		i++;
	}
	new_line[size] = 0;
	return (new_line);
}

int	init_env_null(t_minishell *ms, char **envp, int i)
{
	char	*key;
	char	*value;

	if (!envp[i] || !envp)
	{
		while (i < 2)
		{
			if (i == 0)
			{
				key = "PWD";
				value = getcwd(0, 0);
			}
			else if (i == 1)
			{
				key = "SHLVL";
				value = "1";
			}
			fill_list(&ms->head_env, key, value);
			i++;
		}
		ms->prompt = "42@guest>";
		return (1);
	}
	return (0);
}

int	init_env(t_minishell *ms, char **envp)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	ms->head_env = NULL;
	if (init_env_null(ms, envp, i))
		return (1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
			get_prompt(ms, envp[i]);
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		fill_list(&ms->head_env, key, value);
		i++;
	}
	return (1);
}
