/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:54:05 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:15:50 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*curr;

	curr = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			curr = s;
			break ;
		}
		s++;
	}
	if ((char)c == '\0')
		curr = s;
	return ((char *)curr);
}
