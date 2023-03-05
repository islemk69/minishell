/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/28 20:14:11 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

#include "include/minishell.h"

static void	start_minishell(t_minishell *ms, t_env **env)
{
	ms->line = NULL;
	
	while (1)
	{
		if (ms->parsed)
		{
			free(ms->line);
			ms->line = NULL;
		}
		ms->line = readline(PROMPT);
		if (!ms->line[0])
			continue ;
		check_new_line(ms);
		if (builtins(ms, ms->parsed, env))
			continue ;
		add_history(ms->line);
		if (!check_write_exit(ms))
		{
			ft_free_tab(ms->parsed);
			free(ms->line);
			exit(0);
		}
		if (ms->parsed)
			exec_cmd(ms, env);
		//ft_free_tab(ms->parsed); seg fault mshell> "ls" -la | wc
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