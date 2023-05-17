/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:54:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 05:42:53 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strcpy_no_null(char *dest, const char *src)
{
	char	*ret;

	ret = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	return (ret);
}

void	get_prompt(t_minishell *ms, char *envp)
{
	char	*prompt;
	int		i;

	i = 3;
	prompt = envp + 5;
	ms->prompt = ft_calloc_parent(sizeof(char), (ft_strlen(prompt)) + 6, "prompt");
	ms->prompt = strcpy_no_null(ms->prompt, "42@");
	while (*prompt)
	{
		ms->prompt[i] = *prompt;
		i++;
		prompt++;
	}
	ms->prompt[i] = '>';
	i++;
	ms->prompt[i] = ' ';
	i++;
	ms->prompt[i] = 0;
}

char	*get_key(char *line)
{
	int		size;
	char	*new_line;

	size = 0;
	while (line[size] != '=')
		size++;
	new_line = ft_calloc_parent(sizeof(char), (size + 1), "get key");
	size = 0;
	while (line[size] != '=')
	{
		new_line[size] = line[size];
		size++;
	}
	new_line[size] = 0;
	return (new_line);
}

int	fill_list(t_env **env, char *key, char *value)
{
	t_env	*cell;

	cell = create_cell(key, value);
	if (!cell)
		return (0);
	ft_lstad_back(env, cell);
	return (1);
}
