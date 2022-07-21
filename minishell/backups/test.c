/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:10:13 by youhan            #+#    #+#             */
/*   Updated: 2022/07/15 19:09:30 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// -1 : malloc_error
// -2 : parsing_error


void	make_link(t_cmd *cmd, int i)
{
	int	path;
	int	*bracket;
	int	j;
	int	k;

	j = 0;
	k = 1;
	init_bracket(cmd->mod[i], &bracket, cmd->mod_status[i]);
	delim_bracket(cmd->mod[i], cmd->mod_status[i], &bracket);
	path = count_oprator(cmd->mod[i], bracket);
	cmd->link[i] = (t_link *)malloc(sizeof(t_link) * (path + 1));
	if (cmd->link[i] == NULL)
		panic(NULL);
	cmd->link[i][0] = NONE;
	while (k < path)
	{
		j = skip_operator(cmd->mod[i], cmd->status[i], j, &bracket[j]);
		cmd->link[i][k] = AND;
		if (cmd->mod[i][j + 1] == '|')
			cmd->link[i][k] = OR;
		k++;
		j += 3;
	}
	free(bracket);
	cmd->link[i][k] = NONE;
}

void	printf_link(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < count_char_pointer_3(cmd->opr_cmd))
	{
		j = 0;
		while (j < 1 + count_char_pointer_2(cmd->opr_cmd[i]))
		{
			printf("%d ",cmd->link[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}


void	make_links(t_cmd *cmd)
{
	int	i;

	i =	count_char_pointer_2(cmd->mod);
	cmd->link = (t_link **)malloc(sizeof(t_link *) * i);
	if (cmd->link == NULL)
		panic(NULL);
	i = 0;
	while (i < count_char_pointer_2(cmd->mod))
	{
		make_link(cmd, i);
		i++;
	}
	
}

int	count_backslash_after(char *cmd, int *status)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' && status[i] == -2)
		{
			i++;
			if (cmd[i] == '\0')
				return (-1);
		}
		i++;
		count++;
	}
	return (count);
}

void	change_backslash_after(char *cmd, int *status, char **cmd_mod, int **cmd_status)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' && status[i] == -2)
		{
			(*cmd_mod)[j] = cmd[i + 1];
			(*cmd_status)[j] = status[i + 1];
			j++;
			i++;
		}
		else
		{
			printf("aas:%d\n",i);
			(*cmd_mod)[j] = cmd[i];
			(*cmd_status)[j] = status[i];
			j++;
		}
		i++;
	}
	(*cmd_mod)[j] = '\0';
}

int	del_backslash_after(char **cmd, int **status)
{
	char	*cmd_mod;
	int		*cmd_status;

	if (count_backslash_after(*cmd, *status) == -1)
		return (-1);
	printf("count : %d\n", count_backslash_after(*cmd, *status));
	cmd_mod = (char *)malloc(sizeof(char) * count_backslash_after(*cmd, *status) + 1);
	cmd_status = (int *)malloc(sizeof(int) * count_backslash_after(*cmd, *status));
	if (cmd_mod == NULL || cmd_status == NULL)
		exit(-1);
	cmd_mod[count_backslash_after(*cmd, *status)] = 0;
	change_backslash_after(*cmd, *status, &cmd_mod, &cmd_status);
	free(*cmd);
	free(*status);
	*cmd = cmd_mod;
	*status = cmd_status;
	return (1);
}

char	***test(char *str)
{
	t_cmd	cmd;

	if (str[0] == '\0')
		return (NULL);
	cmd.cmd = str;
	if (del_backslash(&cmd) == -1)
		return (NULL);
	if (del_quotes(&cmd) == -1)
		return (NULL);
	// printf_data(&cmd, ft_strlen(cmd.cmd));
	// printf_data(&cmd, ft_strlen(cmd.cmd_mod));
	if (count_bracket(cmd.cmd_mod, cmd.status[0]) == -1)
		return (NULL);
	if (init_bracket(cmd.cmd_mod, &cmd.status[1], cmd.status[0]) == -1)
		return (NULL);
	if (del_semicolon(&cmd) == -1)
		return (NULL);
	if (check_bracket(cmd.mod, cmd.status[0]) == -1)
		return (NULL);
	// printf_split(cmd.mod);
	if (del_operator(&cmd) == -1)
		return (NULL);
	if (del_pipe(&cmd) == -1)
		return (NULL);
	if (error_token(cmd) == -1)
	{
		printf_token_error();
		return (NULL);
	}
	if (del_space(&cmd) == -1)
		return (NULL);
	// make_links(&cmd);
	// printf_link(&cmd);
	// after
	// printf_space(&cmd);
	// printf_space(&cmd);
	if (del_backslash_after(&(cmd.s_cmd[0][0][0][0]), &(cmd.s_status[0][0][0][0])) == -1)
		return (NULL);
	printf_space(&cmd);
	if (del_quotes_after(&(cmd.s_cmd[0][0][0][0]), &(cmd.s_status[0][0][0][0])) == -1)
		return (NULL);
	printf_space(&cmd);
	env_expansion(&(cmd.s_cmd[0][0][0][0]), &(cmd.s_status[0][0][0][0]));
	printf_space(&cmd);
	printf("FFFFF\n");
	add_history(cmd.cmd);
	return (cmd.s_cmd[0][0]);
}
