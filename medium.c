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
		int chunk_min, int chunk_max)
{
	int	size;
	int	j;

	size = ft_lstsize(*stack_a);
	j = 0;
	while (j < size)
	{
		if ((*stack_a)->index >= chunk_min
			&& (*stack_a)->index <= chunk_max)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
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

static void	push_back_sorted(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int	pos;
	int	j;

	while (ft_lstsize(*stack_b) > 0)
	{
		size = ft_lstsize(*stack_b);
		pos = find_max_pos(*stack_b);
		if (pos <= size / 2)
		{
			j = 0;
			while (j < pos)
			{
				rb(stack_b);
				j++;
			}
		}
		else
		{
			j = 0;
			while (j < size - pos)
			{
				rrb(stack_b);
				j++;
			}
		}
		pa(stack_a, stack_b);
	}
}

void	medium_sort(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int	chunk_size;
	int	i;
	int	chunk_min;
	int	chunk_max;

	size = ft_lstsize(*stack_a);
	chunk_size = get_chunk_size(size);
	i = 0;
	while (i < size)
	{
		chunk_min = i;
		if (i + chunk_size < size)
			chunk_max = i + chunk_size - 1;
		else
			chunk_max = size - 1;
		push_chunk_to_b(stack_a, stack_b, chunk_min, chunk_max);
		i += chunk_size;
	}
	push_back_sorted(stack_a, stack_b);
}
