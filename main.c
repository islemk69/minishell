/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/08 18:11:45 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	start_minishell(t_minishell *ms, t_env **env)
{
	ms->line = NULL;
	
	while (1)
	{
		ms->line = readline(PROMPT);
		if (!ms->line[0] || only(ms->line))
			continue ;
		check_new_line(ms);
		if (!check_write_exit(ms))
		{
			free(ms->line);
			exit(0);
		}
		ft_free_tab(ms->parsed);
		free(ms->line);
		continue ;
		if (ms->parsed)
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
	start_minishell(&ms, &env);
	return(0);
}