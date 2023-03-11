/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:02:22 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/03/11 21:09:25 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mallocsize(long n)
{
	int	cpt;

	cpt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		cpt++;
	}
	while (n > 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

static char	*egalzero(char *tab)
{
	tab[0] = 48;
	return (tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;
	long	nb;

	nb = n;
	i = mallocsize(nb);
	tab = (char *)ft_gc_malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	tab[i--] = '\0';
	if (nb == 0)
		return (egalzero(tab));
	if (nb < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		tab[i--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (tab);
}
