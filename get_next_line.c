/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:03:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/03 15:15:32 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * NOTES:
 * >> Cache is always initialized for an open fildes, and zeroed whenever
 * there's no contents to it.
 * >> ft_strnew() always zeroes the initialized memory.
 * >> Operations are done assuming there's no literal 0's in the read lines.
 * >> ft_strsep() replaces newline character with a 0 and returns a pointer
 * to the following character, so there's TWO actions to it.
 * >> Calls to cache() and join() come from two different states, i.e. 2. when
 * 'popping' the cache and 2. when iterating a line with the buffer.
 *
 * 1. Check if variables have been initialized for given fildes (if cache[fd]
 * exists)
 * >> A. if not
 * 2. Check if there's content in stash
 * >> if TRUE, attempt to join (pop)
 * >> >> A. if a newline is found, exit gnl() with 1
 * >> >> B. if a newline is NOT found, clear
 * >> else
 *
 */

/*
 * Create a line as the strjoin() base if none exists
 * Allocate buffer if this is the first call to this fildes
 */
//TODO
/*
 * stash() stores the rest of a buffer ready for a new call to get_next_line().
 * The stashing is made in a non-destructive way, i.e. a temporary buffer is
 * used to parse the buffer.
 *
 * A cache is used so that there's no conflicts between buffer size changes and
 * overwrites. A separate cache also makes the code easier to read.
 */
/*
   join() should not care about the state of cache and which input it gets as
   the string, since we use it for 1. the cache and 2. the read buffer at
   different stages.
*/

/*
 * join() joins a string in buf (1) to the line stored in line (2). It stores
 * either the entire buffer, or until there's a newline character signifying
 * the end of the line.
 *
 * It does so by searching for a newline character in buf, and storing it in the
 * 'booleanish' variable newline (3). If a '\n' is found, the line is complete
 * and the caller function get_next_line() returns with 1.
 *
 * join() returns 1, 0 or -1, if a newline has been found, if it was not found,
 * or if an error has occured, respectively.
 */
static ssize_t	init(char **line, char *buf, char **newline)
{
	if (*line)
		free(*line);
	*line = ft_strnew(0);
	if (!*line)
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	*newline = NULL;
	// TODO
	return (0);
}

/*
* BUG? Case where '\n' refers to the last character in a file, and the
* resulting pointer from ft_strsep would overflow the file buffer
*/
static ssize_t	join(char **line, char *str, char **newline)
{
	char	*temp;

	*newline = ft_strsep(&str, '\n');
	temp = *line;
	*line = ft_strjoin(*line, str);
	free(temp);
	if (!*line)
		return (-1);
	return (0);
}

// Since buf is always null-terminated, cache is as well; hence strdup in stash()
// doesn't overflow.
//TODO cache states (non-init OR need to clear)
static ssize_t	stash(char **cache, char **newline) //newline can refer to either the cache (pop) or buffer (iteration)
{
	char	*temp;

	temp = ft_strdup(*newline);
	if (*cache)
		free(*cache);
	*cache = temp;
	if (!*cache)
		return (-1);
	return (1);
}

static ssize_t	pop(char **line, char **cache, char **newline)
{
	if (*cache)
	{
		if (join(line, *cache, newline))
			return (-1);
		if (*newline)
			return (stash(cache, newline)); //
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;

	if (fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	if (init(line, &buf[0], &newline)) // check buffer deref syntax
		return (-1);
	ret = pop(line, &cache[fd], &newline); //
	if (ret)
		return ((int) ret);
	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, BUFF_SIZE); //
		if (join(line, buf, &newline)) //
			return (-1);
		if (newline && ret)
			return ((int) stash(&cache[fd], &newline)); //
	}
	if (ret == 0 && *cache)
		free(cache);
	return (0);
}
