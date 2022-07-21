/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:22:16 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/01 20:15:31 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_node
{
	int				num;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_general_node
{
	void					*data;
	struct s_general_node	*prev;
	struct s_general_node	*next;
}	t_gnode;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_deque
{
	size_t	size;
	t_node	*tail;
}	t_deque;

typedef struct s_general_deque
{
	size_t	size;
	t_gnode	*tail;
}	t_deq;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_lstsize(t_list *lst);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_printf(const char *format, ...);
char	*ft_gnl(int fd);
t_deque	*ft_deque_new(void);
void	ft_deque_delete(t_deque **deque);
t_deque	*ft_deque_copy(t_deque *deque);
int		ft_deque_is_empty(t_deque *deque);
t_node	*ft_deque_get(t_deque *deque, size_t index);
int		ft_deque_push_front(t_deque *deque, int num);
int		ft_deque_push_back(t_deque *deque, int num);
int		ft_deque_pop_front(t_deque *deque);
int		ft_deque_pop_back(t_deque *deque);
void	ft_deque_swap(t_deque *deque, size_t i, size_t j);
t_deq	*ft_deq_new(void);
void	ft_deq_delete(t_deq **deque, void del(void *));
t_deq	*ft_deq_copy(t_deq *deque, void *copy(void *), void del(void *));
int		ft_deq_is_empty(t_deq *deque);
t_gnode	*ft_deq_get(t_deq *deque, size_t index);
int		ft_deq_push_front(t_deq *deque, void *data);
int		ft_deq_push_back(t_deq *deque, void *data);
void	*ft_deq_pop_front(t_deq *deque);
void	*ft_deq_pop_back(t_deq *deque);
void	ft_deq_swap(t_deq *deque, size_t i, size_t j);

#endif
