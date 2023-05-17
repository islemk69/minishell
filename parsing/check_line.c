/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 04:34:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 06:28:32 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static int	iter_check_pipe(char *string, char quote, int *i)
{
	while (string[*i] != '\0')
	{
		if (string[*i] == '"' || string[*i] == '\'')
		{
			if (quote == '\0')
				quote = string[*i];
			else if (quote == string[*i])
				quote = '\0';
		}
		else if (string[*i] == '|' && string[*i + 1] == '|' && quote == '\0')
			return (0);
		*i += 1;
	}
	return (1);
}

static int	check_pipe(char *string)
{
	char	quote;
	char	**pipe;
	int		i;

	quote = '\0';
	i = 0;
	pipe = ft_split_token(string, ' ');
	if (!pipe)
		exit_parent("parsing");
	if (pipe[0][0] == '|')
		return (custom_msg_check_line(pipe[0], 0, '|'));
	else if (pipe[ft_strlen_dtab(pipe) - 1][ft_strlen(pipe[ft_strlen_dtab(pipe) \
		- 1]) - 1] == '|')
		return (custom_msg_check_line(pipe[ft_strlen_dtab(pipe) - 1], \
			ft_strlen(pipe[ft_strlen_dtab(pipe) - 1]) - 1, '|'));
	while (pipe[i])
	{
		if (pipe[i][ft_strlen(pipe[i]) - 1] == '|' && pipe[i + 1][0] == '|')
			return (custom_msg_check_line(pipe[i + 1], 0, '|'));
		i++;
	}
	if (!iter_check_pipe(string, quote, &i))
		return (custom_msg_check_line(string, i + 1, '|'));
	return (1);
}

static int	check_wrong_redir(char *string)
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
		else if (string[i] == '<' && string[i + 1] == '<' \
			&& string[i + 2] == '<' && quote == '\0')
			return (custom_msg_check_line(string, i + 2, '<'));
		else if (string[i] == '>' && string[i + 1] == '>' \
			&& string[i + 2] == '>' && quote == '\0')
			return (custom_msg_check_line(string, i + 2, '>'));
		i++;
	}
	return (1);
}

int	check_line(char *line)
{
	if (line[0] == '.' && !line[1])
	{
		ft_dprintf("bash: .: filename argument required\n.: \
			usage: . filename [arguments]\n");
		return (0);
	}
	if (!check_quote(line) || !check_wrong_redir(line) || !check_pipe(line))
		return (0);
	return (1);
}
