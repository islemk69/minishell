/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:52:07 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 05:32:09 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (count != 0 && SIZE_MAX / count < size)
		return (0);
	ptr = (void *)ft_gc_malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_calloc_child(size_t count, size_t size)
{
	char	*ptr;

	if (count != 0 && SIZE_MAX / count < size)
		return (0);
	ptr = (void *)ft_gc_malloc(count * size);
	if (!ptr)
		exit_child(-1);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_calloc_parent(size_t count, size_t size, char *str)
{
	char	*ptr;

	if (count != 0 && SIZE_MAX / count < size)
		return (0);
	ptr = (void *)ft_gc_malloc(count * size);
	if (!ptr)
		exit_parent(str);
	ft_bzero(ptr, count * size);
	return (ptr);
}
