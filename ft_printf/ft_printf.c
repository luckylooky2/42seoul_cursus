/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:48:19 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/19 00:16:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int i = 0;
	char *ch;
	char *str;

	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			ch = va_arg(ap, char *);
			while (*ch != '\0')
			{
				write(1, ch, 1);
				ch++;
			}
			i++;
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	// printf("%c ", (char)va_arg(ap, int));
	// printf("%c ", (char)va_arg(ap, int));
	// printf("%c ", (char)va_arg(ap, int));
	// while (format[i++] != '\0')
	// 	cnt++;
	// i = 0;
	// // str = (char *)malloc(sizeof(char) * (cnt + 1));
	// // while (format[i] != '\0')
	// // {
	// // 	str[i] = format[i];
	// // 	i++;
	// // }
	// // str[i] = '\0';
	// write(1, format, cnt);
	
}

int main()
{
	char	*name = "chanhyle";
	char	*city = "seoul";

	ft_printf("my name is %s. 42 %s student.", name, city);
}
