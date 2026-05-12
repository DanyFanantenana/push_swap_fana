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
	if (!num[0])
		return (0);
	if (num[0] == '-')
		i++;
	if (!num[i])
		return (0);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	validate_arg(char *arg, char **args, int index)
{
	long	tmp;

	tmp = ft_atoi(arg);
	if (!ft_isnum(arg) || ft_contains(tmp, args, index)
		|| tmp < -2147483648 || tmp > 2147483647)
	{
		ft_free(args);
		ft_error();
	}
}

static int	has_empty_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i][0])
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_args(int argc, char **argv)
{
	int		i;
	char	**args;

	if (has_empty_arg(argc, argv))
		ft_error();
	args = get_args(argc, argv);
	if (!args || !args[0])
	{
		if (args)
			ft_free(args);
		ft_error();
	}
	i = 0;
	while (args[i])
	{
		validate_arg(args[i], args, i);
		i++;
	}
	ft_free(args);
}
