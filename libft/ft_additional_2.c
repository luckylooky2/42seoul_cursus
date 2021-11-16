/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:28:33 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 09:55:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char const *s, char const *str1, char *ptr)
{
	int	j;

	j = 0;
	while (*s != *str1)
	{
		ptr[j] = *str1;
		j++;
		str1++;
	}
	ptr[j] = 0;
	return ((char *)str1);
}

static char	**ft_split_2(char const *s, char c, char **ptr, int i)
{
	char const	*str1;

	str1 = s;
	while (*s)
	{
		if (*s == c || *(s + 1) == 0)
		{
			if (*s != c && *(s + 1) == 0)
				s++;
			if (*s != *str1)
			{
				ptr[i] = (char *)malloc(sizeof(char) * (s - str1 + 1));
				if (ptr[i] == 0)
					return (0);
				str1 = (char const *)ft_copy(s, str1, ptr[i]);
				i++;
			}
			str1++;
		}
		if (*s != 0)
			s++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen((char *)s) + 1;
	ptr = (char **)malloc(sizeof(char *) * len);
	if (ptr == 0)
	{
		free(ptr);
		return (0);
	}
	while (len-- >= 0)
		ptr[len] = 0;
	ptr = ft_split_2(s, c, ptr, i);
	if (ptr == 0)
	{
		free(ptr);
		return (0);
	}
	else
		return (ptr);
}

static int	ft_create_array(int n)
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
		return ("-2147483648");
	len = ft_create_array(n);
	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr)
		return (0);
	ptr[len - 1] = 0;
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	while (n > 0)
	{
		ptr[len - 2] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

/*
#include <stdio.h>
int main()
{
// 	char **ptr;
// 	char a[] = "how's          theweather?it'ssunny!wow?really???yes!";
// 	char b = ' ';
// 	int	i = 0;

// 	ptr = ft_split(a, b);
// 	while (ptr[i])
// 	{
// 		printf("%d ", i);
// 		printf("%s\n", ptr[i++]);
// 	}

	// char *p;

	a = ft_itoa(-2147483648);
	printf("%s", a);
	return 0;
}
*/
