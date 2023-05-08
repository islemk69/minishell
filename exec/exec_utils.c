/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 14:28:19 by ikaismou         ###   ########.fr       */
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
	if ((input_cmd[0] == '/' || (input_cmd[0] == '.' && input_cmd[1] == '/')) || (input_cmd[ft_strlen(input_cmd) - 1] == '/'))
	{
		if (stat(input_cmd, &info) == 0 && S_ISDIR(info.st_mode)) 
		{
			print_error(input_cmd,  ": Is a directory\n");
			exit(126);
		}
		if (access(input_cmd, F_OK) == 0)
		{
			if (access(input_cmd, X_OK | R_OK) != 0)
			{
				print_error(input_cmd,  ": Permission denied\n");
				exit (126);
			}
			ms->path_cmd = input_cmd;
			return (1);
		}
		else 
		{
			if (access(input_cmd, F_OK) != 0)
			{
				print_error(input_cmd,  ": No such file or directory\n");
				exit(127);
			}
			if (access(input_cmd, X_OK | R_OK) != 0)
			{
				print_error(input_cmd,  ": Permission denied\n");
				exit (126);
			}
			ms->path_cmd = input_cmd;
			return (1);
		}
		return (0);
	}
	if (is_built_in(input_cmd))
		return (1);
	if (!ms->path_env || !*input_cmd)
	{
		print_error(input_cmd,  ": command not found\n");
		exit(127);
	}
	while (ms->path_env[i])
	{
		tmp = ft_strjoin_gnl(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin_gnl(tmp, input_cmd);
		if (access(ms->path_cmd, X_OK) != -1 )
			return (1);
		i++;
	}
	print_error(input_cmd,  ": command not found\n");
	exit(127);
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


void	access_file2(t_minishell *ms)
{
	int	i;
	char	*tab2;
	i = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			ms->parsed[i] = quote(ms->parsed[i]);
			tab2 = ft_strjoin(".", ms->parsed[i] + 2);
			if (access(tab2, F_OK) != 0)
			{
				print_error(ms->parsed[i] + 2,  ": No such file or directory\n");
				exit (1);
			}
		}
		else
		{
			ms->parsed[i] = quote(ms->parsed[i]);
			if (access(ms->parsed[i] + 1, F_OK) != 0)
			{
				print_error(ms->parsed[i] + 1,  ": No such file or directory\n");
				exit (1);
			}
		}
		i++;
	}
}


void	access_file(char **tab, t_minishell *ms)
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
				ms->infile_stra = tab[i] + 2;
				break ;
			}
		}
		else if (access(tab[i] + 1, F_OK) != 0)
		{
			ms->infile_stra = tab[i] + 1;
			break ;
		}
		i++;
	}
}
