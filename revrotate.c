/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revrotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:07:16 by faharila          #+#    #+#             */
/*   Updated: 2026/04/23 14:07:17 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "bench.h"

int	reverserotate(t_list **stack)
{
	t_list	*head;
	t_list	*tail;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	tail = ft_lstlast(head);
	while (head)
	{
		if (head->next->next == NULL)
		{
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
	tail->next = *stack;
	*stack = tail;
	return (0);
}

int	rra(t_list **stack_a, t_bench *bench)
{
	if (reverserotate(stack_a) == -1)
		return (-1);
	if (bench)
		bench_rra(bench);
	ft_putendl_fd("rra", 1);
	return (0);
}

int	rrb(t_list **stack_b, t_bench *bench)
{
	if (reverserotate(stack_b) == -1)
		return (-1);
	if (bench)
		bench_rrb(bench);
	ft_putendl_fd("rrb", 1);
	return (0);
}

int	rrr(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	reverserotate(stack_a);
	reverserotate(stack_b);
	if (bench)
		bench_rrr(bench);
	ft_putendl_fd("rrr", 1);
	return (0);
}
