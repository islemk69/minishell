/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:40:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/17 05:39:03 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_token_char(char c);
void	check_quote_dollar(char c, int *s_quot, int *d_quot);

char	*do_sdup(char *sdup, char *src, int *int_s, int *j)
{
	int	d_quot;
	int	s_quot;

	s_quot = 0;
	d_quot = 0;
	while (src[*int_s])
	{
		check_quote_dollar(src[*int_s], &s_quot, &d_quot);
		if (is_token_char(src[*int_s]) && (!d_quot && !s_quot))
			break ;
		sdup[*j] = src[*int_s];
		*j += 1;
		*int_s += 1;
	}
	sdup[*j] = 0;
	return (sdup);
}

int	count_size_token(char *src, int save)
{
	int	d_quot;
	int	s_quot;
	int	size;

	d_quot = 0;
	s_quot = 0;
	size = 0;
	while (is_token_char(src[save]))
	{
		size++;
		save++;
	}
	while (src[save])
	{
		check_quote_dollar(src[save], &s_quot, &d_quot);
		if (is_token_char(src[save]) && (!d_quot && !s_quot))
			break ;
		size++;
		save++;
	}
	return (size);
}

char	*strcpy_token_2(char *src, int *int_s)
{
	int		size;
	char	*sdup;
	int		j;

	size = count_size_token(src, *int_s);
	sdup = ft_calloc_parent(sizeof(char), (size + 1), "parsing");
	j = 0;
	while (is_token_char(src[*int_s]))
	{
		sdup[j] = src[*int_s];
		j++;
		*int_s += 1;
	}
	return (do_sdup(sdup, src, &*int_s, &j));
}
