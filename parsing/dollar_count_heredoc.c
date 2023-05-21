/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:22:33 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/21 21:19:48 by ikaismou         ###   ########.fr       */
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

int	countchar_here(t_minishell *ms, char *tab, int dbl_quot, int single_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		check_quote_dollar(tab[i], &single_quot, &dbl_quot);
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
	return (dbl_quot = 0, single_quot = 0, count);
}
