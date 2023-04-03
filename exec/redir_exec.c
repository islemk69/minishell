/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:30:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/03 18:02:39 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**check_redir(t_minishell *ms, char **tab)
{
	int i;
	char	**realloc;
	int		size;
	int		j;
	char	*tab2;

	j = 0;
	size = 0;
	i = 0;
	access_file(tab);
	while (tab[size])
		size++;
	if (tab[i][0] == '<')
	{
		while (tab[i] && tab[i][0] == '<')
			i++;
		i--;
		if (tab[i][1] == '<')
		{
			tab2 = ft_strjoin(".", tab[i] + 2);
			ms->infile = open(tab2, O_RDONLY);
		}
		if (tab[i][1] != '<')
			ms->infile = open(tab[i] + 1, O_RDONLY);
		if (ms->infile < 0)
		{
			ft_dprintf(""RED"bash: %s: No such file or directory\n", ms->parsed[i]);
			exit (0);
		}
		if (dup2(ms->infile, 0) == -1)
			error ("dup");
		i++;
	}
	while (tab[i] && tab[i][0] == '>')
		i++;
	i--;
	if (tab[i][0] == '>')
	{
		ms->outfile_exist = 1;
		if (tab[i][1] == '>')
			ms->outfile = open(tab[i] + 2, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			ms->outfile = open(tab[i] + 1, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(ms->outfile, 1) == -1)
			error ("dup6");
	}
	realloc = ft_gc_malloc(sizeof(char *) * (size - i));
	i++;
	while (tab[i])
	{
		realloc[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	realloc[j] = 0;
	return (realloc);
}
