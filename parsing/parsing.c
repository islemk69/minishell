/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:22:52 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/05 17:16:22 by ikaismou         ###   ########.fr       */
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

char **ft_pipe(char *line)
{
    char	**pipe;
	char	**space;
	char	**join;
	int		i;
    int		j;
	
    pipe = ft_split_token(line, '|');
	if (!pipe)
		return(0);
	join = (char **)ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(pipe) + 1));
	j = -1;
    while (pipe[++j])
    {
        space = ft_split_token(pipe[j], ' ');
		space = redirection(space);
		if (!space)
			return (0);
		join[j] = 0;
		i = -1;
		while (space[++i])
		{
			join[j] = ft_strjoin_gnl(join[j], space[i]);
			join[j] = ft_strdup(ft_strjoin_gnl(join[j], " "));
		}
    }
	join[j] = 0;
	return (join);
}

int parsing(char *line, t_minishell *ms)
{
	char **space;
	if(!check_line(line))
		return(0);
    if (count_token(line, '|'))
	{
		ms->parsed = ft_pipe(line);
		if (!ms->parsed)
        	return (0);
	}
    else
	{
		space = ft_split_token(line, ' ');
		ms->parsed = redirection(space);
		if (!ms->parsed)
			return (0);
	}
	check_dollar(ms);
	//int i = 0;
	//while (ms->parsed[i])
	//{
	//	printf("%s\n", ms->parsed[i]);
	//	i++;
	//}
	return (1);
}