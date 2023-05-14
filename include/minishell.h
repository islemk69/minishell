/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:31:12 by ikaismou          #+#    #+#             */
/*   Updated: 2023/05/10 18:48:17 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../Libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define WHITE "\001\033[1;37m\002"
# define RED "\001\033[1;31m\002"
# define CMD_ERR "Error : Command not found\n"
# define PROMPT "42@guest> "
# define ERR_PROMPT "❌ Minishell> "

# define SQUOTE 39
# define DQUOTE 34
# define DOLLAR 36
# define TILDE 126
# define SYNT_ERR "bash: syntax error near unexpected token"

typedef struct s_data	t_data;

typedef struct s_global
{
	int			g_status;
}				t_global;

extern t_global			g_global;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_env	*head_env;
	char	**new_parsed;
	char	**parsed;
	char	**path_env;
	char	**new_env;
	char	*prompt;
	char	*line;
	char	**input_cmd;
	char	*infile_str;
	char	*infile_stra;
	char	*outfile_str;
	char	*path_cmd;
	bool	overflow;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*line_here;
	int		outfile_exist;
	int		status;
	char	**realloc;
	char	**tmp_dollar;
	char	**change_dollar;
	int		flg;
}				t_minishell;

int		init_env(t_minishell *ms, char **envp);

int		exec_cmd(t_minishell *ms, t_env **env);

int		is_redir(char *str, bool in_quotes, char current_quote);

void	error(char *str);

char	*ft_strdup_token(const char *s1, char c);

char	*strcpy_token(char *src, int *s_int);

int		check_double_token(char **str);

char	**realloc_stick(char **space);

char	**realloc_redir(char **space);

int		pipe_builtins(t_minishell *ms, char **split, t_env **env, int pipe);

int		ft_atoi2(const char *str, t_minishell *ms);

int		built_in_export(t_env **env, char **split);

int		built_in_unset(t_env **env, char **cmd);

void	init_i_k(int *i, int *k);

int		check_key(char *str);

int		input_env(t_env **env, char **split);

int		input_cd(char **split, t_env **env);

int		built_in_pwd(char **split);

char	*ft_find_path(t_env **env, char *srch);

t_env	*create_cell(char *var, char *content);

void	ft_lstad_back(t_env **lst, t_env *new);

void	lstclear(t_env **lst);

int		parsing(char *line, t_minishell *ms);

int		countchar_here(t_minishell *ms, char *tab, int d_quot, int s_quot);

size_t	ft_strlen_dtab(char **s);

char	**redir_first(char **realloc);

int		lstsize(t_env *lst);

int		input_last_cmd(char **split, t_minishell *ms, t_env **env);

int		inputx_index(char **split, t_minishell *ms);

int		is_empty(char *str);

char	**refresh_env(t_env **env);

int		is_built_in(char *str);

void	wait_pid(t_minishell *ms, int i, int *id);

char	**redirection(char **space);

char	*get_key(char *line);

char	*get_value(char *line);

void	signal_handler_parent(int signum);

void	signal_handler_heredoc(int signum);

char	**split_string(char *str);

int		check_command(t_minishell *ms, char *input_cmd);

int		is_token_char(char c);

int		count_token(char *str, char c);

void	access_file(t_minishell *ms, char **tab);

void	check_redir(t_minishell *ms);

void	remove_heredoc(char **tab);

int		here_doc(t_minishell *ms, char *tab, char *tmp);

int		check_key(char *str);

void	access_file2(t_minishell *ms);

int		exec_multi_pipe(t_minishell *ms, t_env **env, int nb_pipe);

int		exec_one_pipe(t_minishell *ms, t_env **env);

int		check_write_exit(t_minishell *ms, char **split, int pipe);

char	*quote(char *line);

void	rm_quote_last(char **cmds);

int		get_path(t_minishell *ms);

int		check_line(char *line);

void	lstclear(t_env **lst);

void	check_dollar(t_minishell *ms);

char	**dollar_exist(t_minishell *ms, char *tab, int d_quot, int s_quot);

void	set_interactive_signals(void);

void	unplug_signals(void);

void	set_exec_signals(void);

void	set_heredoc_signals(void);

int		built_in_echo(char **split);

int		child_builtins(t_minishell *ms, char **split, t_env **env);

int		parent_builtins(t_minishell *ms, char **split, t_env **env, int pipe);

char	**open_files(t_minishell *ms, char **tab);

char	**check_redir_simple(t_minishell *ms);

void	print_error(char *cmd, char *type);

char	*dollar_here_doc(t_minishell *ms, char *tab, int d_quot, int s_quot);

int		countchar(t_minishell *ms, char *tab, int d_quot, int s_quot);

int		size_tmp(char *tab, int i);

void	get_prompt(t_minishell *ms, char *envp);

int		fill_list(t_env **env, char *key, char *value);

int		iter_shlvl(char *str, t_env **env);

void	print_error_export(char *split);

int		custom_msg_check_line(char *line, int pos, char c);

void	check_quote_dollar(char c, int *s_quot, int *d_quot);

char	*ft_tmp_dollar(char *tab, int *i);

char	**change_parsed_dollar(t_minishell *ms, char *tab, \
	int d_quot, int s_quot);

int		error_exit(char *cmd, char *type, int i);

char	**ft_realloc_from_i(char **tab, int size, int i);

void	check_path_count(t_minishell *ms, char *tab, int *i, int *count);

int		special_dollar_count(char *tab, int *i, int *count);

#endif
