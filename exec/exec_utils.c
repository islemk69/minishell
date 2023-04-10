/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/11 00:36:54 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_path(t_minishell *ms)
{
	char *path;
	
	path = ft_find_path(&ms->head_env, "PATH");
	if (!path)
	{
		ms->path_env = NULL;
		return (0);
	}
	ms->path_env = ft_split(path, ':');
	if (!ms->path_env)
		return (0);
	return (1);
}

int	check_command(t_minishell *ms, char *input_cmd)
{
	char	*tmp;
	int		i;
	struct stat info;

	i = 0;
	if (!ms->path_env || !*input_cmd)
		return (0);
	if (input_cmd[0] == '/' || (input_cmd[0] == '.' && input_cmd[1] == '/'))
	{
		if (stat(input_cmd, &info) == 0 && S_ISDIR(info.st_mode)) 
			ft_dprintf(""RED"bash: %s: Is a directory\n"WHITE"", input_cmd);
		else 
		{
			if (access(input_cmd, X_OK) != -1)
			{
				ms->path_cmd = input_cmd;
				return (1);
			}
			ft_dprintf(""RED"bash: %s: command not found"WHITE"\n", input_cmd);
		}
		return (0);
	}
	while (ms->path_env[i])
	{
		tmp = ft_strjoin(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin(tmp, input_cmd);
		if (is_built_in(input_cmd) || access(ms->path_cmd, X_OK) != -1 )
			return (1);
		i++;
	}
	return (0);
}


int	count_token(char *str, char c)
{
	int	count;
	bool	in_quotes;
	char	current_quote;

	count = 0;
	in_quotes = false;
	current_quote = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (in_quotes && *str == current_quote)
			{
				in_quotes = false;
				current_quote = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = true;
				current_quote = *str;
			}
		}
		else if (*str == c && !in_quotes)
			count++;
		str++;
	}
	return (count);
}

void	access_file(char **tab)
{
	int	i;
	char	*tab2;
	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
		{
			tab2 = ft_strjoin(".", tab[i] + 2);
			if (access(tab2, F_OK) != 0)
			{
				ft_dprintf(""RED"bash: %s: No such file or directory\n"WHITE"", tab[i] + 2);
				exit (0);
			}
		}
		else if (access(tab[i] + 1, F_OK) != 0)
		{
			ft_dprintf(""RED"bash: %s: No such file or directory\n"WHITE, tab[i] + 1);
			exit (0);
		}
		i++;
	}
}
