/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:30:17 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 21:12:09 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			j;
	size_t			i;

	i = start;
	j = 0;
	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		ptr = ft_gc_malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	else
		ptr = ft_gc_malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i] && j < len)
	{
		ptr[j] = s[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
