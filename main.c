/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/11 22:30:25 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	start_minishell(t_minishell *ms, t_env **env)
{
	ms->line = NULL;
	ms->parsed = NULL;
	
	while (1)
	{
		if (ms->line != NULL)
			free(ms->line);
		ms->line = readline(PROMPT);
		if (is_empty(ms->line))
			continue ;
		check_new_line(ms);
		if (!check_write_exit(ms))
			return (0);
		int i = 0;
		while (ms->parsed[i])
		{
			ft_printf("%s\n", ms->parsed[i]);
			i++;
		}
		continue ;
		exec_cmd(ms, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_env		*env;

	(void)argv;
	if (argc > 1)
		return (perror("Number of Arguments"), 0);
	env = NULL;
	init_env(&ms, envp, &env);
	if (!start_minishell(&ms, &env))
		return (ft_gc_free_all(), 0);
	ft_gc_free_all();
	return(0);
}