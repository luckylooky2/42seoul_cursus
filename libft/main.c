#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include <stdlib.h>

int	ft_isalpha(int c)
{
	unsigned char	ch;

	if (c == EOF)
		return (0);
	ch = c;
	if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'))
		return (1);
	else
		return (0);
}
size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s == 0)
		return (0);
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
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
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
		tmp[i] = *((unsigned char *)src + i);
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
	len = 0;
	while (src[len])
		len++;
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
	src_len = 0;
	while (src[src_len])
		src_len++;
	dest_len = ft_strlen(dest);
	while ((dest_len + 1 + i < size) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (!(size == 0))
		dest[dest_len + i] = 0;
	if (size < dest_len)
		return (size + src_len);
	else
		return (dest_len + src_len);
}

int	ft_toupper(int c)
{
	if (c < -1 && c > -129)
		return ((unsigned char)c);
	else if ('a' <= c && c <= 'z')
		return(c - ('a' - 'A'));
	else
		return (c);
}

int	ft_tolower(int c)
{
	if (c < -1 && c > -129)
		return ((unsigned char)c);
	else if ('A' <= c && c <= 'Z')
		return(c + ('a' - 'A'));
	else
		return (c);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	char			*ptr;

	ch = c;
	ptr = 0;
	while (*s)
	{
		if (*s == ch)
		{
			ptr = (char *)s;
			break ;
		}
		s++;
	}
	if (c == 0)
		ptr = (char *)s;
	return (ptr);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	char			*ptr;

	ch = c;
	ptr = 0;
	while (*s)
	{
		if (*s == ch)
			ptr = (char *)s;
		s++;
	}
	if (c == 0)
		ptr = (char *)s;
	return (ptr);
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
	unsigned char	ch;
	void			*ptr;
	size_t			i;

	ch = c;
	i = 0;
	ptr = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == ch)
		{
			ptr = ((unsigned char *)s + i);
			break ;
		}
		i++;
	}
	return (ptr);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = *((unsigned char *)s1 + i) - *((unsigned char *)s2 + i);
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

int main()
{
	// char a[] = "";
	// char b[] = "hello";
	// char bb[] = " ";
	// char *c = 0;

	// printf("%s ", strnstr(c, bb, 1));
	// //printf("%s", ft_strnstr(c, bb, 1));

	// char a[] = "----";
	// char *c = 0;

	// printf("%d\n", atoi(a));
	// printf("%d\n", ft_atoi(a));

	char a[] = "abc";
	char *b = 0;
	char c[] = "";

	printf("%s ", strdup(c));
	printf("%s", ft_strdup(c));
}

/*
int main()
{
	char	a[] = "hello";
	char	aaa[] = "11251251";
	char	*ccc = 0;
	char	*aa = 0;
	char	bb[] = "";
	size_t i = 0;

	// //int		b[] = {1, 2, 3, 4, 5};
	// // printf("%d\n", isalpha(EOF));
	// // printf("%d\n", ft_isalpha(EOF));

	// //printf("%ld\n", ft_strlen(a));

	// printf("%s ", (unsigned char *)ft_memset(aa, -1, 5));
	// printf("%s", (unsigned char *)memset(aa, -1, 5));

	ft_bzero(aaa, 3);
	// printf("%d\n", b[2]);
	bzero(aaa, 3);
	// printf("%d\n", b[2]);

	// printf("%s ", (unsigned char *)ft_memmove(aaa, bb, 0));
	//printf("%s", (unsigned char *)memmove(aaa, bb, 0));

	// i = ft_strlcpy(ccc, a, 1);
	// //i = strlcpy(ccc, a, 1);
	// printf("%ld\n", i);
	// printf("%s", ccc);

	// i = strlcat(aaa, a, 1);
	// //i = ft_strlcat(aaa, a, 1);
	// printf("%ld\n", i);
	// printf("%s", aaa);

	// printf("%d %d\n", tolower(0), ft_tolower(0));
	// printf("%d %d\n", tolower(-1), ft_tolower(-1));
	// printf("%d %d\n", tolower(65), ft_tolower(65));
	// printf("%d %d\n", tolower(127), ft_tolower(127));
	// printf("%d %d\n", tolower(-2), ft_tolower(-2));
	// printf("%d %d\n", tolower(-127), ft_tolower(-127));
	// printf("%d %d\n", tolower(-128), ft_tolower(-128));
	// printf("%d %d\n", tolower(-129), ft_tolower(-129));
	// printf("%d %d\n", tolower(-128555), ft_tolower(-128555));
	// printf("%d %d\n", tolower(128555), ft_tolower(128555));

	// char a[] = "hello";
	// char c[] = "";
	// int b = 0;

	// printf("%s", strchr(c, b));
	// // printf("%s", ft_strchr(c, b));

	// char a[] = "aaa";
	// char b[] = "aaa";
	// char *c = 0;
	// char *d = 0;

	// printf("%d\n", strncmp(b, a, 0));
	// printf("%d\n", ft_strncmp(, a, 0));

	// int a[] = {0, 1, 1231232, 3, 4 ,5};
	// char d[] = "hello";
	// char e[] = "";
	// char *c = 0;
	// int b = 'o';

	// printf("%s", (unsigned char *)memchr(e, b, 5));
	// // printf("%s", (unsigned char *)ft_memchr(e, b, 5));

	// // char a[] = "helloc";
	// // char b[] = "hellochanhyle";
	// int c[] = {0, -122, 2, 3};
	// int d[] = {0, -2, 2, 3};

	// printf("%d\n", memcmp(c, d, 5));
	// printf("%d\n", ft_memcmp(c, d, 5));

	// char *a = 0;
	// char b[] = "";

	// printf("%ld", ft_strlen(a));
}
*/