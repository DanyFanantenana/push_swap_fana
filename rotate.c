/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:07:16 by faharila          #+#    #+#             */
/*   Updated: 2026/04/23 15:37:29 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

int	rotate(t_list **stack)
{
	t_list	*head;
	t_list	*tail;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	tail = ft_lstlast(head);
	*stack = head->next;
	head->next = NULL;
	tail->next = head;
	return (0);
}

int	ra(t_list **stack_a, t_bench *bench)
{
	if (rotate(stack_a) == -1)
		return (-1);
	if (bench)
		bench_ra(bench);
	ft_putendl_fd("ra", 1);
	return (0);
}

int	rb(t_list **stack_b, t_bench *bench)
{
	if (rotate(stack_b) == -1)
		return (-1);
	if (bench)
		bench_rb(bench);
	ft_putendl_fd("rb", 1);
	return (0);
}

int	rr(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	rotate(stack_a);
	rotate(stack_b);
	if (bench)
		bench_rr(bench);
	ft_putendl_fd("rr", 1);
	return (0);
}
