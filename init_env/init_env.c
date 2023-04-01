/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:54:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 15:11:37 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char* strcpy_no_null(char* dest, const char* src) {
    char* ret = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    return ret;
}

void get_prompt(t_minishell *ms, char *envp)
{
	char *prompt;
	int i = 3;
	
	prompt = envp + 5;
	ms->prompt = ft_gc_malloc(sizeof(char) * (ft_strlen(prompt)) + 5);
	ms->prompt = strcpy_no_null(ms->prompt, "42@");
	while (*prompt)
	{
		ms->prompt[i] = *prompt;
		i++;
		prompt++;
	}
	ms->prompt[i] = '>';
	i++;
	ms->prompt[i] = 0;
}

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
	int		i;

	i = 0;
	ms->head_env = NULL;
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