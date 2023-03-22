/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:11:23 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/22 14:40:04 by ikaismou         ###   ########.fr       */
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


int is_token_char(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char *ft_strdup_token(const char *s1, char c)
{
	char *ptr;
	int i;
	int j;

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

char **realloc_redir(t_minishell *ms)
{
	int i = 0;
	int size = 0;
	char **realloc;
	while (ms->parsed[i])
	{
		if ((is_token_char(ms->parsed[i][0]) && !ms->parsed[i][1]) 
			|| (is_token_char(ms->parsed[i][0]) && is_token_char(ms->parsed[i][1]) && !ms->parsed[i][2]))
		{
			size++;
			i++;
		}
		else
			size++;
		i++;
	}
	ft_printf("SIZE%d\n", size);
	realloc = ft_gc_malloc(sizeof(char *) * (size + 1));
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
			continue;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	i = 0;
	while (realloc[i])
	{
		if (realloc[i][0] != '>' || (realloc[i][0] == '>' && !realloc[i][1]))
		{
			i++;
			continue;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	i = 0;
	while (realloc[i])
	{
		if ((realloc[i][0] == '<' && realloc[i][1]) || (realloc[i][0] == '>' && realloc[i][1]))
		{
			i++;
			continue;
		}
		new_tab[j] = ft_strdup(realloc[i]);
		j++;
		i++;
	}
	new_tab[j] = 0;
	return (new_tab);
}

int check_double_token(char **str)
{
	int i = 0;
	
	while (str[i])
	{
		if ((is_token_char(str[i][0]) && !str[i + 1] && !str[i][1])
			|| (is_token_char(str[i][ft_strlen(str[i]) - 1]) && !str[i + 1])
			|| (is_token_char(str[i][ft_strlen(str[i]) - 1]) && is_token_char(str[i + 1][0])))
			return (0);
		i++;
	}
	return (1);
}

int is_redir(char *str)
{
	int i;
	int token;

	
	token = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i - 1] != '\"' && str[i + 1] != '\"')
		|| (str[i] == '<' && str[i - 1] != '\"' && str[i + 1] != '\"'))
			token++;
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			i += 2;
		else
			i++;
	}
	return (token);
}

char **realloc_stick(t_minishell *ms)
{
	int i = 0;
	int size = 0;
	int token;
	char **realloc;
	
	token = 0;
	while (ms->parsed[i])
	{
		token = is_redir(ms->parsed[i]);
		if (!is_token_char(ms->parsed[i][0]) && token)
			size += token + 1;
		else if (is_token_char(ms->parsed[i][0]) && token > 1)
			size += token;
		else
			size++;
		token = 0;
		i++;
	}
	realloc = (char**)ft_gc_malloc(sizeof(char *) * (size + 1));
	return (realloc);
}

char *strcpy_token(char* src, int *s_int) 
{
	
	int j;
	int size = 0;
	char	*sdup;
	int save = *s_int;

	j = 0;
	while (src[save] && !is_token_char(src[save])) 
	{
		size++;
		save ++;
    }
	sdup = (char *)ft_gc_malloc(sizeof(char) * (size + 1));
    while (src[*s_int] && !is_token_char(src[*s_int])) 
	{
        sdup[j] = src[*s_int];
        j++;
        *s_int += 1;
    }
	sdup[j] = 0;
	return (sdup);
}

char *strcpy_token_2(char* src, int *s_int, int mod) {
	
	int j;
	int size = 0;
	char *sdup;
	(void)mod;
	int save = *s_int;
	
	while(src[save] && is_token_char(src[save]))
	{
		size++;
        save ++;
	}
    while (src[save] && !is_token_char(src[save])) 
	{
        size++;
		save++;
    }
	sdup = (char *)ft_gc_malloc(sizeof(char) * (size + 1));
	j = 0;
	while(src[*s_int] && is_token_char(src[*s_int]))
	{
		sdup[j] = src[*s_int];
        j++;
        *s_int += 1;
	}
    while (src[*s_int] && !is_token_char(src[*s_int])) {
        sdup[j] = src[*s_int];
        j++;
        *s_int += 1;
    }
	sdup[j] = 0;
    return (sdup);
}


int redirection(t_minishell *ms)
{
	int		i;
	char	**realloc;
	char	**realloc2;
	int		token;
	int		k;
	int		u;
	int		s_int;

	u = 0;
	s_int = 0;
	i = 0;
	k = 0;
	token = 0;
	//realloc = NULL;
	realloc2 = NULL;
	if (!check_double_token(ms->parsed))
		return (ft_dprintf("Error token\n"), 0);
	realloc2 = realloc_stick(ms);
	while (ms->parsed[i])
	{
		s_int = 0;
		token = is_redir(ms->parsed[i]);
		if (!is_token_char(ms->parsed[i][0]) && token)
		{
			u = 1;
			realloc2[k] =  strcpy_token(ms->parsed[i], &s_int);
			k++;
			while (u <= token)
			{
				realloc2[k] = strcpy_token_2(ms->parsed[i], &s_int, 0);
				k++;
				u++;
			}
		}
		else if (is_token_char(ms->parsed[i][0]) && token > 1)
		{
			u = 0;
			while (u < token)
			{
				realloc2[k] = strcpy_token_2(ms->parsed[i], &s_int, 1);
				k++;
				u++;
			}
		}
		else
		{
			realloc2[k] = ft_strdup(ms->parsed[i]);
			k++;
		}
		token = 0;
		i++;
	}
	realloc2[k] = 0;
	k = 0;
	i = 0;
	ms->parsed = realloc2;
	realloc = realloc_redir(ms);//< infile// << infile// > infile// >> infile
	while (ms->parsed[i])
	{
		if ((is_token_char(ms->parsed[i][0]) && !ms->parsed[i][1]) 
			|| (is_token_char(ms->parsed[i][0]) && is_token_char(ms->parsed[i][1]) && !ms->parsed[i][2]))
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
	// i = 0;

	//ms->parsed[i] = 0;
	ms->parsed = redir_first(realloc);
	return (1);
}
