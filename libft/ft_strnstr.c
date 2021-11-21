/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:02:13 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/21 23:39:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == *little)
		{	
			cnt = 0;
			j = 0;
			while (little[j] && i + j < len)
			{
				if (big[i + j] == little[j])
					cnt++;
				j++;
			}
			if (ft_strlen((char *)little) == cnt)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}

/*
#include <bsd/string.h>
#include <stdio.h>
int main(void)
{
	char *s1 = "1234";
	char	*s3 = "1234";
	char	*s4 = "11234";

	printf("%s ", ft_strnstr(s3, s2, 4));
	printf("%s", strnstr(s3, s2, 4));
	// char	*s1 = "see FF your FF return FF now FF";
	// char	*s2 = "FF";
	// size_t	max = strlen(s1);

	// char	*s1 = "FF";
	// char	*s2 = "see F your F return F now F";
	// size_t	max = strlen(s2);

	// char	*s1 = "MZIRIBMZIRIBMZE123";
	// char	*s2 = "MZIRIBMZE";
	// size_t	max = strlen(s2);

	// printf("%s//", ft_strnstr(s1, s2, max));
	// printf("%s", strnstr(s1, s2, max));

	// char *big = "abcdef";
	// char *little = "abcdefghijklmnop";
	// size_t	max = strlen(big);

	// char *	big = "123456789";
	// char *	little = "9";
	// size_t	max = 8;

	// printf("%s//", ft_strnstr(big, little, max));
	// printf("%s", strnstr(big, little, max));

	// char	*s1 = "FF";
	// char	*s2 = "see F your FF return FF now FF";

	// char	*s1 = "";
	// char	*s2 = "oh no not the empty string !";
	// size_t	max = strlen(s2);

	// printf("%s//", ft_strnstr(s1, s2, max));
	// printf("%s", strnstr(s1, s2, max));

	// char	*s1 = "oh no not the empty string !";
	// char	*s2 = "";
	// size_t	max = 0;

	// char	*s1 = "AAAAAAAAAAAAA";
	// size_t	max = strlen(s1);

	// char	*s1 = "A";

	// size_t	size = 20 * 4;
	// char	*s2 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB";
	// char	*s1 = malloc(size + 1);

	// memset(s1, 'A', size);
	// s1[size] = 0;

	// printf("%s//", ft_strnstr(s1, s2, size));
	// printf("%s", strnstr(s1, s2, size));
}
*/