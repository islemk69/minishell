/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:54:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/13 13:10:52 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_key(char *line)
{
	int size = 0;
	char *new_line;
	
	while(line[size] != '=')
		size++;
	new_line = ft_gc_malloc(sizeof(char) * (size + 1));
	size = 0;
	while(line[size] != '=')
	{
		new_line[size] = line[size];
		size++;
	}
	new_line[size] = 0;
	return (new_line);
}

char	*get_value(char *line)
{
	int size = 0;
	int	i = 0;
	char *new_line;
	
	while (line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		size++;
		i++;
	}
	new_line = ft_gc_malloc(sizeof(char) * (size + 1));
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

int	fill_list(t_env **env, char *key, char *value)
{
	t_env *cell;
	
	cell = create_cell(key, value);
	if (!cell)
		return (0);
	ft_lstad_back(env, cell);
	return (1);
}

int	init_env(t_minishell *ms, char **envp)
{
	char	*key;
	char	*value;
	(void)ms;
	char *path;
	int		i;

	i = 0;
	ms->head_env = NULL;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		fill_list(&ms->head_env, key, value);
		i++;
	}
 	path = ft_find_path(&ms->head_env, "PATH");
	if (!path)
		return (0);
	ms->path_env = ft_split(path, ':');
	if (!ms->path_env)
		return (0);
	return (1);
}