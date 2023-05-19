/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 07:29:57 by hamza             #+#    #+#             */
/*   Updated: 2023/05/17 08:19:53 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*assign_name(t_minishell *ms, int count)
{
	int		nb;
	char	*tab;

	nb = 2147483647;
	tab = ft_itoa(nb);
	if (!tab)
		exit_parent("filename heredoc");
	tab = ft_strjoin_gnl(".", tab);
	if (!tab)
		exit_parent("filename heredoc");
	nb--;
	while (access(tab, F_OK) != -1 || !name_exist(ms, tab, count))
	{
		tab = ft_itoa(nb);
		if (!tab)
			exit_parent("filename heredoc");
		tab = ft_strjoin_gnl(".", tab);
		if (!tab)
			exit_parent("filename heredoc");
		nb--;
	}
	return (tab);
}

void	init_fname(t_minishell *ms, int pipe)
{
	int	i;
	int	size;

	i = 0;
	if (!pipe)
		size = size_file_name_simple(ms);
	else
		size = size_file_name_pipe(ms);
	ms->f_name = ft_calloc_parent(sizeof(char *), size + 1, "filename heredoc");
	while (i < size)
	{
		ms->f_name[i] = 0;
		i++;
	}
}

void	do_assign_pipe(t_minishell *ms, char **split, int *k)
{
	int		j;
	char	*tab;

	j = 0;
	while (split[j] && split[j][0] == '<')
	{
		if (split[j][1] == '<')
		{
			tab = assign_name(ms, *k);
			ms->f_name[*k] = ft_strdup(tab);
			if (!ms->f_name[*k])
				exit_parent("filename heredoc");
			*k += 1;
		}
		j++;
	}
}

void	file_name_pipe(t_minishell *ms, int i, int pipe)
{
	int		k;
	char	**split;

	i = -1;
	k = 0;
	init_fname(ms, pipe);
	while (ms->parsed[++i])
	{
		split = ft_split_space(ms->parsed[i]);
		if (!split)
		{
			exit_parent("File name");
		}
		do_assign_pipe(ms, split, &k);
	}
}

void	file_name_simple(t_minishell *ms, int pipe)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	init_fname(ms, pipe);
	while (ms->parsed[i] && ms->parsed[i][0] == '<' && ms->parsed[i][1] == '<')
	{
		if (ms->parsed[i][1] == '<')
		{
			tab = assign_name(ms, j);
			ms->f_name[j] = ft_strdup(tab);
			j++;
		}
		i++;
	}
}
