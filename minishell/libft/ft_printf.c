/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:11:39 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:38:20 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_string(const char **format);
static int	ft_flush(t_buf *buf);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	char	*to_fill;

	va_start(ap, format);
	buf.cnt = 0;
	buf.to_return = 0;
	while (*format)
	{
		to_fill = get_string(&format);
		fill_buffer(&buf, to_fill, format - to_fill, !ALLOC);
		if (*format)
		{
			to_fill = ft_printf_get_format(&buf, &format, &ap);
			if (to_fill == (char *) -1)
				return (-1);
			else if (to_fill != 0
				&& fill_buffer(&buf, to_fill, ft_strlen(to_fill), ALLOC) == -1)
				return (-1);
		}
	}
	ft_flush(&buf);
	va_end(ap);
	return (buf.to_return);
}

static char	*get_string(const char **format)
{
	char	*to_return;
	char	*next;

	to_return = (char *)*format;
	next = ft_strchr(*format, '%');
	if (next == 0)
		*format += ft_strlen(*format);
	else
		*format = next;
	return (to_return);
}

int	fill_buffer(t_buf *buf, char *str, int length, char flag)
{
	int		to_fill;
	char	*to_free;

	if (str == (const char *) -1)
		return (-1);
	to_free = str;
	while (length > 0)
	{
		to_fill = -max(-length, -(BUFSIZE - buf->cnt));
		ft_memcpy(buf->buf + buf->cnt, str, to_fill);
		str += to_fill;
		length -= to_fill;
		buf->cnt += to_fill;
		if (buf->cnt == BUFSIZE && ft_flush(buf) == -1)
		{
			if (flag & ALLOC)
				free(to_free);
			return (-1);
		}
	}
	if (flag & ALLOC)
		free(to_free);
	return (0);
}

static int	ft_flush(t_buf *buf)
{
	ssize_t	temp;

	temp = write(1, buf->buf, buf->cnt);
	if (temp == -1)
		return (-1);
	buf->to_return += temp;
	buf->cnt = 0;
	return (0);
}

char	*error_with_free(char *str)
{
	if (str && str != (char *) -1)
		free(str);
	return ((char *) -1);
}
