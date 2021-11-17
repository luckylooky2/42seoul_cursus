/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:02:13 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 12:02:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	j = ft_strlen((char *)little);
	if (j > len)
		j = len;
	if (j == 0)
		return ((char *)big);
	while (i < len)
	{
		if (big[i] == *little)
		{
			cnt = 0;
			j = 0;
			while (little[j] && i + j <= len)
			{
				if (big[i + j] == little[j])
					cnt++;
			}
			if (j == cnt)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char a[] = "MZIRIBMZIRIBMZE123";
	char b[] = "MZIRIBMZE";
	char *c = 0;

	printf("%s ", ft_strnstr(a, b, 10));
	printf("%s", strnstr(a, b, 10));
}
*/