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
	const char	*curr;

	curr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			curr = s;
		s++;
	}
	if ((char)c == '\0')
		curr = s;
	return ((char *)curr);
}
