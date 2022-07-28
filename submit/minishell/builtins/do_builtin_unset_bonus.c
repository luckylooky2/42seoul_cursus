/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_unset_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:06 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:56:37 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	do_builtin_unset(char **argv)
{
	env_commands(DELETE_ENV, argv + 1);
	global_status(SET_STATUS, 0);
}
