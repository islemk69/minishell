/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:49 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/21 21:42:22 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_infile_pipe(t_minishell *ms, char **tab, int i, int *cpt)
{
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
			*cpt += 1;
		i++;
	}
	*cpt -= 1;
	if (tab[i - 1][1] == '<')
	{
		tab[i - 1] = quote(tab[i - 1]);
		ms->infile = open(ms->f_name[(*cpt)], O_RDONLY);
		*cpt += 1;
		if (ms->infile < 0)
			ms->infile_str = tab[i - 1] + 2;
	}
	if (tab[i - 1][1] != '<')
	{
		tab[i - 1] = quote(tab[i - 1]);
		ms->infile = open(tab[i - 1] + 1, O_RDONLY);
		if (ms->infile < 0)
			ms->infile_str = tab[i - 1] + 1;
	}
	return (i);
}

int	open_outfile_pipe_check(t_minishell *ms, char **tab, int i)
{
	if (tab[i][1] == '>')
	{
		tab[i] = quote(tab[i]);
		ms->outfile = open(tab[i] + 2, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (access(tab[i] + 2, W_OK) == -1)
		{
			ms->outfile_str = tab[i] + 2;
			return (1);
		}
	}
	else
	{
		tab[i] = quote(tab[i]);
		ms->outfile = open(tab[i] + 1, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (access(tab[i] + 1, W_OK) == -1)
		{
			ms->outfile_str = tab[i] + 1;
			return (1);
		}
	}
	return (0);
}

int	open_outfile_pipe(t_minishell *ms, char **tab, int i)
{
	while (tab[i] && tab[i][0] == '>')
	{
		ms->outfile_exist = 1;
		if (open_outfile_pipe_check(ms, tab, i))
			break ;
		i++;
	}
	return (i);
}

char	**open_files(t_minishell *ms, char **tab, int *cpt)
{
	int		i;

	i = 0;
	access_file(ms, tab);
	if (tab[i] && tab[i][0] == '<')
	{
		i = open_infile_pipe(ms, tab, i, &*cpt);
	}
	if (tab[i] && tab[i][0] == '>')
	{
		i = open_outfile_pipe(ms, tab, i);
	}
	if (tab[i] && (tab[i][0] == '>' || tab[i][0] == '<'))
	{
		i = 0;
		while (tab[i] && (tab[i][0] == '>' || tab[i][0] == '<'))
			i++;
	}
	if (!tab[i])
		return (NULL);
	rm_quote_last(tab);
	i--;
	return (ft_realloc_from_i(tab, ft_strlen_dtab(tab), i));
}
