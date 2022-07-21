/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:22:51 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/20 18:40:18 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_syntax *syn, t_data *data)
{
	int	len;

	len = ft_strlen(syn->input);
	if (len == 0)
		return ;
	data->infile_num = 0;
	data->outfile_num = 0;
	data->check = '0';
	data->cmd_num = 0;
	data->rd_flag = (char *)ft_calloc(sizeof(char), len + 1);
	if (data->rd_flag == NULL)
		panic_memory();
	ft_memset(data->rd_flag, '0', len);
}

void	remove_redirection(t_syntax *syntax, t_command *cmd)
{
	t_data	data;

	init_data(syntax, &data);
	assign_redirection_flag(syntax, &data);
	remove_character(syntax, &data);
	parse_redirection(syntax, &data, cmd);
	free(data.rd_flag);
}
