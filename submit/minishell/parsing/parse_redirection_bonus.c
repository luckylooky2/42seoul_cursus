/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:12:57 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:58:40 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	return_end_index(char *start, int i, t_syntax *syn)
{
	if ((syn->input[i] == '<' || syn->input[i] == '>') \
		&& syn->meaning[i] == 1)
		i++;
	i++;
	while (start[i])
	{
		if (start[i] == '0' \
			|| ((syn->input[i] == '<' || syn->input[i] == '>') \
			&& syn->meaning[i] == 1))
			return (i);
		i++;
	}
	return (i);
}

static char	*join_file_and_redirection(char *cut, t_data *data, int i)
{
	char	*rd;

	if (data->rd_flag[i] == '1')
		rd = "< ";
	else if (data->rd_flag[i] == '2')
		rd = "<< ";
	else if (data->rd_flag[i] == '3')
		rd = "> ";
	else if (data->rd_flag[i] == '4')
		rd = ">> ";
	if (data->rd_flag[i] == '1' || data->rd_flag[i] == '3')
	{
		if (data->rd_flag[i + 1] == ' ')
			return (ft_strjoin(rd, &cut[2]));
		else
			return (ft_strjoin(rd, &cut[1]));
	}
	else
	{
		if (data->rd_flag[i + 2] == ' ')
			return (ft_strjoin(rd, &cut[3]));
		else
			return (ft_strjoin(rd, &cut[2]));
	}
}

static char	*cut_end(t_syntax *syn, int i, t_data *data)
{
	int		end;
	char	*cut;

	end = return_end_index(data->rd_flag, i, syn);
	cut = ft_substr(&syn->input[i], 0, end - i);
	if (cut == NULL)
		panic_memory();
	return (cut);
}

static int	make_string(t_syntax *syn, int i, t_data *data, t_command *cmd)
{
	char	*cut;
	char	*join;
	int		end;

	end = return_end_index(data->rd_flag, i, syn);
	cut = cut_end(syn, i, data);
	join = join_file_and_redirection(cut, data, i);
	if (join == NULL)
		panic_memory();
	if (syn->input[i] == '<')
		ft_deq_push_back(cmd->input, join);
	else
		ft_deq_push_back(cmd->output, join);
	while (i < end)
	{
		syn->input[i] = ' ';
		syn->meaning[i] = 1;
		i++;
	}
	free(cut);
	return (end);
}

void	parse_redirection(t_syntax *syn, t_data *data, t_command *cmd)
{
	int		i;

	i = 0;
	while ((data->rd_flag)[i])
	{
		if ((data->rd_flag)[i] != ' ' && (data->rd_flag)[i] != '0')
			i = make_string(syn, i, data, cmd);
		else
			i++;
	}
}
