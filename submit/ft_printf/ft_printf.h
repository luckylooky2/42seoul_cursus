/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:02:34 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/12 11:02:38 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
char	*type_char_or_str(const char *format, va_list ap, int *ret);
char	*type_address_or_percent(const char *format, va_list ap, int *ret);
char	*type_signed_int(const char *format, va_list ap, int *ret);
char	*type_unsigned_int(const char *format, va_list ap, int *ret);
char	*type_hex(const char *format, va_list ap, int *ret);
int		unsigned_digits(unsigned long long n, int base);
char	*make_uint_string(unsigned int n);
char	*make_hex_string(unsigned long long n, int flag);
char	*add_prefix(char **str, int flag);
void	print_string(const char *str, int *ret);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
