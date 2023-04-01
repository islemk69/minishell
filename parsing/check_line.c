/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:22:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 03:30:09 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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

int   ft_pipe(t_minishell *ms)
{
    char	**pipe;
	char	**space;
	char	*tmp;
	int		i;
    int		j;
	
    pipe = ft_split_token(ms->line);
	if (!pipe)
		return(0);
	ms->joined = (char **)ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(pipe) + 1));
	j = 0;
    while (pipe[j])
    {
        space = split_string(pipe[j]);
		if (!redirection(space))
			return (0);
		ms->joined[j] = 0;
		i = 0;
		while (space[i])
		{
			tmp = ft_strjoin_gnl(ms->joined[j], space[i]);
			ms->joined[j] = ft_strdup(ft_strjoin_gnl(tmp, " "));
			i++;
		}
		j++;
    }
	ms->joined[j] = 0;
	return(1);
}

int check_new_line(t_minishell *ms)
{
	char **space;
	//int i = 0;

    if (count_token(ms->line, '|'))
	{
		if (!ft_pipe(ms))
        	return (0);
		ms->parsed = ms->joined;
	}
    else
	{
		space = split_string(ms->line);
		if (!redirection(space))
			return (0);
		ms->parsed = space;
	}
	return (1);
}