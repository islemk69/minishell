/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:19 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/25 23:08:56 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_built_in(char *str)
{
	if (!ft_strncmp(str, "history\0", ft_strlen(str)) 
		|| !ft_strncmp(str, "cd\0", ft_strlen(str)) 
		|| !ft_strncmp(str, "export\0", ft_strlen(str)) 
		|| !ft_strncmp(str, "pwd\0", ft_strlen(str))
		|| !ft_strncmp(str, "unset\0", ft_strlen(str))
		|| !ft_strncmp(str, "!!\0", ft_strlen(str))
		|| (str[0] == '!' && str[1] != '!' && str[1] != ' '))
	{
		ft_printf("je suis un builtin\n");
		return (1);
	}
	return (0);
}


///////////////history/////////////////////
static int	input_history(char **split)
{
	int i;
	
	if (split[0] && !split[1] && !ft_strncmp(split[0], "history\0", 8)) 
	{
		i = 0;
		while (i <= history_length) 
		{
			HIST_ENTRY* entry = history_get(i);
			if (entry != NULL) {
				ft_printf("   %d  %s\n", i, entry->line);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

//////////////////////////////!!!!!!!!!!/////////////////////////
int	input_last_cmd(char **split, t_minishell *ms, t_env **env)
{
	(void)env;
	if (!ft_strncmp(split[0], "!!\0", 3)) 
	{ 
		ft_printf("salut\n");
		HIST_ENTRY *last_entry = history_get(history_length);
		if (last_entry) 
		{
			free(ms->line);
			ms->line = ft_strdup(last_entry->line);
			return (1);
		}
		else
		{
			ft_printf("erreur a mettre \"!!\"\n");
			exit (0);
		}
	} 
	return (0);
}

////////////////////////////!!!!!!!!!!xxxxxxxxx////////////////
int	inputx_index(char **split, t_minishell *ms)
{
	if (split[0] && !split[1] && split[0][0] == '!' && split[0][1] != '!')
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
			ms->line = (char *)index_hist->line;
		}
		return (1);
	}
	return (0);
}

////////////////////////////ENV////////////////////////
static int	input_env(t_env **env, char **split)
{
	t_env 	*head;

	head = *env;
	if (split[0] && !split[1] && !ft_strncmp(split[0], "env\0", 4))
	{
		while (head)
		{
			ft_printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
		return (1);
	}
	return (0);
}

//////////////CCCCCCCCCDDDDDDDDDD////////////
static int	input_cd(char **split, t_env **env)
{
	if (split[0] && !ft_strncmp(split[0], "cd\0", 3))
	{
		if (!split[1])
		{
			if (chdir(ft_find_path(env, "HOME")) == -1)
				ft_printf("erreur a mettre chdir\n");
		}
		else if (chdir(split[1]) == -1 && split[1]) 
			ft_printf("erreur a mettre chdir\n");
		return (1);
	}
	return (0);
}


//////////////////PWD//////////////////////

int	built_in_pwd(char **split)
{
	char cwd[100000];
	
	if (split[0] && !split[1] && !ft_strncmp(split[0], "pwd\0", 4))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s\n", cwd);
		} else {
			perror("getcwd()");
		}
		return (1);
	}
	return (0);
}

///////////////////export//////////

int built_in_export(t_env **env, char **split)
{
	if (!ft_strncmp(split[0], "export\0,", 7) && ft_strchr(split[1], '='))
	{
		t_env	*cell;
		
		char *key = get_key(split[1]);
		char *value = get_value(split[1]);

		cell = create_cell(key, value);
		if (!cell)
		{
			return (0);
		}
		ft_lstad_back(env, cell);
		return (1);
	}
	return (0);
}

////////////////////////unset/////////////////////////////

int built_in_unset(t_env** env, char **cmd) 
{
    t_env* current = *env;
    t_env* previous = NULL;
	
	if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		if (!cmd[1])
			return (1);
		while (current != NULL) 
		{
			if (strcmp(current->key, cmd[1]) == 0) 
			{
				if (previous == NULL) 
					*env = current->next;
				else
					previous->next = current->next;
				return (1);
			}
			previous = current;
			current = current->next;
		}
		return (1);
	}
	return (0);
}

int builtins(t_minishell *ms, char **split, t_env **env)
{
	(void)ms;
	if (input_history(split) || input_env(env, split) 
			|| input_cd(split, env) || built_in_pwd(split) 
			|| built_in_export(env, split) || built_in_unset(env, split))
	{
		return (1);
	}
	return (0);
}