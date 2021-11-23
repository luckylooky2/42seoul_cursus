/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:18:05 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 15:11:07 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!ptr)
		return (0);
	while (*s)
	{
		if ((*f) != 0)
			ptr[i] = (*f)(i, *s);
		i++;
		s++;
	}
	ptr[i] = 0;
	return (ptr);
}
