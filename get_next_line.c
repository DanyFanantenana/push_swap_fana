/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faharila <faharila@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 07:05:01 by faharila          #+#    #+#             */
/*   Updated: 2026/04/13 14:13:06 by faharila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free(char *tp, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(tp, buffer);
	free(tp);
	return (tmp);
}

char	*readtemp(int fd, char *tp)
{
	char	*buffer;
	int		bytes;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(tp, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(tp), free(buffer), NULL);
		buffer[bytes] = '\0';
		tmp = join_and_free(tp, buffer);
		if (!tmp)
			return (free(buffer), NULL);
		tp = tmp;
	}
	free(buffer);
	return (tp);
}

char	*extract_words(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*free_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
	if (!new_stash)
		return (NULL);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = readtemp(fd, temp);
	if (!temp || temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line = extract_words(temp);
	temp = free_stash(temp);
	return (line);
}
