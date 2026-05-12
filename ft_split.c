/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:36:14 by ainarako          #+#    #+#             */
/*   Updated: 2026/04/24 01:36:14 by ainarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	word_length(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	fill_word(char **result, char const *s, int w_len)
{
	int	j;

	j = 0;
	while (j < w_len)
	{
		result[0][j] = s[j];
		j++;
	}
	result[0][j] = '\0';
}

char	**f(char const *s, char c, char **result, int words_count)
{
	int	i;
	int	w_len;

	while (*s == c)
		s++;
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		w_len = word_length(s, c);
		result[i] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!(result[i]))
			return (NULL);
		fill_word(&result[i], s, w_len);
		s += w_len;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!(result))
		return (NULL);
	result = f(s, c, result, wcount);
	result[wcount] = NULL;
	return (result);
}
