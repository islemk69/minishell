/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:19:41 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/21 17:20:43 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	custom_msg_check_line(char *line, int pos, char c)
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
	npipe = ft_calloc_parent(sizeof(char), (size + 1), "parsing");
	size = 0;
	while (line[pos] && line[pos] == c)
	{
		npipe[size] = line[pos];
		pos++;
		size++;
	}
	npipe[size] = 0;
	ft_dprintf(""SYNT_ERR" `%s'\n", npipe);
	return (0);
}

int	name_exist(t_minishell *ms, char *tab, int count)
{
	int	i;

	i = 0;
	while (ms->f_name[i] && i < count)
	{
		if (!ft_strncmp(tab, ms->f_name[i], ft_strlen(tab)))
			return (0);
		i++;
	}
	return (1);
}

int	is_full_null(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->realloc[i])
	{
		if (ms->realloc[i][0])
			return (0);
		i++;
	}
	return (1);
}

char	*init_m_dollar(t_minishell *ms, char *str)
{
	char	*new;

	new = ft_calloc_parent(sizeof(char), \
			(countchar_pipe(ms, str, 0, 0) + 1), "parsing");
	return (new);
}

void	ft_close(t_minishell *ms, int mod, int i)
{
	if (!mod)
	{
		if (ms->infile_ok)
			close(ms->infile);
		if (ms->outfile_ok)
			close(ms->outfile);
		ft_gc_free_all();
	}
	else if (mod == 1)
	{
		if (ms->infile_ok)
			close(ms->infile);
		if (ms->outfile_ok)
			close(ms->outfile);
		ft_gc_free_all();
		exit(i);
	}
}
