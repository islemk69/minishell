/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/25 17:59:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	start_minishell(char **envp, t_minishell *ms, t_env **env)
{
	char	**split;

	ms->line = NULL;
	while (1)
	{
		if (ms->line)
		{
			free(ms->line);
			ms->line = NULL;
		}
		ms->line = readline(PROMPT);
		if (!ms->line[0])
			continue ;
		split = ft_split(ms->line, ' ');
		if (builtins(ms, split, envp, env))
			continue ;
		ft_printf("Exec\n");
		add_history(ms->line);
		if (!check_write_exit(ms))
		{
			ft_free_tab(split);
			free(ms->line);
			exit(0);
		}
		if (ms->line)
			exec_cmd(ms, envp);
		ft_free_tab(split);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_env		*env;

	(void)(argv);
	if (argc > 1)
		return (perror("Number of Arguments"), 0);
	env = NULL;
	init_env(&ms, envp, &env);
	start_minishell(envp, &ms, &env);
	return(0);
}
