/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:53 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/20 07:20:35 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_heredoc(t_minishell *ms)
{
	int		i;

	i = 0;
	while (ms->f_name[i])
	{
		unlink(ms->f_name[i]);
		i++;
	}
}

int	here_doc_dollar(t_minishell *ms)
{
	char	*tmp;

	tmp = ms->line_here;
	ms->line_here = ft_strdup(dollar_here_doc(ms, ms->line_here, 0, 0));
	if (!ms->line_here)
		exit_parent("heredoc");
	free(tmp);
	return (1);
}

void	write_line_heredoc(t_minishell *ms, char *w_quote)
{
	int	dollar;

	dollar = 0;
	if (ft_strnstr(ms->line_here, "$", ft_strlen(ms->line_here)) != 0
		&& (!ft_strchr(w_quote, '"') && !ft_strchr(w_quote, '\'')))
		dollar = here_doc_dollar(ms);
	write(ms->infile, ms->line_here, ft_strlen(ms->line_here));
	write(ms->infile, "\n", 1);
	if (!dollar)
		free(ms->line_here);
}

int	here_doc(t_minishell *ms, char *tab, char *w_quote, int count)
{
	unplug_signals();
	set_heredoc_signals();
	ms->infile = open(ms->f_name[count], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ms->infile < 0)
		exit_child(ms, -1);
	while (1)
	{
		ms->line_here = readline("> ");
		if (!ms->line_here)
		{
			ft_printf("warning: here-document delimited by end-of-file (wanted `%s')\
			\n", tab);
			break ;
		}
		if (!ft_strncmp(tab, ms->line_here, ft_strlen(tab))
			&& (ft_strlen(tab) == ft_strlen(ms->line_here)))
			break ;
		write_line_heredoc(ms, w_quote);
	}
	free(ms->line_here);
	close(ms->infile);
	return (1);
}
