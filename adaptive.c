/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:07:16 by faharila          #+#    #+#             */
/*   Updated: 2026/04/23 15:40:14 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

void	ft_adaptive_algo(t_list **a, t_list **b, t_bench *bench)
{
	float	disorder;

	disorder = compute_disorder(a);
	g_current_bench = bench;
	if (disorder < 0.2)
		simple_sort(a, b);
	else if (disorder < 0.5)
		medium_sort(a, b);
	else
		radix_sort(a, b);
}
