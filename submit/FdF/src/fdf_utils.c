/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:46:20 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 23:43:34 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	longlong;

	i = 0;
	sign = 1;
	longlong = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		longlong = longlong * 10 + (nptr[i++] - '0');
	if (sign == -1)
		longlong *= -1;
	if (sign == 1 && (longlong < 0 || i > 19))
		return (-1);
	else if (sign == -1 && (longlong > 0 || i > 19))
		return (0);
	else
		return ((int)longlong);
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}
