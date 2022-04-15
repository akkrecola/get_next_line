/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:03:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/04/16 00:02:06 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init(char **line, char **cache, char **buf, char **newline)
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
	//TODO: stashing when called before read() block
	if (*newline)
	{
		ft_strclr(*cache);
		*cache = ft_strdup(*newline);
	}
	//TODO: return values to indicate states and proper returns from gnl()
}

/*
   join() should not care about the state of cache and which input it gets as
   the string, since we use it for 1. the cache and 2. the read buffer at
   different stages.
*/
static int	join(char **buf, char **line, char **newline, char **cache)
{
	while (!*newline && ft_strlen(*buf) > 0)
	{
		*newline = ft_strsep(buf, '\n');
		*line = ft_strjoin(*line, *buf); //infinite join?
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
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	static char	*cache[MAX_FD];

	if (init(line, &(cache[fd]), buf, &newline)) //initialize variables and prepare function
		return (-1);
	ret = join(&(cache[fd]), line, &newline, &(cache[fd])); // iterate through cache if there's one
	if (ret)
		return (ret);
	while (!newline && ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret > 0)
		{
			if (join(buf, line, &newline, &(cache[fd])) == -1)
				return (-1);
		}
	}
	if (ret <= 0 && (cache && cache[fd]))
		free(*cache);
	return (ret);
}
