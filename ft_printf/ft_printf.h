/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:53:21 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/21 16:37:36 by marvin           ###   ########.fr       */
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
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_unsigned_number_of_digits(unsigned long long unsigned_n, int flag);
char	*malloc_u(int n);
char	*malloc_p(unsigned long long n, int len);
int		ft_number_of_digits(int n);
char	*print_hex(const char *format, va_list ap, int *ret);

#endif