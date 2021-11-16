/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:44:34 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/11 22:44:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	ch;

	ch = c;
	if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	unsigned char	ch;

	ch = c;
	if ('0' <= ch && ch <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	unsigned char	ch;

	ch = c;
	if (ft_isalpha(ch) || ft_isdigit(ch))
		return (1);
	else
		return (0);
}

int	ft_isascii(int c)
{
	unsigned char	ch;

	ch = c;
	if (ch <= 127)
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	unsigned char	ch;

	ch = c;
	if (32 <= ch && ch <= 126)
		return (1);
	else
		return (0);
}


size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = 0;
		i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 && dest == src)
		return (dest);
	while (i < n)
	{
		*((unsigned char *)dest + i) = *((const unsigned char *)src + i);
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	tmp[100000];

	i = 0;
	if (n == 0 && dest == src)
		return (dest);
	while (i < n)
	{
		tmp[i] = *((const unsigned char *)src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dest + i) = tmp[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen((char *)src);
	while ((i + 1 < size) && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (!(size == 0))
		dest[i] = 0;
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (size == 0)
		return (size + src_len);
	dest_len = ft_strlen(dest);
	while ((dest_len + 1 + i < size) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (size != 0)
		dest[dest_len + i] = 0;
	if (size <= dest_len)
		return (size + src_len);
	else
		return (dest_len + src_len);
}

int	ft_toupper(int c)
{
	if (c < -1 && c > -129)
		return ((unsigned char)c);
	else if ('a' <= c && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}

int	ft_tolower(int c)
{
	if (c < -1 && c > -129)
		return ((unsigned char)c);
	else if ('A' <= c && c <= 'Z')
		return (c + ('a' - 'A'));
	else
		return (c);
}

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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (i < len)
	{
		if (big[i] == *little)
		{
			cnt = 0;
			j = 0;
			while (little[j])
			{
				if (big[i + j] == little[j])
					cnt++;
				j++;
			}
			if (j == cnt)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (0);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)ptr)[i++] = 0;
		return (ptr);
	}
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		s_len;
	int		i;

	i = 0;
	s_len = ft_strlen((char *)s);
	ptr = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!ptr)
		return (0);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
