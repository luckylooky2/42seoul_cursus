/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:18 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:16:16 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = *((unsigned char *)s1) - *((unsigned char *)s2);
		if (res != 0)
			break ;
		if (*((unsigned char *)s1) == '\0' || *((unsigned char *)s2) == '\0')
			break ;
		s1++;
		s2++;
		i++;
	}
	return (res);
}
