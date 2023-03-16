/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:31:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/03/16 14:20:19 by hamzaelouar      ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# define CMD_ERR "Error : Command not found\n"
# define PROMPT "👨‍💻 Minishell> "
# define ERR_PROMPT "❌ Minishell> "


typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_env	*head_env;
	char	**joined;
	char	**parsed;
	char	**path_env;
	char	**new_env;
	char	*prompt;
	char	*line;
	char	**input_cmd;
	char	**split_pipe;
	char	**history;
	char	*path_cmd;
	char	*tmp;
	char	*new_line;
	int		fd[2];
	int		flg;
	int		infile;
	int		outfile;
}				t_minishell;

int		check_write_exit(t_minishell *ms);

int		init_env(t_minishell *ms, char **envp);

int		exec_cmd(t_minishell *ms, t_env **env);

void	error(char *str);

int		builtins(t_minishell *ms, char **split, t_env **env);

char	*ft_find_path(t_env **env, char *srch);

t_env	*create_cell(char *var, char *content);

void	ft_lstad_back(t_env **lst, t_env *new);

void	lstclear(t_env **lst);

void	check_new_line(t_minishell *ms);

size_t	ft_strlen_dtab(char **s);

int		lstsize(t_env *lst);

int		input_last_cmd(char **split, t_minishell *ms, t_env **env);

int		inputx_index(char **split, t_minishell *ms);

int		is_empty(char *str);

char	**refresh_env(t_env **env);

int		is_built_in(char *str);

void	wait_pid(int i);

int		is_token(char *str);

void	redirection(t_minishell *ms);

#endif