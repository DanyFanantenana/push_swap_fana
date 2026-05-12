/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:30:00 by faharila          #+#    #+#             */
/*   Updated: 2026/05/11 08:37:50 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sqrt(int nb)
{
	int	i;

	i = 1;
	while (i <= nb / i)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}

static int	get_chunk_size(int size)
{
	int	chunk;

	chunk = (int)ft_sqrt(size);
	if (chunk < 1)
		chunk = 1;
	return (chunk);
}

static void	push_chunk_to_b(t_list **stack_a, t_list **stack_b,
		int *chunk, t_bench *bench)
{
	int	size;
	int	j;

	size = ft_lstsize(*stack_a);
	j = 0;
	while (j < size)
	{
		if ((*stack_a)->index >= chunk[0]
			&& (*stack_a)->index <= chunk[1])
			pb(stack_a, stack_b, bench);
		else
			ra(stack_a, bench);
		j++;
	}
}

static int	find_max_pos(t_list *stack_b)
{
	int	max;
	int	pos;
	int	i;

	max = -1;
	pos = 0;
	i = 0;
	while (stack_b)
	{
		if (stack_b->index > max)
		{
			max = stack_b->index;
			pos = i;
		}
		stack_b = stack_b->next;
		i++;
	}
	return (pos);
}

static void	move_max_to_top(t_list **stack_b, int pos, int size,
	t_bench *bench)
{
	int	j;

	j = 0;
	if (pos <= size / 2)
	{
		while (j < pos)
		{
			rb(stack_b, bench);
			j++;
		}
	}
	else
	{
		while (j < size - pos)
		{
			rrb(stack_b, bench);
			j++;
		}
	}
}

static void	push_back_sorted(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	int	size;
	int	pos;

	while (ft_lstsize(*stack_b) > 0)
	{
		size = ft_lstsize(*stack_b);
		pos = find_max_pos(*stack_b);
		move_max_to_top(stack_b, pos, size, bench);
		pa(stack_a, stack_b, bench);
	}
}

void	medium_sort(t_list **stack_a, t_list **stack_b, t_bench *bench)
{
	int	size;
	int	chunk_size;
	int	i;
	int	chunk[2];

	size = ft_lstsize(*stack_a);
	chunk_size = get_chunk_size(size);
	i = 0;
	while (i < size)
	{
		chunk[0] = i;
		if (i + chunk_size < size)
			chunk[1] = i + chunk_size - 1;
		else
			chunk[1] = size - 1;
		push_chunk_to_b(stack_a, stack_b, chunk, bench);
		i += chunk_size;
	}
	push_back_sorted(stack_a, stack_b, bench);
}
