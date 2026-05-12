/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:38:35 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:38:35 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	joined_len(int argc, char **argv)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (i < argc)
		len += ft_strlen(argv[i++]) + 1;
	return (len);
}

static void	fill_joined(char *joined, int argc, char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			joined[k++] = argv[i][j++];
		joined[k++] = ' ';
		i++;
	}
	joined[k] = '\0';
}

char	**get_args(int argc, char **argv)
{
	char	*joined;
	char	**args;

	joined = malloc(sizeof(char) * (joined_len(argc, argv) + 1));
	if (!joined)
		return (NULL);
	fill_joined(joined, argc, argv);
	args = ft_split(joined, ' ');
	free(joined);
	return (args);
}
