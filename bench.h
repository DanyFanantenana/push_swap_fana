/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:35:17 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:35:20 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCH_H
# define BENCH_H

typedef struct s_list	t_list;

typedef struct s_bench
{
	int					sa;
	int					sb;
	int					ss;
	int					pa;
	int					pb;
	int					ra;
	int					rb;
	int					rr;
	int					rra;
	int					rrb;
	int					rrr;
}						t_bench;

void					init_bench(t_bench *bench);
void					bench_sa(t_bench *bench);
void					bench_sb(t_bench *bench);
void					bench_ss(t_bench *bench);
void					bench_pa(t_bench *bench);
void					bench_pb(t_bench *bench);
void					bench_ra(t_bench *bench);
void					bench_rb(t_bench *bench);
void					bench_rr(t_bench *bench);
void					bench_rra(t_bench *bench);
void					bench_rrb(t_bench *bench);
void					bench_rrr(t_bench *bench);
int						get_total_ops(t_bench *bench);
char					*get_strategy_name(char *flag, float disorder);
void					run_benchmark(t_list **a, t_list **b, char *flag);
float					compute_disorder(t_list **a);
void					exec_algo(char *flag, t_list **a, t_list **b,
							t_bench *bench);
void					ft_adaptive_algo(t_list **stack_a, t_list **stack_b,
							t_bench *bench);

extern char				*g_algo_flag;

#endif
