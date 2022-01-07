/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:57:24 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/06 17:36:29 by marvin           ###   ########.fr       */
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
char	*print_cs(const char *format, va_list ap, int *ret, t_option *opt);
char	*print_p(const char *format, va_list ap, int *ret, t_option *opt);
char	*print_int(const char *format, va_list ap, int *ret, t_option *opt);
char	*print_uint(const char *format, va_list ap, int *ret, t_option *opt);
char	*print_hex(const char *format, va_list ap, int *ret, t_option *opt);
int		unsigned_digits(unsigned long long n, int base);
char	*make_uint_string(unsigned int n);
char	*make_hex_string(unsigned long long n, int flag);
char	*add_prefix(char **str, int flag);
int		ft_print_string(char *str, int *ret, t_option *opt);
void	flag_switch_fuction(int *ret, t_option *opt, int len, int i);
int		flag_print_plus(int *ret, t_option *opt, int i);
int		flag_print_space_or_zero(int *ret, t_option *opt, int len, int i);
void	flag_print_string(char *str, int *ret, t_option *opt, int flag);
void	print_sharp(int *ret, t_option *opt);
void	write_and_plus(char *sg_char, int *ret, int flag);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
