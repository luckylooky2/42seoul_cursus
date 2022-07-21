/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:04:05 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 18:57:11 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	printf_token_error()
{
	printf("syntax error\n");
}

void	printf_space(t_cmd *cmd)
{
	int i = 0;
	int j;
	int k;
	int l;
	int m;
	while (cmd->s_cmd[i])
	{
		j = 0;
		while (cmd->s_cmd[i][j])
		{
			k = 0;
			while (cmd->s_cmd[i][j][k])
			{
				l = 0;
				while (cmd->s_cmd[i][j][k][l])
				{
					printf("%s|\n",cmd->s_cmd[i][j][k][l]);
					m =0;
					while (cmd->s_cmd[i][j][k][l][m])
					{
						printf("%d ", cmd->s_status[i][j][k][l][m]);
						m++;
					}
					printf("\n");
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}
}

void	printf_pipe(t_cmd *cmd)
{
	int i = 0;
	int	j = 0;
	int k = 0;
	while (cmd->p_cmd[i])
	{
		j = 0;
		printf("start;\n");
		while (cmd->p_cmd[i][j])
		{
			k = 0;
			printf("and\n");
			while (cmd->p_cmd[i][j][k])
			{
				printf("pipe\n");
				printf("%s|\n", cmd->p_cmd[i][j][k]);
				k++;
			}
			j++;
		}
		i++;
	}
}

void	printf_operator(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (cmd->opr_cmd[i])
	{
		printf("opr\n");
		j = 0;
		while (cmd->opr_cmd[i][j])
		{
			printf("%s|\n",cmd->opr_cmd[i][j]);
			j++;
		}
		i++;
	} 
	i = 0;
	while (cmd->opr_cmd[i])
	{
		j =0;
		while (cmd->opr_cmd[i][j])
		{
			k = 0;
			while (cmd->opr_cmd[i][j][k])
			{
				printf("%d ",cmd->opr_status[i][j][k]);
				k++;
			}
			printf("\n");
			j++;
		}
		i++;
	}
}

void	printf_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("%s|\n", str[i]);
		i++;
	}
}

void	printf_split_status(int **str, char **s)
{
	int i;
	int j;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != '\0')
		{	
			printf("%d ",str[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	 printf_data(t_cmd *cmd, int max)
{
	int	i;

	i = 0;
	printf("%s\n",cmd->cmd_mod);
	while (i < max)
	{
		printf("%d ",cmd->status[0][i]);
		i++;
	}
	printf("\n");
}