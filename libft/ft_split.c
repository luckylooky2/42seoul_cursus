/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:46 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 12:13:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_copy(char const *s, char const *start, char *ptr)
{
	int	i;

	i = 0;
	while (*s != *start)
	{
		ptr[i] = *start;
		i++;
		start++;
	}
	ptr[i] = 0;
	return ((char *)start);
}

static char	*ft_second_malloc(char const *s, char c, char **ptr, int i)
{
	char const	*start;

	start = s;
	while (*s)
	{
		if (*s == c || *(s + 1) == 0)
		{
			if (*s != c && *(s + 1) == 0)
				s++;
			if (*s != *start)
			{
				ptr[i] = (char *)malloc(sizeof(char) * (s - start + 1));
				if (ptr[i] == 0)
					return (ptr[i]);
				start = (char const *)ft_copy(s, start, ptr[i]);
				i++;
			}
			start++;
		}
		if (*s != 0)
			s++;
	}
	return (ptr[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*is_ptr_null;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen((char *)s) / 2 + 2;
	ptr = (char **)malloc(sizeof(char *) * len);
	if (ptr == 0)
		return (0);
	while (i < len)
		ptr[i++] = 0;
	is_ptr_null = ft_second_malloc(s, c, ptr, 0);
	if (is_ptr_null == 0)
	{
		i = 0;
		while (ptr[i])
			free(ptr[i++]);
		return (0);
	}
	else
		return (ptr);
}


int main(void)
{
	char a[] = "   ";
	char b = ' ';
	char **ptr;
	int	i;

	i = 0;
	ptr = ft_split(a, b);
	while (ptr[i])
	{
		printf("%d %s\n", i, ptr[i]);
		i++;
	}
}
