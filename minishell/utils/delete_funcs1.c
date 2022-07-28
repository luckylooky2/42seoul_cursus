/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_funcs1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:03:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 23:04:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_t_syntax(void *arg)
{
	t_syntax	*syntax;

	if (arg == NULL)
		return ;
	syntax = arg;
	free(syntax->input);
	syntax->input = NULL;
	free(syntax->meaning);
	syntax->meaning = NULL;
	free(arg);
}