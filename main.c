/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/18 13:27:36 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

	#define SHELLSCRIPT "\
	#/bin/bash \n\
	echo -e \""PURPLE"        .__       .__       .__           .__  .__   \n  _____ |__| ____ |__| _____|  |__   ____ |  | |  |  \n /     \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |  \n|  Y Y  \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  |__\n|__|_|  /__|___|  /__/____  >___|  /\\___  >____/____/\n      \\/        \\/        \\/     \\/     \\/           \" \n\
	"

static int	start_minishell(t_minishell *ms)
{
	ms->line = NULL;
	ms->parsed = NULL;

    system(SHELLSCRIPT);
	while (1)
	{
		// ft_printf("okok");
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
		add_history(ms->line);
		if (!check_write_exit(ms))
			return (free(ms->line), 0);

		exec_cmd(ms, &ms->head_env);
		free(ms->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argv;
	if (argc > 1)
		return (ft_dprintf(""RED"Error : Number of Arguments\n"CYAN""), 0);
	init_env(&ms, envp);
	if (!start_minishell(&ms))
		return (ft_gc_free_all(), 0);
	return(0);
}