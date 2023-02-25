/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:29:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/25 16:57:17 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

t_env	*ft_lstlas(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_env	*create_cell(char *str)
{
	t_env	*cell;

	cell = malloc(sizeof(t_env));
	if (!cell)
		return (cell);
	cell->str = str;
	cell->next = NULL;
	return (cell);
}

void	ft_lstad_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlas(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	lstclear(t_env **lst)
{
	t_env	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
}
