/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:19 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/24 00:07:50 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	input_history(char **split, t_minishell *ms)
{
	int i;
	
	if (split[0] && !split[1] && !ft_strncmp(split[0], "history\0", 8)) 
	{
		i = 0;
		add_history(ms->line);
		while (i <= history_length) 
		{
			HIST_ENTRY* entry = history_get(i);
			if (entry != NULL) {
				ft_printf("   %d  %s\n", i, entry->line);
			}
			i++;
		}
		free(ms->line);
		ft_free_tab(split);
		ms->line = NULL;
		return (1);
	}
	return (0);
}

static int	input_last_cmd(char **split, t_minishell *ms, char **envp)
{
	if (split[0] && !split[1] && !ft_strncmp(split[0], "!!\0", 3))
	{
		HIST_ENTRY *last_entry = history_get(history_length);
		if (last_entry) 
		{
			free(ms->line);
			ms->line = last_entry->line;
			add_history(ms->line);
			ft_printf("%s\n", ms->line);
			if (ms->line)
				exec_cmd(ms, envp);
			free(ms->line);
			ft_free_tab(split);
			ms->line = NULL;
			return (1);
		}
		else
		{
			ft_printf("message d'erreur a mettre\n");
			ft_free_tab(split);
			return (1);
		}
	} 
	return (0);
}

static int	inputx_index(char **split, t_minishell *ms, char **envp)
{
	if (split[0] && !split[1] && split[0][0] == '!')
	{
		int index;

		*split += 1;
		index = ft_atoi(split[0]);
		if (index > history_length)
		{
			printf("erreur a mette\n");
			return (1);
		}
		HIST_ENTRY *index_hist = history_get(index);
		if (index_hist != NULL) {
			ms->line = index_hist->line;
			add_history(ms->line);
		}
		if (ms->line)
			exec_cmd(ms, envp);
		free(ms->line);
		ft_free_tab(split);
		ms->line = NULL;
		return (1);
	}
	return (0);
}

static int	input_env(char **env, char **split, t_minishell *ms)
{
	int		i;

	i = 0;
	if (split[0] && !split[1] && !ft_strncmp(split[0], "env\0", 4))
	{
		while (env[i])
		{
			ft_printf("%ssalut\n", env[i]);
			i++;
		}
		free(ms->line);
		ft_free_tab(split);
		ms->line = NULL;
		return (1);
	}
	return (0);
}

static int	input_cd(char **split, char **envp)
{
	if (split[0] && !ft_strncmp(split[0], "cd\0", 3))
	{
		if (!split[1])
		{
			if (chdir(ft_find_path(envp, "HOME")) == -1)
				ft_printf("erreur a mettre chdir\n");
		}
		else if (chdir(split[1]) == -1 && split[1]) 
			ft_printf("erreur a mettre chdir\n");
		return (1);
	}
	return (0);
}


int builtins(t_minishell *ms, char **split, char **envp)
{
	if (input_history(split, ms) || input_last_cmd(split, ms, envp) || inputx_index(split, ms, envp) || input_env(envp, split, ms) || input_cd(split, envp))
		return (1);
	return (0);
}