/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:38:49 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:38:49 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "push_swap.h"

static void	trim_command(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	execute_command(char *line, t_list **stack_a, t_list **stack_b)
{
	if (!ft_strcmp(line, "sa"))
		return (swap(stack_a), 0);
	if (!ft_strcmp(line, "sb"))
		return (swap(stack_b), 0);
	if (!ft_strcmp(line, "ss"))
		return (swap(stack_a), swap(stack_b), 0);
	if (!ft_strcmp(line, "pa"))
		return (push(stack_a, stack_b), 0);
	if (!ft_strcmp(line, "pb"))
		return (push(stack_b, stack_a), 0);
	if (!ft_strcmp(line, "ra"))
		return (rotate(stack_a), 0);
	if (!ft_strcmp(line, "rb"))
		return (rotate(stack_b), 0);
	if (!ft_strcmp(line, "rr"))
		return (rotate(stack_a), rotate(stack_b), 0);
	if (!ft_strcmp(line, "rra"))
		return (reverserotate(stack_a), 0);
	if (!ft_strcmp(line, "rrb"))
		return (reverserotate(stack_b), 0);
	if (!ft_strcmp(line, "rrr"))
		return (reverserotate(stack_a), reverserotate(stack_b), 0);
	return (1);
}

int	do_commands(char *line, t_list **stack_a, t_list **stack_b)
{
	trim_command(line);
	return (execute_command(line, stack_a, stack_b));
}

void	print_checker_res(t_list **stack_a, t_list **stack_b)
{
	if (is_sorted(stack_a))
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	if (*stack_a)
		free_stack(stack_a);
	if (*stack_b)
		free_stack(stack_b);
}

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	char	*line;

	if (argc < 2)
		return (0);
	stack_a = (t_list **)malloc(sizeof(t_list *));
	stack_b = (t_list **)malloc(sizeof(t_list *));
	*stack_a = NULL;
	*stack_b = NULL;
	ft_check_args(argc, argv);
	initstack(stack_a, argc, argv);
	line = get_next_line(0);
	while (line)
	{
		if (do_commands(line, stack_a, stack_b))
		{
			ft_error();
			return (-1);
		}
		free(line);
		line = get_next_line(0);
	}
	print_checker_res(stack_a, stack_b);
	return (0);
}
