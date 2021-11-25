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
	int		i;

	index = 0;
	i = 0;
	new_ary = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_ary)
		return (NULL);
	while (s1[i])
	{
		new_ary[index++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_ary[index++] = s2[i];
		i++;
	}
	new_ary[index] = '\0';
	return (new_ary);
}
