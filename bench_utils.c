/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:35:02 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:35:04 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

void	init_bench(t_bench *bench)
{
	bench->sa = 0;
	bench->sb = 0;
	bench->ss = 0;
	bench->pa = 0;
	bench->pb = 0;
	bench->ra = 0;
	bench->rb = 0;
	bench->rr = 0;
	bench->rra = 0;
	bench->rrb = 0;
	bench->rrr = 0;
}

int	get_total_ops(t_bench *bench)
{
	int	total;

	total = bench->sa + bench->sb + bench->ss;
	total += bench->pa + bench->pb;
	total += bench->ra + bench->rb + bench->rr;
	total += bench->rra + bench->rrb + bench->rrr;
	return (total);
}

char	*get_strategy_name(char *flag, float disorder)
{
	if (flag)
	{
		if (!ft_strcmp(flag, "--simple"))
			return ("Simple / O(n²)");
		if (!ft_strcmp(flag, "--medium"))
			return ("Medium / O(n√n)");
		if (!ft_strcmp(flag, "--complex"))
			return ("Complex / O(n log n)");
	}
	if (disorder < 0.2)
		return ("Adaptive / O(n²)");
	if (disorder >= 0.2 && disorder < 0.5)
		return ("Adaptive / O(n√n)");
	return ("Adaptive / O(n log n)");
}

float	compute_disorder(t_list **a)
{
	int		total;
	int		inversions;
	t_list	*i;
	t_list	*j;

	total = ft_lstsize(*a);
	if (total <= 1)
		return (0.0);
	inversions = 0;
	i = *a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->value > j->value)
				inversions++;
			j = j->next;
		}
		i = i->next;
	}
	return ((float)inversions / (total * (total - 1) / 2));
}

void	exec_algo(char *flag, t_list **a, t_list **b, t_bench *bench)
{
	g_current_bench = bench;
	if (!ft_strcmp(flag, "--simple"))
		simple_sort(a, b);
	else if (!ft_strcmp(flag, "--medium"))
		medium_sort(a, b);
	else if (!ft_strcmp(flag, "--complex"))
		radix_sort(a, b);
	else
		radix_sort(a, b);
}
