# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:42:32 by ikaismou          #+#    #+#              #
#    Updated: 2023/05/10 15:17:45 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g

SRCS = main.c init_env/init_env.c init_env/init_env_util.c exec/exec.c utils/builtins_util.c utils/parsing_util.c  utils/error.c builtins/builtins.c \
		utils/find_path.c utils/list.c parsing/parsing.c utils/wait.c parsing/redirection.c \
		signal/signal.c signal/signals_handlers.c builtins/cd.c builtins/env.c builtins/pwd.c builtins/export.c builtins/unset.c \
		builtins/exit.c builtins/echo.c exec/here_doc.c exec/pipe.c exec/simple_exec.c exec/redir_exec.c\
		parsing/check_line.c parsing/dollar.c exec/open_pipe.c exec/open_simple.c parsing/dollar_here_doc.c \
		parsing/dollar_count.c parsing/dollar_change.c exec/exec_utils.c exec/exec_utils_2.c parsing/redir_first.c parsing/parsing_utils.c
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = minishell

HEAD = include/minishell.h

RM = rm -f

%.o: %.c Makefile ${HEAD}
		${CC} ${FLAGS} -ILibft -c $< -o $@

all: Libft $(NAME)

$(NAME): $(OBJS) Libft
	$(CC) $(OBJS) Libft/libft.a -o $(NAME) -lreadline

clean:
	${MAKE} clean -C Libft/

Libft :
	${MAKE} -C Libft
	
fclean: clean
	${MAKE} fclean -C Libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)

leaks:    all
	echo "{" > valgrind_ignore_leaks.txt
	echo "leak readline" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:readline" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	echo "{" >> valgrind_ignore_leaks.txt
	echo "    leak add_history" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:add_history" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
		--show-leak-kinds=all --track-fds=yes \
		--show-mismatched-frees=yes --read-var-info=yes \
		--log-file=valgrind.txt ./${NAME}
	
re: fclean
	make all

.PHONY:	all clean fclean re bonus Libft