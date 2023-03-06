/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/06 19:45:14 by hel-ouar         ###   ########.fr       */
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
			ft_printf("jesuispasse\n");
			ms->line = NULL;
		}
		ms->line = readline(PROMPT);
		if (!ms->line[0])
		{
			continue ;
		}
		check_new_line(ms);
		int i = 0;
		while (ms->parsed[i])
		{
			ft_printf("%s\n", ms->parsed[i]);
			i++;
		}
		continue ;
		if (!check_write_exit(ms))
		{
			ft_free_tab(ms->parsed);
			free(ms->line);
			exit(0);
		}
		if (ms->parsed)
			exec_cmd(ms, env);
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