/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:53 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/05 17:52:57 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_heredoc(char **tab)
{
	int		i;
	char	*tab2;
	
	i = 0;
	while (tab[i] && tab[i][0] == '<')
	{
		if (tab[i][1] == '<')
		{
			tab2 = ft_strjoin(".", tab[i] + 2);
			unlink(tab2);
		}
		i++;
	}
}

 

int	here_doc(t_minishell *ms, char *tab, char *w_quote)
{
	int		dollar;
	char	*tab2;
	char	*tmp;
	
	set_heredoc_signals();
	tab2 = ft_strjoin(".", tab);
	ms->infile = open(tab2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		dollar = 0;
		ms->line_here = readline(">");
		if (!ms->line_here)
			return (free(ms->line_here), 0);
		if (!ft_strncmp(tab, ms->line_here, ft_strlen(tab))
				&& (ft_strlen(tab) == ft_strlen(ms->line_here)))
			break ;
		if (ft_strnstr(ms->line_here, "$", ft_strlen(ms->line_here)) != 0
			&& (!ft_strchr(w_quote, '"') && !ft_strchr(w_quote, '\'')))
		{
			dollar = 1;
			tmp = ms->line_here;
			//ms->line_here = ft_strdup(dollar_exist(ms, ms->line_here, 0, 0));
			free(tmp);
		}
		write(ms->infile, ms->line_here, ft_strlen(ms->line_here));
		write(ms->infile, "\n", 1);
		if (!dollar)
			free(ms->line_here);
	}
	free(ms->line_here);
	close(ms->infile);
	return (1);
}