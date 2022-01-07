/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:45:17 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/07 18:45:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_option
{
	int		f_minus;
	int		f_space;
	int		f_plus;
	int		f_sharp;
	int		f_zero;
	int		width;
	int		dot;
	int		prcs;
	char	type;
	int		neg;
}					t_option;

int		ft_printf(const char *format, ...);
char	*type_cs(const char *format, va_list ap, int *ret, t_option *opt);
char	*type_p(const char *format, va_list ap, int *ret, t_option *opt);
char	*type_int(const char *format, va_list ap, int *ret, t_option *opt);
char	*type_uint(const char *format, va_list ap, int *ret, t_option *opt);
char	*type_hex(const char *format, va_list ap, int *ret, t_option *opt);
int		unsigned_digits(unsigned long long n, int base);
char	*make_uint_string(unsigned int n);
char	*make_hex_string(unsigned long long n, int flag);
char	*add_prefix(char **str, int flag);
int		print_sign(int *ret, t_option *opt, int i);
int		print_padding(int *ret, t_option *opt, int len, int i);
void	print_base(int *ret, t_option *opt);
void	print_stdin(char *sg_char, int *ret, int flag);
int		print_string(char *str, int *ret, t_option *opt);
void	print_string_with_option(char *str, int *ret, t_option *opt, int flag);
void	switch_fuction(int *ret, t_option *opt, int len, int i);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
