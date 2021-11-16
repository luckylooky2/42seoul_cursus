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
