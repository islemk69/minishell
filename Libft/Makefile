# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 15:15:32 by hel-ouar          #+#    #+#              #
#    Updated: 2023/05/09 19:41:51 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_tolower.c ft_toupper.c ft_nbr.c ft_put.c \
		ft_printf.c get_next_line_utils.c get_next_line.c ft_free.c\
		ft_sort_int_tab.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
		ft_lstiter.c ft_lstmap.c ft_split_2char.c ft_split_3char.c\
		ft_dnbr.c ft_dput.c ft_dprintf.c ft_gc_ctx_create.c ft_gc_ctx_delete.c\
		ft_gc_ctx_transfer.c ft_gc_ctx_wild_manip.c ft_gc_global.c\
		ft_gc_ptr_utils.c ft_gc_static.c ft_split_token.c ft_strncpy.c\
		ft_split_space.c ft_strcpy2.c
		
OBJS = $(SRCS:.c=.o)
NAME = libft.a
HEAD = libft.h
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

%.o: %.c Makefile ${HEAD}
		${CC} ${FLAGS} -I./ -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean 
	make all

.PHONY: all clean fclean re