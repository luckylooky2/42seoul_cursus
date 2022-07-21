/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:37:21 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:38:32 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*process_char(t_buf *buf, t_type type, char c)
{
	int		width;
	char	*format_str;

	width = max(type.width, 1);
	format_str = (char *)malloc(sizeof(char) * (width + 1));
	if (format_str == 0)
		return (error_with_free(0));
	if (type.flag & NEG)
		format_str[0] = c;
	else
		format_str[width - 1] = c;
	format_str = set_format(type.flag, format_str, 0, width);
	if (fill_buffer(buf, format_str, width, ALLOC) == -1)
		return (error_with_free(0));
	return (0);
}

char	*process_str(t_type type, char *str)
{
	int		len;
	int		width;
	char	*str_str;
	char	*format_str;

	if (str == 0)
		len = 6;
	else
		len = ft_strlen(str);
	if (type.precision || type.flag & NO_DIGIT)
		len = -max(-len, -type.precision);
	width = max(type.width, len);
	str_str = (char *)malloc(sizeof(char) * (width + 1));
	if (str_str == 0)
		return (error_with_free(0));
	if (str == 0)
		ft_strlcpy(str_str, "(null)", len + 1);
	else
		ft_strlcpy(str_str, str, len + 1);
	format_str = (char *)malloc(sizeof(char) * (width + 1));
	if (format_str == 0)
		return (error_with_free(0));
	return (set_format(type.flag, format_str, str_str, width));
}

char	*process_ptr(t_type type, void *p)
{
	int		width;
	char	*format_str;
	char	*ptr_str;
	char	*str_with_prefix;

	ptr_str = ultoa((unsigned long)p, "0123456789abcdef", 16);
	if (type.flag & ZERO)
		str_with_prefix = cat_prefix(ptr_str, "0x", max(type.width - 2, 0));
	else
		str_with_prefix = cat_prefix(ptr_str, "0x", 0);
	if (str_with_prefix == (char *) -1)
		return (error_with_free(0));
	width = max(type.width, ft_strlen(str_with_prefix));
	format_str = (char *)malloc(sizeof(char) * (width + 1));
	if (format_str == 0)
		return (error_with_free(str_with_prefix));
	return (set_format(type.flag, format_str, str_with_prefix, width));
}

char	*process_uint(t_type type, unsigned int n, char *base, int base_len)
{
	int		width;
	char	*format_str;
	char	*num_str;
	char	*str_with_prefix;

	if (n == 0 && type.flag & NO_DIGIT)
		num_str = ft_strdup("");
	else
		num_str = ultoa(n, base, base_len);
	if (n * (type.flag & ALT) && base_len == 16 && base[15] == 'f')
		str_with_prefix = cat_prefix_handler(&type, num_str, CASE1);
	else if (n * (type.flag & ALT) && base_len == 16 && base[15] == 'F')
		str_with_prefix = cat_prefix_handler(&type, num_str, CASE2);
	else
		str_with_prefix = cat_prefix_handler(&type, num_str, 0);
	if (str_with_prefix == (char *) -1)
		return (error_with_free(0));
	width = max(type.width, ft_strlen(str_with_prefix));
	format_str = (char *)malloc(sizeof(char) * (width + 1));
	if (format_str == 0)
		return (error_with_free(str_with_prefix));
	return (set_format(type.flag, format_str, str_with_prefix, width));
}

char	*process_int(t_type type, int n)
{
	int			width;
	char		*format_str;
	char		*num_str;
	char		*str_with_prefix;
	static char	*dec = "0123456789";

	if (n == 0 && (type.flag & NO_DIGIT) != 0)
		num_str = ft_strdup("");
	else
		num_str = ultoa((unsigned int)(((n < 0) * -2 + 1) * n), dec, 10);
	if (type.flag & PLUS && n >= 0)
		str_with_prefix = cat_prefix_handler(&type, num_str, CASE3);
	else if (type.flag & SPC && n >= 0)
		str_with_prefix = cat_prefix_handler(&type, num_str, CASE4);
	else if (n < 0)
		str_with_prefix = cat_prefix_handler(&type, num_str, CASE5);
	else
		str_with_prefix = cat_prefix_handler(&type, num_str, 0);
	if (str_with_prefix == (char *) -1)
		return (error_with_free(0));
	width = max(type.width, ft_strlen(str_with_prefix));
	format_str = (char *)malloc(sizeof(char) * (width + 1));
	if (format_str == 0)
		return (error_with_free(str_with_prefix));
	return (set_format(type.flag, format_str, str_with_prefix, width));
}
