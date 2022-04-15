/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:03:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/04/12 12:14:19 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init(char **line, char **buf, char **newline)
{
	if (line && *line)
		free(*line);
	*line = ft_strnew(0);
	if (!line || !*line)
		return (-1);
	*newline = NULL;
	ft_bzero(*buf, BUFF_SIZE + 1);
	if (cache && !*cache)
		ft_strnew(BUFF_SIZE);
	if (!cache || !*cache)
		return (-1);
	return (0);
}

/* Might not be needed as join() handles both buffer and cache
static int	pop(char **cache)
{
	
}
*/

//TODO
static int	stash(char **newline, char **cache)
{
	if (cache && *cache)
	{
		ft_strclr(*cache);
		ft_strdup(*cache, *newline);
	}
}

/*
   join() should not care about the state of cache and which input it gets as
   the string, since we use it for 1. the cache and 2. the read buffer at
   different stages.
*/
static int	join(char **buf, char **line, char **newline, char **cache)
{
	while (!*newline)
	{
		*newline = ft_strsep(buf, '\n');
		*line = ft_strjoin(*line, *buf);
		if (!*line)
			return (-1);
	}
	if (stash(newline, cache) == -1)
		return (-1);
	if (*newline)
		return (1);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*newline;
	char	*cache[MAX_FD];

	if (init(line, buf, &newline) || pop() == -1) //initialize variables and prepare function
		return (-1);
	ret = join(cache, line); // iterate through cache if there's one
	if (ret)
		return (ret);
	while (!newline && ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret > 0)
		{
			if (join(buf, line, &newline) == -1)
				return (-1);
		}
	}
	// ft_putendl(*line); //testing
	if (ret == 0 && (cache && *cache))
		free(*cache);
	return (ret);
}
