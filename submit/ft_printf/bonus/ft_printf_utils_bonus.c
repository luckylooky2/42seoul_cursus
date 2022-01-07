/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:07:43 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/23 20:54:56 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	unsigned_digits(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*make_uint_string(unsigned int n)
{
	char	*new_str;
	int		len;

	len = unsigned_digits(n, 10) + 1;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	while (n > 0)
	{
		new_str[len - 2] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (new_str);
}

char	*make_hex_string(unsigned long long n, int flag)
{
	char	*new_str;
	int		len;

	len = unsigned_digits(n, 16) + 1;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	if (n == 0)
		return (new_str);
	while (n > 0)
	{
		if (9 < n % 16 && n % 16 < 16 && flag == 0)
			new_str[len - 2] = (n % 16 - 10) + 'a';
		else if (9 < n % 16 && n % 16 < 16 && flag == 1)
			new_str[len - 2] = (n % 16 - 10) + 'A';
		else
			new_str[len - 2] = n % 16 + '0';
		n /= 16;
		len--;
	}
	return (new_str);
}

char	*add_prefix(char **str, int flag)
{
	char	*new_str;
	int		i;

	i = 0;
	if (*str == NULL)
		return (NULL);
	new_str = (char *)ft_calloc(sizeof(char), (ft_strlen(*str) + 2));
	while (new_str != NULL && (*str)[i] != '\0')
	{
		new_str[i + 2] = (*str)[i];
		i++;
	}
	free(*str);
	if (new_str != NULL && flag == 0)
	{
		new_str[0] = '0';
		new_str[1] = 'x';
	}
	return (new_str);
}

int	print_string(char *str, int *ret, t_option *opt)
{
	int	i;

	i = 0;
	if (opt->dot && opt->type == 's' && opt->prcs == 0)
		return (i);
	else if (opt->dot && (opt->type == 'd' || opt->type == 's')
	{
		if ((str[i] == '-' && opt->type == 'd')
			str++;
		while (i < opt->prcs && str[i] != '\0')
			write_and_plus(str[i++], ret, 1);
	}
	else if (opt->type != 'c')
	{
		while (str[i] != '\0')
		{
			if (!(str[i] == '-' && opt->type == 'd'))
				write_and_plus(str[i], ret, 1);
			i++;
		}
	}
	else
		write(1, &str[i++], 1);
	return (i);
}
