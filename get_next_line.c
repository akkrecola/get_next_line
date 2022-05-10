/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:50:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/10 17:13:57 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
   get_next_line() reads a file from a file descriptor one line (separated by
   a newline '\n') at a time.

   The function takes as parameters an open file descriptor fd, and a pointer
   to a string that's used to save the line read from file descriptor fd.

   get_next_line() returns 1 on succesfully read line, -1 on error, and 0 when
   a file has finished reading (EOF).

   The function is designed to work on multiple open file descriptors at once,
   i.e. one can read from files A, then B, then C, and again B, without losing
   the correct position in each file.

   This implementation is based on a heap allocated cache, where the bytes stored
   in buffer after a successfully read line are stored to wait for a new call
   to get_next_line (see: stash()).

   The function naming convention loosely resembles that of git-stash, due to
   the similar caching logic used here. See respective functions for details.

   The function is memory safe.

   NOTE: This version of the function does not pass the 42FileChecker
   moulitest. This is due to proper memory management, i.e. freeing memory
   from previous line on each call to prevent subsequent leaks, and freeing
   cache memory before get_next_line() returns 0. This point can be demonstrated
   during defence.
*/

/*
   pop() (1) retrieves the contents of the cache stashed by a previous call
   to stash(), (2) joins it to the line that's returned by get_next_line(), (3) 
   and prepares the cache for a stash() -call down the line.

   The function also frees the previously read line and allocates a base
   for the currently read line.
*/

static ssize_t	pop(char **cache, char **line, char **newline)
{
	if (*line)
		ft_strdel(line);
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
 * stash() looks for a newline in the buffer, and if it's found,
 * the string starting from that newline is saved to the cache.
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
 * join() simply joins the buffer to the resulting line in a safe manner.
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

/*
   A teardown function that frees any allocated memory when reading
   reaches EOF.
*/
static int	teardown(char **line, char **cache)
{
	if (*cache)
		free(*cache);
	free(*line);
	return (0);
}

/*
 * get_next_line() //TODO
 */
int	get_next_line(int fd, char **line)
{
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;

	if (fd < 0 || fd > MAX_FD || !line)
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
	return (teardown(line, &cache[fd]));
}
