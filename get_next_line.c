/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/04/06 15:06:51 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	update_cache(char **cache, char **buf, char **newline)
{
	if (!*newline)
		*cache = ft_strdup(*buf);
	*newline = ft_strsep(cache, '\n');
	if (!*cache)
		return (-1);
	return (0);
}

static int	join(char **line, char **cache, char **newline)
{
	*line = ft_strjoin(*line, *cache);
	if (!*line)
		return (-1);
	if (*newline)
		*cache = *newline;
	return (0);
}

/* retrieve cache content to line between calls */
static int	get_cache(char **line, char **cache, char **newline)
{
	if (*cache)
	{
		*newline = ft_strsep(cache, '\n');
		if (*newline)
			return (join(line, cache, newline));
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	static char	*cache[MAX_FD];

	if (*line)
		free(line);
	*line = ft_strnew(0);
	ret = get_cache();
	if (ret != 0)
		return (ret);
	while (!newline)
	{
		ft_memset(buf, '\0', BUFF_SIZE + 1);
		ret = read(fd, buf, BUFF_SIZE);
		if (ret < 1)
			return (ret);
		buf[ret] = '\0';
		if (update_cache(cache, &buf, newline) == -1)
			return (-1);
		if (join(line, cache, newline) == -1)
			return (-1);
	}
	return (1);
}
