/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:34:03 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/19 16:54:27 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	start_minishell(char **envp, t_minishell *ms)
{
	int	i;

	while (1)
	{
		free(ms->line);
		ms->line = NULL;
		ms->line = readline(PROMPT);
		/////////////////////HISTORIQUE///////////////
		if (!ms->line[0]) {
			continue ;
        }
		add_history(ms->line);
		if (ms->line && ms->line[0] && !ft_strncmp(ms->line, "history\0", 8)) 
		{
			i = 0;
            while (i < history_length) 
			{
                HIST_ENTRY* entry = history_get(i);
                if (entry != NULL) {
                    ft_printf(" %d %s\n", i, entry->line);
                }
				i++;
            }
			add_history(ms->line);
			free(ms->line);
			ms->line = NULL;
			continue ;
        }
		if (!ft_strncmp(ms->line, "!!\0", 3))
		{
			HIST_ENTRY *last_entry = history_get(history_length - 1);
            if (last_entry) {
				free(ms->line);
                ms->line = last_entry->line;
                add_history(ms->line);
			}
			else //si il n'y a aucune commande dans l'historique
			{
				ft_printf("message d'erreur a mettre\n");
				continue ;
			}
		} 
		if (!ft_strncmp(ms->line, "!5", 2))
		{
			int index;

			index = ft_atoi(&ms->line[1]);//faire un atoi modifier qui zappe ! et prend aue des chiffre
			ft_printf("%d\n", index);            //et rien d'autres
			HIST_ENTRY *index_hist = history_get(index);
            if (index_hist != NULL) {
                ms->line = index_hist->line;
                add_history(ms->line);
			}
		}
		//ft_printf("%s\n", ms->line);
		////////////////////HISTORIQUE////////////////		
		if (!check_write_exit(ms))
			exit(0);
		if (ms->line)
			exec_cmd(ms, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)(argv);
	if (argc > 1)
		return (perror("Number of Arguments"), 0);
	init_env(&ms, envp);
	start_minishell(envp, &ms);
	return(0);
}
