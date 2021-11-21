/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:54:05 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/21 21:57:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

#include <string.h>
#include <stdio.h>

int main()
{
	char s[] = "hello";

	printf("%s", ft_strchr(s, 'z'));
	printf("%s", strchr(s, 'z'));
	printf("%s", ft_strchr(s, 'z'+256));
	printf("%s", strchr(s, 'z'+256));
}