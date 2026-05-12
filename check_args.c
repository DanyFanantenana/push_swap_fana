/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:38:35 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:38:35 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_contains(int num, char **argv, int i)
{
	i++;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == num)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	validate_arg(char *arg, char **args, int index, int should_free)
{
	long	tmp;

	tmp = ft_atoi(arg);
	if (!ft_isnum(arg) || ft_contains(tmp, args, index)
		|| tmp < -2147483648 || tmp > 2147483647)
	{
		if (should_free)
			ft_free(args);
		ft_error();
	}
}

static char	**prepare_args(int argc, char **argv, int *start, int *should_free)
{
	if (argc == 2)
	{
		*should_free = 1;
		*start = 0;
		return (ft_split(argv[1], ' '));
	}
	*should_free = 0;
	*start = 1;
	return (argv);
}

void	ft_check_args(int argc, char **argv)
{
	int		i;
	int		should_free;
	char	**args;

	args = prepare_args(argc, argv, &i, &should_free);
	if (should_free && !args[0])
	{
		ft_free(args);
		ft_error();
	}
	while (args[i])
	{
		validate_arg(args[i], args, i, should_free);
		i++;
	}
	if (should_free)
		ft_free(args);
}
