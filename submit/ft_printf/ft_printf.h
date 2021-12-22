/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:07:33 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/22 13:07:37 by chanhyle         ###   ########.fr       */
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
char	*ft_itoa(int n);

#endif
