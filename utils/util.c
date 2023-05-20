/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:37:56 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/20 06:29:56 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_i_k(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

int	size_file_name_simple(t_minishell *ms)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ms->parsed[i] && ms->parsed[i][0] == '<')
	{
		if (ms->parsed[i][1] == '<')
			count++;
		i++;
	}
	return (count);
}

int	size_file_name_pipe(t_minishell *ms)
{
	char	**split;
	int		j;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ms->parsed[i])
	{
		split = ft_split_space(ms->parsed[i], 0);
		if (!split)
			exit_parent("filename heredoc");
		j = 0;
		while (split[j] && split[j][0] == '<')
		{
			if (split[j][1] == '<')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

char	quote_check_wrong(char *string, int i, char quote)
{
	if (string[i] == '"' || string[i] == '\'')
	{
		if (quote == '\0')
			quote = string[i];
		else if (quote == string[i])
			quote = '\0';
	}
	return (quote);
}
