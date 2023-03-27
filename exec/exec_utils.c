/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/27 17:49:05 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_command(t_minishell *ms, char *input_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->path_env[i])
	{
		tmp = ft_strjoin(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin(tmp, input_cmd);
		if (access(ms->path_cmd, X_OK) != -1 || is_built_in(input_cmd))
			return (1);
		i++;
	}
	return (0);
}

int count_pipe(t_minishell *ms)
{
	int	pipe;
	int i;

	i = 0;
	pipe = 0;
	while (ms->line[i])
	{
		if (ms->line[i] == '|' && ms->line[i - 1] != '\"' && ms->line[i + 1] != '\"')
			pipe++;
		i++;
	}
	return (pipe);
}

void	access_file(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
		{
			if (access(tab[i] + 2, F_OK) != 0)
			{
				ft_dprintf(""RED"bash: %s: No such file or directory"WHITE"\n", tab[i] + 2);
				exit (0);
			}
		}
		else if (access(tab[i] + 1, F_OK) != 0)
		{
			ft_dprintf(""RED"bash: %s: No such file or directory"WHITE"\n", tab[i] + 1);
			exit (0);
		}
		i++;
	}
}