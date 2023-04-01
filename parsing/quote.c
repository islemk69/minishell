/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 04:34:06 by ikaismou          #+#    #+#             */
/*   Updated: 2023/04/01 05:10:36 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_quote(char* str) 
{
    int single_quote;
    int double_quote;
    int len;
    int i;

    single_quote = 0;
    double_quote = 0;
    len = ft_strlen(str);
    i = 0;

			while (i < len) 
			{
				if (str[i] == '\'') 
				{
					if (double_quote == 0 || (double_quote == 1 && str[i-1] == '\\'))
					{
						single_quote = (single_quote + 1) % 2;
					}
				} 
				else if (str[i] == '\"') 
				{
					if (single_quote == 0 || (single_quote == 1 && str[i-1] == '\\')) 
					{
						double_quote = (double_quote + 1) % 2;
					}
				}
				i++;
			}

    if (single_quote == 0 && double_quote == 0) 
        return 1;
    return 0;
}