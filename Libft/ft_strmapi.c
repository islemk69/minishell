/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:14:11 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 21:10:46 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i])
		i++;
	tab = (char *)ft_gc_malloc(sizeof(char) * (i + 1));
	while (!tab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return ((char *)tab);
}
