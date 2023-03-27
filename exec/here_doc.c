/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:53 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/27 15:56:24 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_heredoc(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
			unlink(tab[i] + 2);
		i++;
	}
}

int	here_doc(t_minishell *ms, char *tab)
{
	ms->infile = open(tab, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		g_exit_status = 1;
		ms->line_here = readline(">");
		if (!ms->line_here)
			return (free(ms->line_here), 0);
		if (!ft_strncmp(tab, ms->line_here, ft_strlen(tab))
				&& (ft_strlen(tab) == ft_strlen(ms->line_here)))
			break ;
		write(ms->infile, ms->line_here, ft_strlen(ms->line_here));
		write(ms->infile, "\n", 1);
		free(ms->line_here);
	}
	free(ms->line_here);
	close(ms->infile);
	return (1);
}