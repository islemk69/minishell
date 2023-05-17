/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:28:32 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/05/17 05:40:01 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdint.h>
# include "ft_gc.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc_child(size_t count, size_t size);

void	*ft_calloc_parent(size_t count, size_t size, char *str);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

char	*strcpy_token_2(char *src, int *int_s);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memset(void *b, int c, size_t len);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int nb, int fd);

void	ft_putstr_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int		ft_strlen(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_printf(const char *str, ...);

void	ft_putchar_printf(char c, int *len);

void	ft_putstr_printf(char *str, int *len);

void	ft_putnbr_base_printf(long long unsigned int nb, \
		long long unsigned int taille, char *base, int *len);

void	ft_putnbr_printf(int n, int *len);

char	*get_next_line_gnl(int fd);

char	*ft_strjoin_gnl(char *s1, char *s2);

char	*ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);

size_t	ft_strlen_gnl(const char *s);

int		ft_strchr_gnl(const char *s, int c);

char	*ft_newtmp_gnl(char *tmp);

char	*ft_newline_gnl(char *tmp);

char	*ft_tmp_gnl(int fd, char *tmp);

void	ft_free_tab(char **tab);

void	ft_sort_int_tab(int *tab, int size);

char	**ft_split2(char const *s, char c, char e);

char	**ft_split3(char const *s, char c, char e, char f);

int		ft_dprintf(const char *str, ...);

void	format_dprintf(const char c, va_list args, int *len);

void	ft_putnbr_base_dprintf(long long unsigned int nb, \
		long long unsigned int taille, char *base, int *len);

void	ft_putnbr_dprintf(int n, int *len);

void	ft_putchar_dprintf(char c, int *len);

void	ft_putstr_dprintf(char *str, int *len);

char	**ft_split_token(char *input, char sep);

char	*ft_strncpy(char *dest, const char *src, size_t n);

char	**ft_split_space(char *input);

#endif