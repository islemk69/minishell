/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pipe_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 06:27:51 by hamza             #+#    #+#             */
/*   Updated: 2023/05/19 01:03:49 by hel-ouar         ###   ########.fr       */
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

int	is_expandable(char *tab, int i, int d_quot, int s_quot)
{
	if ((tab[i] == '$' && s_quot) || (tab[i] == '$' && tab[i + 1] == ' ')
		|| (tab[i] == '$' && tab[i + 1] == 0) || ((tab[i] == '$' && d_quot)
			&& (tab[i + 1] == 32 || tab[i + 1] == '"' || tab[i + 1] == '\'')))
		return (0);
	return (1);
}

int	countchar_pipe(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (check_quote_dollar(tab[i], &s_quot, &d_quot))
	{
		if (is_heredoc_name(tab, d_quot, s_quot, i))
		{
			while (tab[i++] && ((tab[i] != 32 && !d_quot)
					|| (tab[i] != 32 && !s_quot)))
				count += check_quote_dollar(tab[i], &s_quot, &d_quot);
			continue ;
		}
		else if (!is_expandable(tab, i, d_quot, s_quot))
			i = i;
		else if (tab[i] == '$' && (!special_count_pipe(tab, &i, &count)
				|| check_path_count(ms, tab, &i, &count)))
			continue ;
		count++;
		i++;
	}
	return (count);
}

// int	countchar_pipe(t_minishell *ms, char *tab, int d_quot, int s_quot)
// {
// 	int		i;
// 	int		count;

// 	count = 0;
// 	i = 0;
// 	while (tab[i])
// 	{
// 		check_quote_dollar(tab[i], &s_quot, &d_quot);
// 		if (is_heredoc_name(tab, d_quot, s_quot, i))
// 		{
// 			while (tab[i] && ((tab[i] != 32 && !d_quot)
// 					|| (tab[i] != 32 && !s_quot)))
// 			{
// 				count++;
// 				i++;
// 				check_quote_dollar(tab[i], &s_quot, &d_quot);
// 			}
// 			continue ;
// 		}
// 		if (!is_expandable(tab, i, d_quot, s_quot))
// 		{
// 			count++;
// 			i++;
// 			continue ;
// 		}
// 		else if (tab[i] == '$')
// 		{
// 			if (!special_count_pipe(tab, &i, &count))
// 				continue ;
// 			i++;
// 			check_path_count(ms, tab, &i, &count);
// 			continue ;
// 		}
// 		i++;
// 		count++;
// 	}
// 	return (count);
// }
