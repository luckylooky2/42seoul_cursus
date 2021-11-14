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
		res = *((char *)s1 + i) - *((char *)s2 + i);
		printf("%d %d\n", *((char *)s1 + i), *((char *)s2 + i));
		res = ((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i];
		printf("%d %d\n", ((const unsigned char *)s1)[i], ((const unsigned char *)s2)[i]);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (s == 0)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (i < len)
	{
		if (s_len > start)
			ptr[i] = s[start];
		else
			break ;
		i++;
		start++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		index;

	index = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	while (*s1)
	{
		ptr[index++] = *s1;
		s1++;
	}
	while (*s2)
	{
		ptr[index++] = *s2;
		s2++;
	}
	ptr[index] = 0;
	return (ptr);
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

int main()
{
	// char *ptr;
	// char *p;

	printf("%s ", (char *)calloc(0, 0));
	printf("%s", (char *)ft_calloc(0, 0));


	// char a[] = "hello ";
	// char b[] = "world";
	// char c[] = "";
	// char d[] = "";
	// char *e = 0;
	// char *f = 0;

	// // printf("%s", ft_strjoin(a, a));

	// // char a[] = "";
	// char b[] = "hello";
	// char bb[] = "2";
	// // char *c = 0;

	// printf("%s ", strnstr(b, bb, 0));
	// printf("%s", ft_strnstr(b, bb, 0));

	// char a[] = "----";
	// char *c = 0;

	// printf("%d\n", atoi(a));
	// printf("%d\n", ft_atoi(a));

	// char a[] = "abc";
	// char *b = 0;
	// char c[] = "";

	// // printf("%s ", strdup(b));
	// printf("%s", ft_strdup(b));

	// char a[] = "hello";
	// char b[] = "";
	// char *c = 0;
	
	// printf("%s", ft_substr(b, 1, 1));
}


// int main()
// {

// 	// unsigned int a = 3333333333;
// 	// char b = 120;

// 	// printf("%c", b);
// 	// char	a[] = "world! 123123123";
// 	// char	aaa[20] = "hello";
// 	// char	*ccc = 0;
// 	// char	*aa = 0;
// 	// char	bb[] = "123";
// 	// size_t i = 0;
// 	// int i = 0b1111111111111111111111111111111;

// 	// //int		b[] = {1, 2, 3, 4, 5};
// 	// printf("%d\n", i);
// 	// printf("%d\n", isalpha(i));
// 	// printf("%d\n", ft_isalpha(i));

// 	// printf("%ld\n", strlen(aa));

// 	// printf("%s ", (unsigned char *)ft_memset(aa, -1, 5));
// 	// printf("%s", (unsigned char *)memset(aa, -1, 5));

// 	// ft_bzero(aaa, 3);
// 	// printf("%d\n", b[2]);
// 	// bzero(aaa, 3);
// 	// printf("%d\n", b[2]);

// 	// printf("%s ", (unsigned char *)ft_memcpy(bb, a, 1));
// 	// printf("%s", (unsigned char *)memcpy(bb, a, 1));

// 	// i = ft_strlcpy(ccc, aa, 0);
// 	// i = strlcpy(ccc, aa, 0);
// 	// printf("%ld\n", i);
// 	// printf("%s", ccc);

// 	// // i = strlcat(aaa, a, 0);
// 	// i = ft_strlcat(aaa, aa, 0);
// 	// printf("%ld\n", i);
// 	// printf("%s", aaa);

// 	// printf("%d %d\n", tolower(0), ft_tolower(0));
// 	// printf("%d %d\n", tolower(-1), ft_tolower(-1));
// 	// printf("%d %d\n", tolower(65), ft_tolower(65));
// 	// printf("%d %d\n", tolower(127), ft_tolower(127));
// 	// printf("%d %d\n", tolower(-2), ft_tolower(-2));
// 	// printf("%d %d\n", tolower(-127), ft_tolower(-127));
// 	// printf("%d %d\n", tolower(-128), ft_tolower(-128));
// 	// printf("%d %d\n", tolower(-129), ft_tolower(-129));
// 	// printf("%d %d\n", tolower(-128555), ft_tolower(-128555));
// 	// printf("%d %d\n", tolower(128555), ft_tolower(128555));

// 	// const char a[] = "hello";
// 	// // const char c[] = "";
// 	// // const char *d = 0;
// 	// int b = 102;

// 	// printf("%s", strchr(a, b));
// 	// printf("%s", ft_strchr(a, b));

// 	// char a[] = "aaa";
// 	// char b[] = "aaa";
// 	// char *c = 0;
// 	// char *d = 0;

// 	// printf("%d\n", strncmp(b, a, 0));
// 	// printf("%d\n", ft_strncmp(, a, 0));

// 	// int a[] = {0, 1, 1231232, 3, 4 ,5};
// 	// // char d[] = "hello";
// 	// // char e[] = "";
// 	// // char *c = 0;
// 	// int b = 3;

// 	// // printf("%d", *(int *)memchr(a, b, 20));
// 	// printf("%d", *(int *)ft_memchr(a, b, 20));

// 	// char a[] = "helloc";
// 	// char b[] = "hellochanhyle";
// 	// // int c[] = {12, 121, 2, 3};
// 	// // int d[] = {12, -112412, 2, 3};

// 	// printf("%d\n", memcmp(a, b, 8));
// 	// printf("%d\n", ft_memcmp(a, b, 8));

// 	// char *a = 0;
// 	// char b[] = "";

// 	// printf("%ld", ft_strlen(a));
// }
