/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 04:34:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 16:59:38 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	custom_msg(char *line, int pos, char c)
{
	char	*npipe;
	int		size;
	int		save;

	save = pos;
	size = 0;
	while (line[save] && line[save] == c)
	{
		size++;
		save++;
	}
	npipe = ft_gc_malloc(sizeof(char) * (size + 1));
	size = 0;
	while (line[pos] && line[pos] == c)
	{
		npipe[size] = line[pos];
		pos++;
		size++;
	}
	npipe[size] = 0;
	ft_dprintf(""RED""SYNT_ERR" `%s'\n"WHITE"", npipe);
	return (0);
}

static int	check_quote(char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (double_quote == 0 || (double_quote == 1 && str[i - 1] == '\\'))
				single_quote = (single_quote + 1) % 2;
		}
		else if (str[i] == '\"')
		{
			if (single_quote == 0 || (single_quote == 1 && str[i - 1] == '\\'))
				double_quote = (double_quote + 1) % 2;
		}
		i++;
	}
	if (single_quote == 0 && double_quote == 0)
		return (1);
	return (ft_dprintf(""RED"bash: syntax error \
			quote not closed \"'\" or '\"'\n"WHITE""), 0);
}

static int	check_pipe(char* string) 
{
	char	quote;
	char	**pipe;
	int		i;

	quote = '\0';
	i = 0;
	pipe = ft_split_token(string, ' ');
	if(pipe[0][0] == '|')
		return(custom_msg(pipe[0], 0, '|'));
	else if (pipe[ft_strlen_dtab(pipe) - 1][ft_strlen(pipe[ft_strlen_dtab(pipe) - 1]) - 1] == '|') 
		return (custom_msg(pipe[ft_strlen_dtab(pipe) - 1], ft_strlen(pipe[ft_strlen_dtab(pipe) - 1]) - 1 , '|'));
	while (pipe[i])
	{
		if (pipe[i][ft_strlen(pipe[i]) - 1] == '|' && pipe[i + 1][0] == '|')
			return (custom_msg(pipe[i + 1], 0, '|'));
		i++;
	}
	while (string[i] != '\0') 
	{
		if (string[i] == '"' || string[i] == '\'') 
		{
			if (quote == '\0') 
				quote = string[i];
			else if (quote == string[i]) 
				quote = '\0';
		} 
		else if (string[i] == '|' && string[i+1] == '|' && quote == '\0')
			return (custom_msg(string, i + 1, '|'));
		i++;
	}
	return (1);
}

static int	check_wrong_redir(char* string) 
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (string[i] != '\0') 
	{
		if (string[i] == '"' || string[i] == '\'') 
		{
			if (quote == '\0') 
				quote = string[i];
			else if (quote == string[i]) 
				quote = '\0';
		} 
		else if (string[i] == '<' && string[i+1] == '<'  && string[i+2] == '<' && quote == '\0')
			return (custom_msg(string, i + 2, '<'));
		else if (string[i] == '>' && string[i+1] == '>'  && string[i+2] == '>' && quote == '\0')
			return (custom_msg(string, i + 2, '>'));
		i++;
	}
	return (1);
}

int	check_line(char *line)
{
	if (line[0] == '.' && !line[1])
	{
		ft_dprintf("bash: .: filename argument required\n.: usage: . filename [arguments]\n");
		return (0);
	}
	if (!check_quote(line) || !check_wrong_redir(line) || !check_pipe(line))
		return (0);
	return (1);
}
