/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:44:23 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/08 20:16:34 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	format_dprintf(const char c, va_list args, int *len)
{
	if (c == 'c')
		ft_putchar_dprintf(va_arg(args, int), len);
	if (c == 's')
		ft_putstr_dprintf(va_arg(args, char *), len);
	if (c == 'p')
	{
		ft_putstr_dprintf("0x", len);
		ft_putnbr_base_dprintf(va_arg(args, long long unsigned int),
			16, "0123456789abcdef", len);
	}
	if (c == 'd' || c == 'i')
		ft_putnbr_dprintf(va_arg(args, int), len);
	if (c == 'u')
		ft_putnbr_base_dprintf(va_arg(args, unsigned int), \
		10, "0123456789", len);
	if (c == 'x')
		ft_putnbr_base_dprintf(va_arg(args, unsigned int), \
		16, "0123456789abcdef", len);
	if (c == 'X')
		ft_putnbr_base_dprintf(va_arg(args, unsigned int), \
		16, "0123456789ABCDEF", len);
	if (c == '%')
		ft_putchar_dprintf('%', len);
}

int	ft_dprintf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i] && len != -1)
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break ;
			format_dprintf(str[i + 1], args, &len);
			i++;
		}
		else
			ft_putchar_dprintf(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
