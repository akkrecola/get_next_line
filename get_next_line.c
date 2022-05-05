/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:03:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/05 17:42:46 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;
	char		*tmp;

	if (fd < 0 || !line || fd > MAX_FD)
		return (-1);
	if (*line)
		free(*line);
	*line = ft_strnew(0);
	if (cache[fd])
	{
		newline = ft_strsep(&cache[fd], '\n');
		*line = ft_strjoin(*line, cache[fd]);
		if (newline)
		{
			tmp = cache[fd];
			if (!(cache[fd] = ft_strdup(newline)))
				return (-1);
			free(tmp);
			return (1);
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = 0;
		cache[fd] = ft_strdup(&buf[0]);
		newline = ft_strsep(&cache[fd], '\n');
		*line = ft_strjoin(*line, cache[fd]);
		if (newline)
		{
			tmp = cache[fd];
			if (!(cache[fd] = ft_strdup(newline)))
				return (-1);
			free(tmp);
			return (1);
		}
	}
	free(cache[fd]);
	if (**line)
		return (1);
	return (0);
}
