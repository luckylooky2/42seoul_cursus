/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:13:01 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/14 17:12:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	const char		*ptr;

	ch = c;
	ptr = 0;
	while (*s)
	{
		if (*s == ch)
		{
			ptr = s;
			break ;
		}
		s++;
	}
	if (c == 0)
		ptr = s;
	return ((char *)ptr);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	const char		*ptr;

	ch = c;
	ptr = 0;
	while (*s)
	{
		if (*s == ch)
			ptr = s;
		s++;
	}
	if (c == 0)
		ptr = s;
	return ((char *)ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = *s1 - *s2;
		if (res != 0)
			break ;
		if (*s1 == 0 || *s2 == 0)
			break ;
		s1++;
		s2++;
		i++;
	}
	return (res);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		ch;
	const unsigned char	*ptr;
	size_t				i;

	ch = c;
	i = 0;
	ptr = 0;
	while (i < n)
	{
		if (*((const unsigned char *)s + i) == ch)
		{
			ptr = ((const unsigned char *)s + i);
			break ;
		}
		i++;
	}
	return ((void *)ptr);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = ((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i];
		if (res != 0)
			break ;
		i++;
	}
	return (res);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char a[] = "hello";
	//int b;
	char c[] = "cello";

	//b = 'e';
	//printf("%s", ft_strrchr(a, b));
	printf("%d\n", ft_strncmp(a, c, 3));
	printf("%d\n", strncmp(a, c, 3));
}
*/
