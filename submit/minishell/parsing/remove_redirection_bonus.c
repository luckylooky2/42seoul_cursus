/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirection_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:22:51 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:58:42 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	init_data(t_syntax *syn, t_data *data)
{
	int	len;

	len = ft_strlen(syn->input);
	data->infile_num = 0;
	data->outfile_num = 0;
	data->check = '0';
	data->cmd_num = 0;
	data->rd_flag = (char *)ft_calloc(sizeof(char), len + 1);
	if (data->rd_flag == NULL)
		panic_memory();
	ft_memset(data->rd_flag, '0', len);
}

static void	move_forward(t_syntax *syn, t_data *data, int dst, int src)
{
	int	len;

	len = ft_strlen(data->rd_flag + dst);
	ft_memmove(data->rd_flag + dst, data->rd_flag + src, len);
	ft_memmove(syn->input + dst, syn->input + src, len);
	ft_memmove(syn->meaning + dst, syn->meaning + src, len - 1);
}

static void	remove_special_character(t_syntax *s, t_data *data)
{
	int	i;

	i = 0;
	while (data->rd_flag[i])
	{
		if ((s->meaning[i] == 1 && data->rd_flag[i] != '0' && (\
		s->input[i] == '\\' || s->input[i] == '\"' || s->input[i] == '\'')) \
		|| data->rd_flag[i] == ' ')
		{
			move_forward(s, data, i, i + 1);
			continue ;
		}
		i++;
	}
}

void	remove_redirection(t_syntax *syntax, t_command *cmd)
{
	t_data	data;

	init_data(syntax, &data);
	assign_redirection_flag(syntax, &data);
	remove_special_character(syntax, &data);
	parse_redirection(syntax, &data, cmd);
	free(data.rd_flag);
}
