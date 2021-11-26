/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:14 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 15:08:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_ary;
	int		index;
	int		len;

	index = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	new_ary = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_ary)
		return (NULL);
	while (*s1)
	{
		new_ary[index++] = *s1;
		s1++;
	}
	while (*s2)
	{
		new_ary[index++] = *s2;
		s2++;
	}
	new_ary[index] = '\0';
	return (new_ary);
}
