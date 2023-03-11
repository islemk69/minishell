/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:53:49 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 21:09:43 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cell;

	cell = ft_gc_malloc(sizeof(t_list));
	if (!cell)
		return (0);
	cell->content = content;
	cell->next = 0;
	return (cell);
}
