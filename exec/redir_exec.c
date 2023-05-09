/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:30:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/10 00:24:53 by hel-ouar         ###   ########.fr       */
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

int	error_exit(char *cmd, char *type, int i)
{
	char	*tmp;
	char	*msg;

	tmp = "bash: ";
	msg = ft_strjoin(tmp, cmd);
	msg = ft_strjoin(msg, type);
	write(2, msg, ft_strlen(msg));
	ft_gc_free_all();
	exit(i);
}

void	check_redir(t_minishell *ms)
{
	if (ms->infile_stra)
		error_exit(ms->infile_stra, ": No such file or directory\n", 1);
	if (ms->infile < 0)
		error_exit(ms->infile_str, ": Permission denied\n", 1);
	if (ms->infile > 0)
	{
		if (dup2(ms->infile, 0) == -1)
			error ("dup");
	}
	if (ms->outfile < 0)
		error_exit(ms->outfile_str, ": Permission denied\n", 1);
	if (ms->outfile > 0)
	{
		if (dup2(ms->outfile, 1) == -1)
			error ("dup6");
	}
}
