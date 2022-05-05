/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:09:01 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 10:09:32 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_count(t_aux *aux)
{
	aux->cnt = 0;
	aux->sorted = 0;
}

void	init_aux(t_aux *aux)
{
	aux->cnt = 0;
	aux->pa = 0;
	aux->pb = 0;
	aux->ra = 0;
	aux->rb = 0;
	aux->sorted = 0;
	aux->big = 0;
	aux->small = 0;
}
