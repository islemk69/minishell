/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:22:21 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/14 17:47:07 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return ("true");
	while (s[i] != (char)c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	return ((char *)s + i);
}
