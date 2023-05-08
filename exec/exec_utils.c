/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:15 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 00:22:11 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_path(t_minishell *ms)
{
	char	*path;

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
	char		*tmp;
	int			i;
	struct stat	info;

	i = 0;
	if ((input_cmd[0] == '/' || (input_cmd[0] == '.' && input_cmd[1] == '/')) \
		|| (input_cmd[ft_strlen(input_cmd) - 1] == '/'))
	{
		if (stat(input_cmd, &info) == 0 && S_ISDIR(info.st_mode))
		{
			print_error(input_cmd, ": Is a directory\n");
			exit(126);
		}
		if (access(input_cmd, F_OK) == 0)
		{
			if (access(input_cmd, X_OK | R_OK) != 0)
			{
				print_error(input_cmd, ": Permission denied\n");
				exit (126);
			}
			ms->path_cmd = input_cmd;
			return (1);
		}
		else
		{
			if (access(input_cmd, F_OK) != 0)
			{
				print_error(input_cmd, ": No such file or directory\n");
				exit(127);
			}
			if (access(input_cmd, X_OK | R_OK) != 0)
			{
				print_error(input_cmd, ": Permission denied\n");
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
		print_error(input_cmd, ": command not found\n");
		exit(127);
	}
	while (ms->path_env[i])
	{
		tmp = ft_strjoin_gnl(ms->path_env[i], "/");
		ms->path_cmd = ft_strjoin_gnl(tmp, input_cmd);
		if (access(ms->path_cmd, X_OK) != -1)
			return (1);
		i++;
	}
	print_error(input_cmd, ": command not found\n");
	exit(127);
	return (0);
}

int	count_token(char *str, char c)
{
	int		count;
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
	int		i;
	char	*tab2;
	char	**head;

	i = 0;
	head = ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(ms->parsed) + 1));
	while (ms->parsed[i])
	{
		head[i] = ft_strdup(ms->parsed[i]);
		i++;
	}
	i = 0;
	while (head[i] && head[i][0] == '<')
	{
		if (head[i][1] == '<')
		{
			head[i] = quote(head[i]);
			tab2 = ft_strjoin(".", head[i] + 2);
			if (access(tab2, F_OK) != 0)
			{
				print_error(head[i] + 2, ": No such file or directory\n");
				exit (1);
			}
		}
		else
		{
			head[i] = quote(head[i]);
			if (access(head[i] + 1, F_OK) != 0)
			{
				print_error(head[i] + 1, ": No such file or directory\n");
				exit (1);
			}
		}
		i++;
	}
}

void	access_file(t_minishell *ms, char **tab)
{
	int		i;
	char	*tab2;
	char	**head;

	i = 0;
	head = ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(tab) + 1));
	while (tab[i])
	{
		head[i] = ft_strdup(tab[i]);
		i++;
	}
	i = 0;
	while (head[i] && head[i][0] == '<')
	{
		if (head[i][1] == '<')
		{
			head[i] = quote(head[i]);
			tab2 = ft_strjoin(".", head[i] + 2);
			if (access(tab2, F_OK) != 0)
			{
				ms->infile_stra = head[i] + 2;
				break ;
			}
		}
		else
		{
			head[i] = quote(head[i]);
			if (access(head[i] + 1, F_OK) != 0)
			{
				ms->infile_stra = head[i] + 1;
				break ;
			}
		}
		i++;
	}
}
