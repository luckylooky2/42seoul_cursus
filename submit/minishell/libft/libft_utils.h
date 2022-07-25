/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:56:38 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/23 16:17:51 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# define BUFSIZE 4096
# define ALT 1
# define ZERO 2
# define NEG 4
# define SPC 8
# define PLUS 16
# define NO_DIGIT 32
# define CASE1 1
# define CASE2 2
# define CASE3 4
# define CASE4 8
# define CASE5 16
# define ALLOC 1
# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buf
{
	char	buf[BUFSIZE];
	int		cnt;
	int		to_return;
}	t_buf;

typedef struct s_type
{
	char	flag;
	int		width;
	int		precision;
}	t_type;

typedef struct s_contents
{
	char		*line;
	char		buf[4096];
	int			line_cnt;
	int			buf_cnt;
	int			nl_cnt;
}	t_contents;

int		max(int a, int b);
int		fill_buffer(t_buf *buf, char *str, int length, char flag);
char	*ft_printf_get_format(t_buf *buf, const char **current, va_list *ap);
char	*process_char(t_buf *buf, t_type type, char c);
char	*process_str(t_type type, char *str);
char	*process_ptr(t_type type, void *p);
char	*process_int(t_type type, int n);
char	*process_uint(t_type type, unsigned int n, char *base, int base_len);
char	*set_format(char flag, char *format_str, char *str, int width);
char	*cat_prefix(char *num_str, char *prefix, int precision);
char	*cat_prefix_handler(t_type *type, char *num_str, char flag);
char	*ultoa(unsigned long n, char *base, int base_len);
char	*error_with_free(char *str);
char	*with_wrapper(char *line, t_contents *content);
char	*flush_content(t_contents *content);
void	_memcpy(char *dst, char *src, size_t size);
void	_memcpy_with_null(char *dst, char *src, size_t size);
int		_memcpy_with_detect(char *dst, char *src, size_t size);
int		fill_content(t_contents *content, int fd, int bytes_to_read);
int		with_free(int val, char *buf);

#endif
