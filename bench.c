/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:35:09 by ainarako          #+#    #+#             */
/*   Updated: 2026/05/07 22:25:28 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bench.h"
#include "push_swap.h"

t_bench	*g_current_bench = NULL;

static void	print_bench_details(t_bench *bench)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(bench->sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(bench->sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(bench->ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(bench->pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(bench->pb, 2);
	ft_putstr_fd("\n[bench] ra: ", 2);
	ft_putnbr_fd(bench->ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(bench->rb, 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(bench->rr, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(bench->rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(bench->rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(bench->rrr, 2);
	ft_putstr_fd("\n", 2);
}

static void	print_bench(t_bench *bench, float disorder, char *strategy)
{
	int	int_part;
	int	dec_part;

	int_part = (int)(disorder * 100);
	dec_part = (int)((disorder * 100 - int_part) * 100);
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(int_part, 2);
	ft_putstr_fd(".", 2);
	if (dec_part < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(dec_part, 2);
	ft_putstr_fd("%\n[bench] strategy: ", 2);
	ft_putstr_fd(strategy, 2);
	ft_putstr_fd("\n[bench] total_ops:  ", 2);
	ft_putnbr_fd(get_total_ops(bench), 2);
	ft_putstr_fd("\n", 2);
	print_bench_details(bench);
}

void	run_benchmark(t_list **a, t_list **b, char *flag)
{
	t_bench	bench;
	float	disorder;
	char	*strategy;

	init_bench(&bench);
	disorder = compute_disorder(a);
	strategy = get_strategy_name(flag, disorder);
	if (flag)
		exec_algo(flag, a, b, &bench);
	else
		ft_adaptive_algo(a, b, &bench);
	print_bench(&bench, disorder, strategy);
}
