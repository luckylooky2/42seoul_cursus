/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:18:21 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/09 23:59:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j])
			{
				if (big[i + j] == little[j])
					cnt++;
				j++;
			}
			if (j == cnt)
				return ((char *)(big + i));
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
	while (nptr[i] == ' ' || nptr[i] == '\t')
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		res += res * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		s_len;
	int		i;

	i = 0;
	s_len = ft_strlen((char *)s);
	ptr = (char *)malloc(sizeof(char) * (s_len + 1));
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
