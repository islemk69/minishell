/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:22:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/21 16:45:22 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_token(char *str, char c)
{
	int i;
	int token;

	
	token = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == c && str[i - 1] != '\"' && str[i + 1] != '\"'))
			token++;
		i++;
	}
	return (token);
}

char	*quote_2(char *line, char *str)
{
	int		i;
	int		i2;
	char	c;

	str = ft_calloc(sizeof(char), (ft_strlen(line) - 2 + 1));
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
		str = quote_2(line, str);
	else
		return (line);
	return (str);
}

static int del_char(t_minishell *ms)
{
    int size;
    int i;
	int j;
    
    i = 0;
    size = 0;
    while (ms->line[i++])
    {
        if (ms->line[i] != 92 && ms->line[i] != ';')
            size++;
    }
    ms->new_line = ft_gc_malloc(sizeof(char) * (size + 1));
    if (!ms->new_line)
        return (0);
    i = -1;
    j = 0;
    while (ms->line[++i])
    {
        if (ms->line[i] != 92 && ms->line[i] != ';')
            ms->new_line[j++] = ms->line[i];
    }
    ms->new_line[j] = 0;
	return (1);
}

void new(t_minishell *ms, char **space)
{
    int i;
    char **quot;

	i = 0;
	while(space[i])
		i++;
    quot = (char**)ft_gc_malloc(sizeof(char *) * (i + 1));
	ms->parsed = (char **)ft_gc_malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (space[i])
    {
		if((space[i][0] == '\"' || space[i][0] == '\'') && !space[i][1])
			quot[i] = ft_strdup(space[i]);
		else
        	quot[i] = ft_strdup(quote(space[i]));
        i++;
    }
	quot[i] = 0;
    i = 0;
    while (quot[i])
    {
        ms->parsed[i] = ft_strdup(quot[i]);
        i++;
    }
    ms->parsed[i] = 0;
}

int   ft_pipe(t_minishell *ms)
{
    char	**pipe;
	char	**space;
	char	*tmp;
	int		i;
    int		j;
	
    pipe = ft_split_token(ms->new_line);
	if (!pipe)
		return(0);
	ms->joined = (char **)ft_gc_malloc(sizeof(char *) * (ft_strlen(*pipe) + 1));
	j = -1;
    while (pipe[++j])
    {
        space = ft_split(pipe[j], ' ');
        new(ms, space);
		if (!redirection(ms))
			return (0);
		ms->joined[j] = 0;
		i = -1;
		while (ms->parsed[++i])
		{
			tmp = ft_strjoin_gnl(ms->joined[j], ms->parsed[i]);
			ms->joined[j] = ft_strdup(ft_strjoin_gnl(tmp, " "));
		}
		ms->parsed[i] = 0;
    }
	ms->joined[j] = 0;
	return(1);
}



int check_new_line(t_minishell *ms)
{
	char	**space;
    int i;
    
    if (ft_strchr(ms->line, 92) || ft_strchr(ms->line, ';'))
        del_char(ms);
    else
        ms->new_line = ft_strdup(ms->line);
    if (is_token(ms->new_line, '|'))
	{
		if (!ft_pipe(ms))
        	return (0);
		ms->parsed = ft_gc_malloc(sizeof(char *) * (ft_strlen(*ms->joined) + 1));
		i = 0;
		while(ms->joined[i])
		{
			ms->parsed[i] = ft_strdup(ms->joined[i]);
			i++;
		}
	}
    else
	{
		space = ft_split(ms->new_line, ' ');
        new(ms, space);
		if (!redirection(ms))
			return (0);
	}
	return (1);
}