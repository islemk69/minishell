/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_count_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:22:33 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 06:31:28 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_tab_count(char *tab, int *i, int *count)
{
	if (tab[*i + 1] == '"')
	{
		*count += 1;
		*i += 1;
		return (1);
	}
	if (!special_dollar_count(tab, &*i, &*count))
		return (1);
	return (0);
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
		if (tab[i] == '$' && tab[i + 1] != '$' && tab[i + 1] != 32 \
			&& tab[i + 1] != 0 && s_quot == 0)
		{
			if (check_tab_count(tab, &i, &count))
				continue ;
			i++;
			check_path_count(ms, tab, &i, &count);
			continue ;
		}
		count++;
		i++;
	}
	d_quot = 0;
	s_quot = 0;
	return (count);
}

char	*ft_tmp_dollar_heredoc(char *tab, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	*i += 1;
	tmp = ft_calloc_child(sizeof(char), (size_tmp(tab, *i) + 1));
	while (tab[*i] && tab[*i] != '"' && tab[*i] != '\''
		&& tab[*i] != ' ' && tab[*i] != '$'
		&& (ft_isalnum(tab[*i]) || tab[*i] == '_'))
	{
		tmp[j] = tab[*i];
		*i += 1;
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}
