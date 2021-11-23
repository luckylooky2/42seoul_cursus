/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:54:19 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:16:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	const char		*ptr;

	ch = c;
	ptr = 0;
	while (*s)
	{
		if (*s == ch)
			ptr = s;
		s++;
	}
	if (c == 0)
		ptr = s;
	return ((char *)ptr);
}
