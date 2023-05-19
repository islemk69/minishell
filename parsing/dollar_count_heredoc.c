/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:22:33 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/18 18:51:56 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	special_count_heredoc(char *tab, int *i, int *count)
{
	if (tab[*i + 1] == '?')
	{
		*count += ft_strlen(ft_itoa(g_global.g_status));
		*i += 2;
		return (0);
	}
	return (1);
}

int	countchar_here(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		check_quote_dollar(tab[i], &s_quot, &d_quot);
		if (tab[i] == '$' && (ft_isalnum(tab[i + 1]) || tab[i + 1] == '?'))
		{
			if (!special_count_heredoc(tab, &i, &count))
				continue ;
			check_path_count(ms, tab, &i, &count);
			continue ;
		}
		count++;
		i++;
	}
	return (d_quot = 0, s_quot = 0, count);
}
