/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 00:21:03 by faharila          #+#    #+#             */
/*   Updated: 2026/05/11 09:05:01 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

int	swap(t_list **stack)
{
	t_list	*head;
	t_list	*next;
	int		tmp_val;
	int		tmp_index;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	next = head->next;
	if (!head && !next)
		ft_error();
	tmp_val = head->value;
	tmp_index = head->index;
	head->value = next->value;
	head->index = next->index;
	next->value = tmp_val;
	next->index = tmp_index;
	return (0);
}

int	sa(t_list **stack_a, t_bench *bench)
{
	if (swap(stack_a) == -1)
		return (-1);
	if (bench)
		bench_sa(bench);
	ft_putendl_fd("sa", 1);
	return (0);
}

int	sb(t_list **stack_b, t_bench *bench)
{
	if (swap(stack_b) == -1)
		return (-1);
	if (bench)
		bench_sb(bench);
	ft_putendl_fd("sb", 1);
	return (0);
}

int	ss(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	swap(stack_a);
	swap(stack_b);
	if (bench)
		bench_ss(bench);
	ft_putendl_fd("ss", 1);
	return (0);
}
