# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 18:23:28 by hel-ouar          #+#    #+#              #
#    Updated: 2023/03/11 16:15:46 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 

SRCS = main.c exit/check_write_exit.c init_env/init_env.c exec/exec.c utils/error.c builtins/builtins.c \
		utils/find_path.c utils/list.c parsing/check_line.c utils/wait.c parsing/token.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror 

NAME = minishell

HEAD = include/minishell.h

RM = rm -f

%.o: %.c Makefile ${HEAD}
		${CC} ${FLAGS} -ILibft -c $< -o $@ 

all: Libft $(NAME)

$(NAME): $(OBJS) Libft
	$(RM) $(OBJB)
	$(CC) $(OBJS) Libft/libft.a -o $(NAME) -lreadline

clean:
	$(RM) $(OBJS) $(OBJB)
	${MAKE} clean -C Libft/

Libft :
	${MAKE} -C Libft
	
fclean: clean
	${MAKE} fclean -C Libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)
	
re: fclean
	make all

.PHONY:	all clean fclean re bonus Libft
