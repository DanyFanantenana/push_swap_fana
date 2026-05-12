/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:02:09 by faharila          #+#    #+#             */
/*   Updated: 2026/04/18 01:02:09 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_bench	t_bench;

typedef struct s_list
{
	int				value;
	int				index;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(int value);
t_list	*ft_lstlast(t_list *head);
void	ft_lstadd_back(t_list **stack, t_list *new);
int		ft_lstsize(t_list *head);

void	ft_error(void);
void	ft_check_args(int argc, char **argv);
char	**get_args(int argc, char **argv);
int		is_sorted(t_list **stack);
int		get_distance(t_list **stack, int index);
void	make_top(t_list **stack, int distance, t_bench *bench);
void	free_stack(t_list **stack);
void	ft_free(char **str);
void	initstack(t_list **stack, int argc, char **argv);

void	radix_sort(t_list **stack_a, t_list **stack_b, t_bench *bench);
void	simple_sort(t_list **stack_a, t_list **stack_b, t_bench *bench);
void	medium_sort(t_list **stack_a, t_list **stack_b, t_bench *bench);
void	ft_adaptive_algo(t_list **stack_a, t_list **stack_b, t_bench *bench);
void	index_stack(t_list **stack);
void	sort_3(t_list **stack_a, t_bench *bench);
void	sort_4(t_list **stack_a, t_list **stack_b, t_bench *bench);
void	sort_5(t_list **stack_a, t_list **stack_b, t_bench *bench);

int		swap(t_list **stack);
int		push(t_list **stack_to, t_list **stack_from);
int		rotate(t_list **stack);
int		reverserotate(t_list **stack);

int		sa(t_list **stack_a, t_bench *bench);
int		sb(t_list **stack_b, t_bench *bench);
int		ss(t_list **stack_a, t_list **stack_b, t_bench *bench);
int		pa(t_list **stack_a, t_list **stack_b, t_bench *bench);
int		pb(t_list **stack_a, t_list **stack_b, t_bench *bench);
int		ra(t_list **stack_a, t_bench *bench);
int		rb(t_list **stack_b, t_bench *bench);
int		rr(t_list **stack_a, t_list **stack_b, t_bench *bench);
int		rra(t_list **stack_a, t_bench *bench);
int		rrb(t_list **stack_b, t_bench *bench);
int		rrr(t_list **stack_a, t_list **stack_b, t_bench *bench);

#endif