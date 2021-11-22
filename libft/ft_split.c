/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:46 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 00:05:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
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

static int	ft_len_first_malloc(char const *s, char c)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 0;
	len = ft_strlen((char *)s);
	while (i < len)
	{
		if (s[i] == c)
			cnt++;
		i++;
	}
	cnt += 2;
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*last_ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_len_first_malloc(s, c);
	ptr = (char **)ft_calloc(len, sizeof(char *));
	if (ptr == 0)
		return (0);
	last_ptr = ft_second_malloc(s, c, ptr, i);
	if ((last_ptr == 0) && (ptr[0] != 0))
		ft_free(ptr);
	return (ptr);
}

#include <stdio.h>
int main(void)
{
	char a[] = "";
	char b = 'z';
	char **ptr;
	int	i;

	i = 0;
	ptr = ft_split(a, b);
	while (ptr[i])
	{
		printf("%d %s\n", i, ptr[i]);
		i++;
	}
	free(ptr);
}