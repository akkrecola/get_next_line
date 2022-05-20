/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:50:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/20 16:27:29 by elehtora         ###   ########.fr       */
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
static ssize_t	pop(char *buf, char **line, char **newline)
{
	*newline = NULL;
	*newline = ft_strsep(&buf, '\n');
	*line = ft_strdup(buf);
	if (*newline)
	{
		ft_strcpy(buf, *newline);
		*newline = buf;
	}
	else
		ft_strclr(buf);
	if (*line == NULL)
		return (0);
	return (1);
}

/*
 * Stash() seeks a newline in buffer, and if found, sets that newline \n to \0,
 * and saves everything after that newline to cache.
 */
static ssize_t	stash(char *buf, char **newline)
{
	if (*newline)
	{
		ft_strcpy(buf, *newline);
		*newline = buf;
	}
	else
		ft_bzero(buf, BUFF_SIZE);
	return (1);
}

/*
 * Join() simply joins a string (previously formed with strsep() in stash()) to
 * the result variable 'line'.
 */
static ssize_t	join(char **line, char *buf, char **newline)
{
	char	*tmp;

	*newline = ft_strsep(&buf, '\n');
	tmp = *line;
	*line = ft_strjoin(*line, buf);
	ft_strdel(&tmp);
	if (!*line)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[MAX_FD][BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;

	if (fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	ret = pop(&buf[fd][0], line, &newline);
	if (!ret)
		return (-1);
	while (ret && !newline)
	{
		ret = read(fd, buf[fd], BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[fd][ret] = '\0';
		if (!(join(line, &buf[fd][0], &newline)))
			return (-1);
	}
	if (!(stash(&buf[fd][0], &newline)))
		return (-1);
	if (ret || **line)
		return (1);
	return (0);
}
