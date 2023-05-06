/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/06 17:59:13 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_exit_status = 0;

int	urandom(char *str)
{
	unsigned char	c;

	if (!str)
		return (0);
	while (*str)
	{
		if (*str < 0)
			return (ft_dprintf(""RED"Your are a Nazi\n"WHITE""), 0);
		c = (unsigned char)*str;
		if (c > 127)
			return (ft_dprintf(""RED"Your are a Nazi\n"WHITE""), 0);
		str++;
	}	
	return (1);
}

static int	start_minishell(t_minishell *ms)
{
	ms->line = NULL;
	ms->parsed = NULL;
	while (1)
	{
		set_interactive_signals();
		ms->line = readline(ms->prompt);
		if (!urandom(ms->line))
			return (free(ms->line), 0);
		if (is_empty(ms->line))
			continue ;
		add_history(ms->line);
		if (!parsing(ms->line, ms))
		{
			printf("error token parsing\n");
			free(ms->line);
			continue ;
		}
		// if (!check_write_exit(ms))
		// 	return (0);
		if (!exec_cmd(ms, &ms->head_env))
			return (free(ms->line), 0);
		free(ms->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argv;
	ms.infile = 0;
		ms.outfile = 0;
		ms.infile_stra = NULL;
		ms.outfile_exist = 0;
	if (argc > 1)
		return (ft_dprintf(""RED"Error : Number of Arguments\n"WHITE""), 0);
	//system(SHELLSCRIPT);
	ms.new_env = NULL;
	init_env(&ms, envp);
	if (!start_minishell(&ms))
	{
		lstclear(&ms.head_env);
		return (ft_gc_free_all(), 0);
	}
	ft_gc_free_all();
	return (0);
}
