/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:11:53 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/08 21:11:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	s_len = ft_strlen(s);
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
	int		i;

	index = 0;
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[index++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[index++] = s2[i];
		i++;
	}
	ptr[index] = 0;
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		ptr_index;
	int		set_index;
	int		cnt;

	ptr_index = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	while (*s1)
	{
		set_index = 0;
		cnt = 0;
		while (set[set_index])
		{
			if (*s1 != set[set_index])
				cnt++;
			set_index++;
		}
		if (set_index == cnt)
			ptr[ptr_index++] = *s1;
		s1++;
	}
	ptr[ptr_index] = 0;
	return (ptr);
}

static void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return ;
}

static char	*ft_copy(char const *str2, char const *str1, char *ptr_ary)
{
	int	i;

	i = 0;
	while (*str2 != *str1)
	{
		ptr_ary[i] = *str1;
		i++;
		str1++;
	}
	ptr_ary[i] = 0;
	return ((char *)str1);
}

static char	*ft_second_malloc(char const *str2, char c, char **ptr, int i)
{
	char const	*str1;

	str1 = str2;
	while (*str2)
	{
		if (*str2 == c || *(str2 + 1) == 0)
		{
			if (*str2 != c && *(str2 + 1) == 0)
				str2++;
			if (*str2 != *str1)
			{
				ptr[i] = (char *)malloc(sizeof(char) * (str2 - str1 + 1));
				if (ptr[i] == 0)
					return (ptr[i]);
				str1 = (char const *)ft_copy(str2, str1, ptr[i]);
				i++;
			}
			str1++;
		}
		if (*str2 != 0)
			str2++;
	}
	if (i == 0)
		return (ptr[i]);
	return (ptr[i - 1]);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*last_ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen((char *)s) / 2 + 2;
	ptr = (char **)ft_calloc(len, sizeof(char *));
	if (ptr == 0)
		return (0);
	last_ptr = ft_second_malloc(s, c, ptr, i);
	if ((last_ptr == 0) && (ptr[0] != 0))
	{
		ft_free(ptr);
		return (0);
	}
	else if ((last_ptr == 0) && (ptr[0] == 0))
	{
		free(ptr);
		return (ptr);
	}
	else
		return (ptr);
}

static int	ft_number_of_digits(int n)
{
	int		len;

	len = 1;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;

	if (n == -2147483648)
	{
		ptr = ft_itoa(n + 1);
		ptr[10] = '8';
		return (ptr);
	}
	len = ft_number_of_digits(n);
	ptr = (char *)ft_calloc(len, sizeof(char));
	if (!ptr)
		return (0);
	ptr[0] = '0';
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	while (n > 0)
	{
		ptr[len-- - 2] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (0);
	while (*s)
	{
		ptr[i] = (*f)(i, *s);
		i++;
		s++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		(*f)(i, s);
		i++;
		s++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, 1);
		return ;
	}
	else
	{
		c = n % 10 + '0';
		ft_putnbr_fd(n / 10, fd);
		write(fd, &c, 1);
	}
}
