/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:12:02 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:15:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_ary;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s);
	new_ary = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_ary)
		return (NULL);
	while (s[i])
	{
		new_ary[i] = s[i];
		i++;
	}
	new_ary[i] = '\0';
	return (new_ary);
}
