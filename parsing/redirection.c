/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:11:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/15 20:38:02 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	**ft_strdup_dtab(char **s1)
// {
// 	char	**ptr;
// 	int		i;

// 	while (s1[i])
// 		i++;
// 	ptr = (char **)ft_gc_malloc(sizeof(const char) * (i + 1));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		ptr[i] = ft_strdup(s1[i]);
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

char	*ft_strdup_token(const char *s1, char c)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (s1[i])
		i++;
	ptr = (void *)ft_gc_malloc(sizeof(const char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	ptr[0] = c;
	i = 0;
	while (s1[i])
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char  **realloc_redir(t_minishell *ms)
{
	int i = 0;
	int size = 0;
	char **realloc;
	while (ms->parsed[i])
	{
		if (ms->parsed[i][0] == '<' && !ms->parsed[i][1] && !ft_strchr(ms->parsed[i + 1], '<'))
		{
			size++;
			i++;
		}
		else
			size++;
		i++;
	}
	realloc = ft_gc_malloc(sizeof(char *) * (size + 1));
	ft_printf("SIZE %d\n", size);
	if (!realloc)
		return (NULL);
	return (realloc);
}


char **redir_first(char **realloc)
{
	char **new_tab;
	int i = 0;
	int j = 0;
	
	new_tab = (char **)ft_gc_malloc(sizeof(char *) * (ft_strlen_dtab(realloc) + 1));
	while (realloc[i])
	{
		if (realloc[i][0] != '<' || (realloc[i][0] == '<' && !realloc[i][1]))
		{
			i++;
			continue ;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	i = 0;
	while (realloc[i])
	{
		if (realloc[i][0] == '<' && realloc[i][1])
		{
			i++;
			continue ;
		}
		ft_printf("je suis passe\n");
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	ft_printf("INDEX %d\n", i);
	new_tab[j] = 0;
	return (new_tab);
}

void	redirection(t_minishell *ms)
{
	int i = 0;
	//int flg = 0;
	//int j = 0;
	char **realloc;
	//char **split_token;
	int k = 0;
	
	realloc = realloc_redir(ms);
	while (ms->parsed[i])
	{
		if (ms->parsed[i][0] == '<' && !ms->parsed[i][1] && !ft_strchr(ms->parsed[i + 1], '<'))
		{
			realloc[k] = ft_strjoin_gnl(ms->parsed[i], ms->parsed[i + 1]);
			i += 2;
			k++;
			continue;
		}
		realloc[k] = ft_strdup(ms->parsed[i]);
		k++;
		i++;
	}
	realloc[k] = 0;
	ms->parsed = realloc;
	//i = 0;
	//while (ms->parsed[i])
	//{
	//	if (ft_strchr(ms->parsed[i], '<') && ms->parsed[i][0] != '<')
	//	{
	//		ft_printf("JE SUIS LA \n");
	//		split_token = ft_split(ms->parsed[i], '<');
	//		j = 0;
	//		ms->parsed[i] = ft_strdup(split_token[j]);
	//		ft_printf("PARSED %s\n", ms->parsed[i]);
	//		j++;
	//		i++;
	//		while (split_token[j])
	//		{
	//			ms->parsed[i] = ft_strdup_token(split_token[j], '<');
	//			ft_printf("PARSED %s\n", ms->parsed[i]);
	//			i++;
	//			j++;
	//		}
	//	}
	//	i++;
	//}
	//ms->parsed[i] = 0;
	ms->parsed = redir_first(realloc);
	ft_printf("_____________________________________\n");
}