/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redirection_flag_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:21:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:58:21 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	skip_space(t_syntax *syn, int i, t_data *data)
{
	i++;
	while (syn->input[i] == ' ' && syn->meaning[i] == 1)
	{
		data->rd_flag[i] = ' ';
		i++;
	}
	return (i);
}

static void	assign_check(t_syntax *syn, int i, t_data *data)
{
	if (syn->input[i] == syn->input[i + 1])
	{
		if (syn->input[i] == '<')
			data->check = '2';
		else
			data->check = '4';
	}
	else
	{
		if (syn->input[i] == '<')
			data->check = '1';
		else
			data->check = '3';
	}
}

static void	assign_consecutive_flag(t_syntax *syn, int *num, t_data *data)
{
	while (!(((syn->input[*num] == '<' || syn->input[*num] == '>' \
			|| syn->input[*num] == ' ') \
			&& syn->meaning[*num] == 1) || syn->input[*num] == '\0'))
	{
		data->rd_flag[*num] = data->check;
		(*num)++;
	}
	(*num)--;
	data->check = '0';
}

static void	assign_flag(t_syntax *syn, int *i, t_data *data)
{
	int	skip;

	data->rd_flag[*i] = data->check;
	if (data->check == '2' || data->check == '4')
		data->rd_flag[++(*i)] = data->check;
	skip = skip_space(syn, *i, data);
	assign_consecutive_flag(syn, &skip, data);
	*i = skip;
}

void	assign_redirection_flag(t_syntax *syn, t_data *data)
{
	int	i;

	i = 0;
	while (syn->input[i])
	{
		if ((syn->input[i] == '<' || syn->input[i] == '>') \
			&& syn->meaning[i] == 1)
		{
			if (syn->input[i] == '<')
				data->infile_num++;
			else
				data->outfile_num++;
			assign_check(syn, i, data);
			assign_flag(syn, &i, data);
		}
		else
			data->rd_flag[i] = data->check;
		i++;
	}
}
