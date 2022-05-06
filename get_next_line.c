/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:39:47 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/06 15:45:20 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	update_cache(char **newline, char **cache, char *buf)
{
	char	*tmp;

	*newline = ft_strsep(&buf, '\n');
	if (*newline)
	{
		tmp = *cache;
		*cache = ft_strdup(*newline);
		free(tmp);
		if (*cache == NULL)
			return (0);
	}
	return (1);
}

static int	join(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	if (!*line)
		return (0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	ssize_t		ret;
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;

	if (fd < 0 || !line || fd > MAX_FD)
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
		if (!(update_cache(&newline, &cache[fd], buf)))
			return (-1);
		if (!(join(line, buf)))
			return (-1);
	}
	if (ret || **line)
		return (1);
	free(*line);
	return (0);
}
