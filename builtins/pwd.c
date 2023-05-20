/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/08 22:19:17 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in_pwd(t_minishell *ms, char **split)
{
	char	*str;

	if (split[0] && !ft_strncmp(split[0], "pwd\0", 4))
	{
		str = getcwd(0, 0);
		if (!str)
		{
			g_global.g_status = 1;
			ft_close(ms, 0, 0);
			perror("getcwd()");
		}
		printf("%s\n", str);
		free(str);
		g_global.g_status = 0;
		return (1);
	}
	return (0);
}
