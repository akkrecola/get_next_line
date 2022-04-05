/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/04/05 11:02:21 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	update_cache(char **cache, char *buf, char **newline)
{
	*newline = ft_strsep(cache, '\n');
	if (!*cache)
		*cache = ft_strdup(buf);
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
static int	get_cache()
{
	*newline = ft_strsep(cache, '\n');
	if (*newline)
		return (join(line, cache, newline));
	else
	{
		
	}
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	static char	*cache[MAX_FD];

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
		if (update_cache(cache, buf, newline) == -1)
			return (-1);
		if (join(line, cache, newline) == -1)
			return (-1);
	}
	return (1);
}
