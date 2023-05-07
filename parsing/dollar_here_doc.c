/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:33:33 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/05/07 22:11:08 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	s_check_dollar_heredoc(char *tab, char *realloc, int *i, int *k)
{
	char	*tmp;

	if (*i != 0)
	{
		if (tab[0] == '<' && tab[1] == '<')
		{
			realloc[*k] = tab[*i];
			*k += 1;
			*i += 1;
			return (0);
		}
	}
	if (tab[*i + 1] == '?')
	{
		tmp = ft_itoa(g_global.g_status);
		while (*tmp)
		{
			realloc[*k] = *tmp;
			*k += 1;
			tmp++;
		}
		*i += 2;
		return (0);
	}
	return (1);
}

static void	check_path_heredoc(t_minishell *ms, char *real, char *tmp, int *k)
{
	char	*dollar;
	int		j;

	j = 0;
	dollar = NULL;
	if (tmp[0])
	{	
		dollar = ft_find_path(&ms->head_env, tmp);
	}
	if (dollar != 0)
	{
		j = 0;
		while (dollar[j])
		{
			real[*k] = dollar[j];
			*k += 1;
			j++;
		}
	}
}

char	*dollar_here_doc(t_minishell *ms, char *tab, int d_quot, int s_quot)
{
	int		i;
	int		k;
	char	*tmp;
	char	*realloc;

	k = 0;
	i = 0;
	realloc = ft_gc_malloc(sizeof(char) * \
		(countchar(ms, tab, d_quot, s_quot) + 1));
	while (tab[i])
	{
		check_quote_dollar(tab[i], &s_quot, &d_quot);
		if (tab[i] == '$' && tab[i + 1] != '"' && tab[i + 1] != '\''
			&& tab[i + 1] != ' ' && tab[i + 1] != '$' && s_quot == 0)
		{
			if (!s_check_dollar_heredoc(tab, realloc, &i, &k))
				continue ;
			i++;
			tmp = ft_tmp_dollar(tab, &i);
			check_path_heredoc(ms, realloc, tmp, &k);
			continue ;
		}
		realloc[k++] = tab[i++];
	}
	return (realloc[k] = 0, realloc);
}
