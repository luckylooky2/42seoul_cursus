/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:25:58 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/20 18:43:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_forward(t_syntax *syn, t_data *data, int dst, int src)
{
	int	len;

	len = ft_strlen(data->rd_flag + dst) + 1;
	ft_memmove(data->rd_flag + dst, data->rd_flag + src, len);
	ft_memmove(syn->input + dst, syn->input + src, len);
	ft_memmove(syn->meaning + dst, syn->meaning + src, len);
}

static void	remove_space(t_syntax *syn, t_data *data)
{
	int		i;

	i = 0;
	while (data->rd_flag[i])
	{
		if (data->rd_flag[i] == ' ')
		{
			if (data->rd_flag[i + 1] == ' ')
			{
				move_forward(syn, data, i, i + 1);
				continue ;
			}
		}
		i++;
	}
}

static void	remove_special_character(t_syntax *syn, t_data *data)
{
	int	i;

	i = 0;
	while (data->rd_flag[i])
	{
		if (syn->meaning[i] && !syn->meaning[i + 1] && (syn->input[i] == '\\' \
			|| syn->input[i] == '\"' || syn->input[i] == '\''))
		{
			move_forward(syn, data, i, i + 1);
			continue ;
		}
		else if (!syn->meaning[i] && syn->meaning[i + 1] \
			&& (syn->input[i + 1] == '\"' || syn->input[i + 1] == '\''))
		{
			move_forward(syn, data, i + 1, i + 2);
			continue ;
		}
		if ((syn->input[i] == '\"' && syn->input[i + 1] == '\"' ) \
			|| (syn->input[i] == '\'' && syn->input[i + 1] == '\''))
		{
			move_forward(syn, data, i, i + 2);
			continue ;
		}
		i++;
	}
}

void	remove_character(t_syntax *syn, t_data *data)
{
	remove_special_character(syn, data);
	remove_space(syn, data);
}
