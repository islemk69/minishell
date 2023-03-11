/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:29:42 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 19:52:54 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_dprintf(char c, int *len)
{
	if (*len == -1)
		return ;
	if (write(2, &c, 1) != -1)
		*len += 1;
	else
		*len = -1;
}

void	ft_putstr_dprintf(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		ft_putchar_dprintf(*str++, len);
}
