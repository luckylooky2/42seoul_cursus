/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:43:08 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:46:01 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_format(char flag, char *format_str, char *str, int width)
{
	int	len;
	int	offset;

	if (str == 0)
		len = 1;
	else
		len = ft_strlen(str);
	offset = width - len;
	if (offset)
	{
		if (flag & NEG || !(flag & ZERO))
			ft_memset(format_str + ((flag & NEG) != 0) * len, ' ', offset);
		else
			ft_memset(format_str, '0', offset);
	}
	if (flag & NEG && str)
		ft_memcpy(format_str, str, len);
	else if (str)
		ft_memcpy(format_str + offset, str, len);
	format_str[width] = 0;
	if (str)
		free(str);
	return (format_str);
}

char	*cat_prefix(char *num_str, char *prefix, int precision)
{
	int		len;
	int		prefix_len;
	char	*str;

	if (num_str == 0)
		return (error_with_free(0));
	len = ft_strlen(num_str);
	prefix_len = ft_strlen(prefix);
	if (precision > len)
		str = (char *)malloc(sizeof(char) * (precision + prefix_len + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + prefix_len + 1));
	if (str == 0)
		return (error_with_free(num_str));
	ft_strlcpy(str, prefix, prefix_len + 1);
	if (precision > len)
	{
		ft_memset(str + prefix_len, '0', precision - len);
		ft_strlcpy(str + prefix_len + precision - len, num_str, len + 1);
	}
	else
		ft_strlcpy(str + prefix_len, num_str, len + 1);
	free(num_str);
	return (str);
}

char	*cat_prefix_handler(t_type *type, char *num_str, char flag)
{
	int		is_zero_flag;

	if (num_str == 0)
		return (error_with_free(0));
	if (type->flag & ZERO && (type->precision || type->flag & NO_DIGIT))
		type->flag ^= ZERO;
	else if (type->flag & ZERO)
		type->precision = max(type->width, ft_strlen(num_str));
	is_zero_flag = (type->flag & ZERO) != 0;
	if (flag & CASE1)
		return (cat_prefix(num_str, "0x", type->precision - 2 * is_zero_flag));
	else if (flag & CASE2)
		return (cat_prefix(num_str, "0X", type->precision - 2 * is_zero_flag));
	else if (flag & CASE3)
		return (cat_prefix(num_str, "+", type->precision - is_zero_flag));
	else if (flag & CASE4)
		return (cat_prefix(num_str, " ", type->precision - is_zero_flag));
	else if (flag & CASE5)
		return (cat_prefix(num_str, "-", type->precision - is_zero_flag));
	else
		return (cat_prefix(num_str, "", type->precision));
}

char	*ultoa(unsigned long n, char *base, int base_len)
{
	char			*str;
	size_t			digits;
	unsigned long	n_dup;

	if (n == 0)
		return (ft_strdup("0"));
	digits = 0;
	n_dup = n;
	while (n_dup)
	{
		++digits;
		n_dup /= base_len;
	}
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (str == 0)
		return (0);
	str += digits;
	*str = 0;
	while (n)
	{
		--str;
		*str = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
