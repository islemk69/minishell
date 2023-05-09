/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:54:37 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/09 19:37:08 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	head = *env;
	if (!ft_strncmp(str, "./minishell\0", ft_strlen(str) + 1))
	{
		while (head)
		{
			if (!ft_strncmp(head->key, "SHLVL\0", 6))
			{
				shlvl = ft_atoi(head->value);
				shlvl++;
				head->value = ft_strdup(ft_itoa(shlvl));
			}
			head = head->next;
		}
		return (1);
	}
	return (0);
}

void	print_error_export(char *split)
{
	ft_dprintf(""RED"bash: export: `%s': not a valid identifier\n"\
				WHITE"", split);
	g_global.g_status = 1;
}
