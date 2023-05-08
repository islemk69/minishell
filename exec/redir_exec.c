/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:30:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/09 00:12:36 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *cmd, char *type)
{
	char	*tmp;
	char	*msg;

	tmp = "bash: ";
	msg = ft_strjoin(tmp, cmd);
	msg = ft_strjoin(msg, type);
	write(2, msg, ft_strlen(msg));
}

void	check_redir(t_minishell *ms)
{
	if (ms->infile_stra)
	{
		print_error(ms->infile_stra, ": No Such File Directory\n");
		exit(1);
	}
	if (ms->infile < 0)
	{
		print_error(ms->infile_str, ": Permission denied\n");
		exit (1);
	}
	if (ms->infile > 0)
	{
		if (dup2(ms->infile, 0) == -1)
			error ("dup");
	}
	if (ms->outfile < 0)
	{
		print_error(ms->outfile_str, ": Permission denied\n");
		exit (1);
	}
	if (ms->outfile > 0)
	{
		if (dup2(ms->outfile, 1) == -1)
			error ("dup6");
	}
}
