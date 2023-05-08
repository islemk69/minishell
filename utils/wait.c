/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:14:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/03 19:13:37 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_pid(t_minishell *ms, int i)
{
	while (i >= 0)
	{
		waitpid(-1, &ms->status, 0);
		i--;
	}
}

static int	overflow(int sign, t_minishell *ms)
{
	(void)sign;
	ms->overflow = true;
	return (-1);
}

static int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	else
		return (0);
}

int	ft_atoi2(const char *str, t_minishell *ms)
{
	int			i;
	long long	nbr;
	long long	signe;

	i = 0;
	nbr = 0;
	signe = 1;
	if (!ft_strncmp(str, "-9223372036854775808", ft_strlen(str)))
		return (0);
	while (ft_isspace(str[i]) && str[i] != 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		if (!ft_isdigit(str[i + 1]))
			return (0);
		i++;
	}
	while (ft_isdigit(str[i]) && str[i] != 0)
	{
		if (nbr != (nbr * 10 + (str[i] - '0')) / 10)
			return ((int)overflow(signe, ms));
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * signe);
}
