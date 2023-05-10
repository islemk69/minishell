/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:40:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/10 19:41:10 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_token_char(char c);

char	*strcpy_token_2(char *src, int *s_int, int mod)
{
	int		j;
	int		size;
	char	*sdup;
	int		save;
	int		d_quot;
	int		s_quot;

	(void)mod;
	d_quot = 0;
	s_quot = 0;
	save = *s_int;
	size = 0;
	while (is_token_char(src[save]))
	{
		size++;
		save++;
	}
	while (src[save])
	{
		if (src[save] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (src[save] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (is_token_char(src[save]) && (!d_quot && !s_quot))
			break ;
		size++;
		save++;
	}
	sdup = (char *)ft_gc_malloc(sizeof(char) * (size + 1));
	j = 0;
	while (is_token_char(src[*s_int]))
	{
		sdup[j] = src[*s_int];
		j++;
		*s_int += 1;
	}
	s_quot = 0;
	d_quot = 0;
	while (src[*s_int])
	{
		if (src[*s_int] == '"' && s_quot == 0)
		{
			if (d_quot == 0)
				d_quot = 1;
			else
				d_quot = 0;
		}
		if (src[*s_int] == '\'' && d_quot == 0)
		{
			if (s_quot == 0)
				s_quot = 1;
			else
				s_quot = 0;
		}
		if (is_token_char(src[*s_int]) && (!d_quot && !s_quot))
			break ;
		sdup[j] = src[*s_int];
		j++;
		*s_int += 1;
	}
	sdup[j] = 0;
	return (sdup);
}