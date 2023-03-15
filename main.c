/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/15 13:29:28 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	start_minishell(t_minishell *ms)
{
	ms->line = NULL;
	ms->parsed = NULL;
	
	while (1)
	{
		ms->line = readline(PROMPT);
		if (is_empty(ms->line))
			continue ;
		check_new_line(ms);
		int i = 0;
		while (ms->parsed[i])
		{
			ft_printf("%s\n", ms->parsed[i]);
			i++;
		}
		if (!check_write_exit(ms))
			return (free(ms->line), 0);
		continue ;
		free(ms->line);
		exec_cmd(ms, &ms->head_env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argv;
	if (argc > 1)
		return (ft_dprintf("Error : Number of Arguments\n"), 0);
	init_env(&ms, envp);
	if (!start_minishell(&ms))
		return (ft_gc_free_all(), 0);
	return(0);
}