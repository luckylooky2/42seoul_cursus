/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:56:36 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/26 17:56:43 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
char	*print_char_or_str(const char *format, va_list ap, int *ret);
char	*print_address_or_percent(const char *format, va_list ap, int *ret);
char	*print_signed_int(const char *format, va_list ap, int *ret);
char	*print_unsigned_int(const char *format, va_list ap, int *ret);
char	*print_hex(const char *format, va_list ap, int *ret);
int		unsigned_digits(unsigned long long unsigned_n, int flag);
char	*make_uint_string(unsigned int unsigned_n);
char	*make_hex_string(unsigned long long n, int len, int flag);
char	*add_prefix(char **str, int flag);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
