/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_r_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:34:47 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:34:50 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

void	bench_ra(t_bench *bench)
{
	bench->ra++;
}

void	bench_rb(t_bench *bench)
{
	bench->rb++;
}

void	bench_rr(t_bench *bench)
{
	bench -> rr ++;
}

void	bench_rra(t_bench *bench)
{
	bench->rra++;
}

void	bench_rrb(t_bench *bench)
{
	bench->rrb++;
}
