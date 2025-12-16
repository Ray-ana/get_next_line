/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:58:25 by rzimaeva          #+#    #+#             */
/*   Updated: 2025/12/16 19:12:27 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (new_str);
}

static char	*fill_stash(char **stash, int fd)
{
	char	*buffer;
	int		bytes_read;

	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(*stash), *stash = NULL, NULL);
	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(*stash), *stash = NULL, NULL);
		buffer[bytes_read] = '\0';
		*stash = ft_strjoin_and_free(*stash, buffer);
		if (!*stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (*stash);
}

static char	*clean_stash(char *stash)
{
	char	*new_stash;
	char	*newline_pos;
	size_t	len_read;
	size_t	len_to_keep;

	if (!stash || ft_strlen(stash) == 0)
		return (free(stash), NULL);
	newline_pos = ft_strchr(stash, '\n');
	if (!newline_pos)
		return (free(stash), NULL);
	len_read = (newline_pos - stash) + 1;
	len_to_keep = ft_strlen(stash) - len_read;
	if (len_to_keep == 0)
		return (free(stash), NULL);
	new_stash = ft_substr(stash, len_read, len_to_keep);
	free(stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

static char	*get_line(char *stash)
{
	char	*line;
	char	*new_pos;
	size_t	len_line;

	if (!stash || ft_strlen(stash) == 0)
	{
		free(stash);
		return (NULL);
	}
	new_pos = ft_strchr(stash, '\n');
	if (new_pos)
	{
		len_line = (new_pos - stash) + 1;
	}
	else
	{
		len_line = ft_strlen(stash);
	}
	line = ft_substr(stash, 0, len_line);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!fill_stash(&stash[fd], fd))
		return (NULL);
	if (!stash[fd] || ft_strlen(stash[fd]) == 0)
	{
		if (stash[fd])
			free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = get_line(stash[fd]);
	if (!line)
	{
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
