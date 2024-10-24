/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:23:45 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/24 18:41:49 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

// List structure definition
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ------------------------------------------------------------------------- */
/*                           Character Checking Functions                    */
/* ------------------------------------------------------------------------- */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

/* ------------------------------------------------------------------------- */
/*                           String Manipulation                             */
/* ------------------------------------------------------------------------- */
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ------------------------------------------------------------------------- */
/*                           Memory Manipulation                             */
/* ------------------------------------------------------------------------- */
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_realloc(void *ptr, int old_size, int new_size);

/* ------------------------------------------------------------------------- */
/*                             Number Conversion                             */
/* ------------------------------------------------------------------------- */
int			ft_atoi(const char *nptr);
void		ft_putnbr_base(int nbr, char *base);
char		*ft_itoa(int n);

/* ------------------------------------------------------------------------- */
/*                           Output Functions                                */
/* ------------------------------------------------------------------------- */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ------------------------------------------------------------------------- */
/*                           Linked List Manipulation                        */
/* ------------------------------------------------------------------------- */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ------------------------------------------------------------------------- */
/*                           Matrix Manipulation                             */
/* ------------------------------------------------------------------------- */
void		ft_free_matrix(char **matrix);
char		**ft_matrixdup(char **matrix, int height);
size_t		ft_str2dlen(char **array);
char		**ft_append_to_array(char **matrix, char *str, int size);

#endif
