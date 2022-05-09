/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:50:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/09 14:23:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	teardown(char **line, char **cache)
{
	if (*cache)
		free(*cache);
	free(*line);
	return (0);
}

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
