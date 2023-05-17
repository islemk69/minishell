/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:22:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 06:46:44 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_2(char *line, char *str)
{
	int		i;
	int		i2;
	char	c;

	str = ft_calloc(sizeof(char), (ft_strlen(line) - 2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	i2 = 0;
	while (line[i2])
	{
		if (line[i2] && ft_strchr("\'\"", line[i2]))
		{
			c = line[i2++];
			while (line[i2] && line[i2] != c)
				str[i++] = line[i2++];
			i2++;
		}
		else if (line[i2])
			str[i++] = line[i2++];
	}
	str[i] = 0;
	return (str);
}

char	*quote(char *line)
{
	char	*str;

	str = NULL;
	if (!line)
		return (0);
	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
	{
		str = quote_2(line, str);
		if (!str)
			return(NULL);
	}
	else
		return (line);
	return (str);
}

char	**ft_pipe(char *line, int j)
{
	char	**pipe;
	char	**space;
	char	**join;
	int		i;
	char	*tmp;

	pipe = ft_split_token(line, '|');
	if (!pipe)
		exit_parent("parsing");
	join = ft_calloc_parent(sizeof(char *), \
		(ft_strlen_dtab(pipe) + 1), "parsing");
	while (pipe[++j])
	{
		space = ft_split_token(pipe[j], ' ');
		if (!space)
			exit_parent("parsing");
		space = redirection(space);
		if (!space)
			return (0);
		join[j] = 0;
		i = -1;
		while (space[++i])
		{
			join[j] = ft_strjoin_gnl(join[j], space[i]);
			if (!join[j])
				exit_parent("parsing");
			tmp = ft_strjoin_gnl(join[j], " ");
			if (!tmp)
				exit_parent("parsing");
			join[j] = ft_strdup(tmp);
			if (!join[j])
				exit_parent("parsing");
		}
	}
	return (join[j] = 0, join);
}

int	parsing(char *line, t_minishell *ms)
{
	char	**space;

	if (!check_line(line))
		return (0);
	if (count_token(line, '|'))
	{
		ms->parsed = ft_pipe(line, -1);
		if (!ms->parsed)
			return (0);
	}
	else
	{
		space = ft_split_space(line);
		if (!space)
			exit_parent("parsing");
		ms->parsed = redirection(space);
		if (!ms->parsed)
			return (0);
	}
	check_dollar(ms);
	return (1);
}
