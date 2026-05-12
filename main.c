/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 08:47:28 by faharila          #+#    #+#             */
/*   Updated: 2026/04/22 08:47:28 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"
#include "get_next_line.h"
#include "libft.h"

int		g_is_bench = 0;

static void	sort_stack(t_list **stack_a, t_list **stack_b, char *algo_flag)
{
	if (algo_flag)
	{
		if (!ft_strcmp(algo_flag, "--simple"))
			simple_sort(stack_a, stack_b);
		else if (!ft_strcmp(algo_flag, "--medium"))
			medium_sort(stack_a, stack_b);
		else if (!ft_strcmp(algo_flag, "--complex"))
			radix_sort(stack_a, stack_b);
	}
	else if (ft_lstsize(*stack_a) <= 5)
		simple_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}

static void	remove_arg_at_index(int *argc, char **argv, int index)
{
	int	j;

	j = index;
	while (j < *argc - 1)
	{
		argv[j] = argv[j + 1];
		j++;
	}
	(*argc)--;
	argv[*argc] = NULL;
}

static int	parse_args(int *argc, char **argv, char **algo_flag)
{
	int	i;

	i = 1;
	*algo_flag = NULL;
	g_is_bench = 0;
	while (i < *argc)
	{
		if (!ft_strcmp(argv[i], "--bench"))
		{
			g_is_bench = 1;
			remove_arg_at_index(argc, argv, i);
			continue ;
		}
		else if (!ft_strcmp(argv[i], "--simple")
			|| !ft_strcmp(argv[i], "--medium")
			|| !ft_strcmp(argv[i], "--complex")
			|| !ft_strcmp(argv[i], "--adaptive"))
		{
			*algo_flag = argv[i];
			remove_arg_at_index(argc, argv, i);
			continue ;
		}
		i++;
	}
	return (*argc >= 2);
}

static void	init_stacks(t_list ***stack_a, t_list ***stack_b)
{
	*stack_a = (t_list **)malloc(sizeof(t_list));
	*stack_b = (t_list **)malloc(sizeof(t_list));
	*(*stack_a) = NULL;
	*(*stack_b) = NULL;
}

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	char	*algo_flag;
	t_bench	bench;

	if (!parse_args(&argc, argv, &algo_flag))
		return (-1);
	ft_check_args(argc, argv);
	init_stacks(&stack_a, &stack_b);
	initstack(stack_a, argc, argv);
	if (is_sorted(stack_a))
	{
		free_stack(stack_a);
		free_stack(stack_b);
		return (0);
	}
	if (g_is_bench)
		run_benchmark(stack_a, stack_b, algo_flag);
	else if (algo_flag && !ft_strcmp(algo_flag, "--adaptive"))
		ft_adaptive_algo(stack_a, stack_b, &bench);
	else
		sort_stack(stack_a, stack_b, algo_flag);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
