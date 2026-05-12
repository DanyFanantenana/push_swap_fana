/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 07:16:49 by faharila          #+#    #+#             */
/*   Updated: 2026/04/22 07:16:49 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min(t_list **stack, int val)
{
	t_list	*head;
	int		min;

	head = *stack;
	min = head->index;
	while (head->next)
	{
		head = head->next;
		if ((head->index < min) && head->index != val)
			min = head->index;
	}
	return (min);
}

static void	finish_sort_3(t_list **stack_a, t_list *head, int min,
	t_bench *bench)
{
	if (head->next->index == min)
		ra(stack_a, bench);
	else
	{
		sa(stack_a, bench);
		rra(stack_a, bench);
	}
}

static void	handle_sort_3_cases(t_list **stack_a, t_list *head,
	t_bench *bench)
{
	int	min;
	int	next_min;

	min = get_min(stack_a, -1);
	next_min = get_min(stack_a, min);
	if (head->index == min && head->next->index != next_min)
	{
		ra(stack_a, bench);
		sa(stack_a, bench);
		rra(stack_a, bench);
	}
	else if (head->index == next_min)
	{
		if (head->next->index == min)
			sa(stack_a, bench);
		else
			rra(stack_a, bench);
	}
	else
		finish_sort_3(stack_a, head, min, bench);
}

void	sort_3(t_list **stack_a, t_bench *bench)
{
	t_list	*head;

	if (is_sorted(stack_a))
		return ;
	head = *stack_a;
	handle_sort_3_cases(stack_a, head, bench);
}

void	sort_4(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	int	distance;

	if (is_sorted(stack_a))
		return ;
	distance = get_distance(stack_a, get_min(stack_a, -1));
	if (distance == 1)
		ra(stack_a, bench);
	else if (distance == 2)
	{
		ra(stack_a, bench);
		ra(stack_a, bench);
	}
	else if (distance == 3)
		rra(stack_a, bench);
	if (is_sorted(stack_a))
		return ;
	pb(stack_a, stack_b, bench);
	sort_3(stack_a, bench);
	pa(stack_a, stack_b, bench);
}

void	sort_5(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	int	distance;

	distance = get_distance(stack_a, get_min(stack_a, -1));
	if (distance == 1)
		ra(stack_a, bench);
	else if (distance == 2)
	{
		ra(stack_a, bench);
		ra(stack_a, bench);
	}
	else if (distance == 3)
	{
		rra(stack_a, bench);
		rra(stack_a, bench);
	}
	else if (distance == 4)
		rra(stack_a, bench);
	if (is_sorted(stack_a))
		return ;
	pb(stack_a, stack_b, bench);
	sort_4(stack_a, stack_b, bench);
	pa(stack_a, stack_b, bench);
}
