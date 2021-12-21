/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:53:21 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/21 11:04:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_number_of_digits_2(unsigned int unsigned_n);
char	*ft_uitoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
int	    ft_number_of_digits(int n);
char	*ft_itoa(int n);
int	    ft_number_of_digits_3(unsigned long long n);
char	*ft_litoa(unsigned long long n, int len, int *ret);

#endif