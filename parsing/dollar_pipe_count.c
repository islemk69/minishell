/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pipe_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 06:27:51 by hamza             #+#    #+#             */
/*   Updated: 2023/05/21 21:20:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	special_count_pipe(char *tab, int *i, int *count)
{
	if (tab[*i + 1] == '?')
	{
		*count += ft_strlen(ft_itoa(g_global.g_status));
		*i += 2;
		return (0);
	}
	return (1);
}

int	is_expandable(char *tab, int i, int dbl_quot, int single_quot)
{
	if ((tab[i] == '$' && single_quot) || (tab[i] == '$' && tab[i + 1] == ' ')
		|| (tab[i] == '$' && tab[i + 1] == 0) || ((tab[i] == '$' && dbl_quot)
			&& (tab[i + 1] == 32 || tab[i + 1] == '"' || tab[i + 1] == '\'')))
		return (0);
	return (1);
}

int	countchar_pipe(t_minishell *ms, char *tab, int dbl_quot, int single_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (check_quote_dollar(tab[i], &single_quot, &dbl_quot))
	{
		if (is_heredoc_name(tab, dbl_quot, single_quot, i))
		{
			while (tab[i++] && ((tab[i] != 32 && !dbl_quot)
					|| (tab[i] != 32 && !single_quot)))
				count += check_quote_dollar(tab[i], &single_quot, &dbl_quot);
			continue ;
		}
		else if (!is_expandable(tab, i, dbl_quot, single_quot))
			i = i;
		else if (tab[i] == '$' && (!special_count_pipe(tab, &i, &count)
				|| check_path_count(ms, tab, &i, &count)))
			continue ;
		count++;
		i++;
	}
	return (count);
}
