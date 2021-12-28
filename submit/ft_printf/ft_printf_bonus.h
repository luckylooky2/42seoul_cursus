/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:57:24 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/28 14:57:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
char	*print_cs(const char *format, va_list ap, int *ret, int (*opt)[8]);
char	*print_p(const char *format, va_list ap, int *ret, int (*opt)[8]);
char	*print_int(const char *format, va_list ap, int *ret, int (*opt)[8]);
char	*print_uint(const char *format, va_list ap, int *ret, int (*opt)[8]);
char	*print_hex(const char *format, va_list ap, int *ret, int (*opt)[8]);
int		unsigned_digits(unsigned long long n, int base);
char	*make_uint_string(unsigned int n);
char	*make_hex_string(unsigned long long n, int flag);
char	*add_prefix(char **str, int flag);
int		print_string(const char *str, int *ret, int (*opt)[8]);
int		flag_print_space(int *ret, int (*opt)[8], int len, int i);
void	flag_print_string(const char *str, int *ret, int (*opt)[8], int flag);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
