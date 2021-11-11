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
	if (s == 0)
		return (s);
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
	if (s == 0)
		return ;
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
	if (n == 0 || dest == src)
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
	if (n == 0 || dest == src)
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

int main()
{
	//char	a[] = "hello";
	//char	aaa[] = "1";
	//char	*ccc = 0;
	//char	*aa = 0;
	//char	*bb = 0;
	//size_t i = 0;
	

	//int		b[] = {1, 2, 3, 4, 5};
	// printf("%d\n", isalpha(EOF));
	// printf("%d\n", ft_isalpha(EOF));

	//printf("%ld\n", ft_strlen(a));

	//printf("%s\n", (unsigned char *)ft_memset(aaa, -1, 3));
	//printf("%s\n", (unsigned char *)memset(aaa, -1, 3));

	//ft_bzero(b, 8);
	//printf("%d\n", b[2]);
	//bzero(b, 8);
	//printf("%d\n", b[2]);

	//printf("%s\n", (unsigned char *)ft_memcpy(aa, aaa, 0));
	//printf("%s\n", (unsigned char *)memcpy(bb, ccc, 0));

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
}
