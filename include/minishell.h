/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:31:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/02/23 14:47:09 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD_ERR "Error : Command not found\n"
# define PROMPT "👨‍💻 Minishell> "
# define ERR_PROMPT "❌ Minishell> "

typedef struct s_minishell
{
	char	**path_env;
	char	*prompt;
	char	*line;
	char	**input_cmd;
	char	**split_pipe;
	char	**history;
	char	*path_cmd;
	int		fd[2];
}				t_minishell;

int		check_write_exit(t_minishell *ms);

int		init_env(t_minishell *ms, char **envp);

int		exec_cmd(t_minishell *ms, char **envp);

void	error(char *str);

int		builtins(t_minishell *ms, char **split, char **envp);

#endif