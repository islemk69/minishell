/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:54:37 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 08:05:58 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rm_quote_last(char **cmds)
{
	char	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = quote(tmp);
		if (!*cmds)
			exit_child_simple(-1);
		cmds++;
	}
}

void	rm_quote_last_parent(char **cmds)
{
	char	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = quote(tmp);
		if (!*cmds)
			exit_parent("builtins");
		cmds++;
	}
}

int	is_token_char(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	iter_shlvl(char *str, t_env **env)
{
	t_env	*head;
	int		shlvl;
	char	*tmp;

	head = *env;
	if (!ft_strncmp(str, "./minishell\0", ft_strlen(str) + 1))
	{
		while (head)
		{
			if (!ft_strncmp(head->key, "SHLVL\0", 6))
			{
				shlvl = ft_atoi(head->value);
				shlvl++;
				tmp = ft_itoa(shlvl);
				if (!tmp)
					exit_parent("builtins");
				head->value = ft_strdup(tmp);
				if (!head->value)
					exit_parent("builtins");
			}
			head = head->next;
		}
		return (1);
	}
	return (0);
}

int	check_key(char *str)
{
	while (*str)
	{
		if ((*str > 64 && *str < 91) || (*str > 96 && *str < 123)
			|| (*str > 47 && *str < 58) || *str == '_')
		{
			str++;
			continue ;
		}
		return (0);
	}
	return (1);
}
