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
	char			*new_str;
	unsigned int	i;

	i = 0;
	if ((*f) == NULL)
		return (NULL);
	new_str = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (*s)
	{
		new_str[i] = (*f)(i, *s);
		i++;
		s++;
	}
	new_str[i] = '\0';
	return (new_str);
}
