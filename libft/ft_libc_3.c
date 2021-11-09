/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:12:13 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/09 23:12:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	while ((i + 1 < size) && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	while (src[src_len])
		src_len++;
	dest_len = ft_strlen(dest);
	while ((dest_len + 1 < size) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = 0;
	if (size < dest_len)
		return (size + src_len);
	else
		return (dest_len + i);
}

int	ft_toupper(int c)
{
	unsigned char	ch;

	ch = c;
	if ('a' <= ch && ch <= 'z')
		ch -= 'a' - 'A';
	return (ch);
}

int	ft_tolower(int c)
{
	unsigned char	ch;

	ch = c;
	if ('A' <= ch && ch <= 'Z')
		ch += 'a' - 'A';
	return (ch);
}

/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char a[] = "1234567890";
	char b[] = "hello";
	char c[] = "1234567890";
	char d[] = "hello";

	//printf("%d %s\n", strlcpy(a, b, 5), a);
	printf("%ld %s\n", ft_strlcpy(c, d, 4), c);
	printf("%d\n", ft_tolower(85));
	return 0;
}
*/
