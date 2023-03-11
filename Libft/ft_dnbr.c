/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dnbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:20:42 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 19:54:29 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_dprintf(long long unsigned int nb, \
		long long unsigned int taille, char *base, int *len)
{
	if (nb > (taille - 1))
		ft_putnbr_base_dprintf((nb / taille), taille, base, len);
	ft_putchar_dprintf(base[nb % taille], len);
}

void	ft_putnbr_dprintf(int n, int *len)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_dprintf('-', len);
		nb = -n;
	}
	else
		nb = n;
	return (ft_putnbr_base_dprintf(nb, 10, "0123456789", len));
}
