/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:50:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/13 14:27:35 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Description:
   get_next_line() reads a file from a file descriptor one line (separated by
   a newline '\n') at a time. The read line is saved to the variable line
   which is passed to the function by reference. (See README for more).

Usage:
   Declare a string to pass as **line to the function, and free(line) after
   every call to get_next_line() to prevent leaks.

Parameters:
   The function takes as parameters an open file descriptor fd, and a pointer
   to a string that's used to save the line read from file descriptor fd.

Return:
   get_next_line() returns 1 on succesfully read line, -1 on error, and 0 when
   a file has finished reading (EOF).
*/

/*
 * Pop() checks if there's cached buffer in store, and if found, makes that
 * into the beginning of the resulting line. If a newline is found in the cache,
 * that \n is turned in to a terminator \0 and a pointer to the next line (char
 * after the new \0) is saved to 'newline'. If no newline is found, cache is
 * cleared and 'line' is allocated an empty string as a base.
 */
static ssize_t	pop(char **cache, char **line, char **newline)
{
	*newline = NULL;
	if (*cache)
	{
		*newline = ft_strsep(cache, '\n');
		*line = ft_strdup(*cache);
		if (*newline)
			ft_strcpy(*cache, *newline);
		else
			ft_strclr(*cache);
		if (*line == NULL)
			return (0);
	}
	else
		*line = ft_strnew(0);
	return (1);
}

/*
 * Stash() seeks a newline in buffer, and if found, sets that newline \n to \0,
 * and saves everything after that newline to cache.
 */
static ssize_t	stash(char **cache, char *buf, char **newline)
{
	char	*tmp;

	*newline = ft_strsep(&buf, '\n');
	if (*newline)
	{
		tmp = *cache;
		*cache = ft_strdup(*newline);
		free(tmp);
		if (!*cache)
			return (0);
	}
	return (1);
}

/*
 * Join() simply joins a string (previously formed with strsep() in stash()) to
 * the result variable 'line'.
 */
static ssize_t	join(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	if (!*line)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;

	if (fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	ret = pop(&cache[fd], line, &newline);
	if (!ret)
		return (-1);
	while (ret && !newline)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(stash(&cache[fd], buf, &newline)))
			return (-1);
		if (!(join(line, buf)))
			return (-1);
	}
	if (ret || **line)
		return (1);
	free(cache[fd]);
	return (0);
}
