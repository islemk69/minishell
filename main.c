/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/11 16:55:30 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	start_minishell(t_minishell *ms, t_env **env)
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
		{
			free(ms->line);
			if (ms->parsed)
				ft_free_tab(ms->parsed);
			lstclear(env);
			exit(0);
		}
		exec_cmd(ms, env);
		//free(ms->line);
		//ft_free_tab(ms->parsed);
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