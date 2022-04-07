/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/04/07 06:02:39 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static int	join(char **line, char **buf, char **newline, const int fd)
{
	while (!newline && ret > 0)
	{
		if (!**buf)
		{
			ret = read(fd, &buf, BUFF_SIZE);
			if (ret < 1)
				return (ret);
		}
		*newline = ft_strsep(buf, '\n');
		*line = ft_strjoin(*line, *buf);
		if (!*line)
			return (-1);
		if (!*newline)
			ft_memset(*buf, '\0', (BUFF_SIZE + 1));
	} //add proper returns
}
*/
/*
// init cache if doesn't exist
static int	pop(char **line, char **buf, char **cache, char **newline)
{
	if (!*cache && !**cache)
	{
		*cache = ft_strnew(BUFF_SIZE);
		if (!*cache)
			return (-1);
	}
	else
	{
		ft_memcpy(*buf, *cache, BUFF_SIZE + 1);
		join();
	}
}
*/

/*
// if EOF, free cache
static int	stash(char **cache, char **buf, char **newline)
{
	free(*cache);
	*cache = ft_strdup(*newline);
}
*/

char	*ft_strsep_arr(char *p_string[], int c)
{
	char	*latter;

	if (!p_string || !*p_string || !ft_isascii(c))
		return (NULL);
	latter = ft_strchr(*p_string, c);
	if (!latter)
		return (NULL);
	else
	{
		*latter = '\0';
		latter++;
	}
	return (latter);
}

/*
   1. Retrieve cache (pop/dig)
   2. Join until newline found OR ret == 0 (join)
   3. Fill cache if newline found (stash)
*/
int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf;
	char		*newline;
	static char	*cache[MAX_FD];

	if (*line)
		free(line);
	*line = ft_strnew(0);
	buf = ft_strnew(BUFF_SIZE);
	if (cache[fd]) //checks what exactly?
		ft_memcpy(buf, *cache, BUFF_SIZE + 1); //pop cache
	ft_memset(buf, '\0', BUFF_SIZE + 1);
	while (!newline && ret > 0)
	{
		if (!*buf)
		{
			ret = read(fd, &buf, BUFF_SIZE);
			if (ret < 1)
			{
				free(*line);
				return (ret);
			}
		}
		newline = ft_strsep_arr(&buf, '\n');
		*line = ft_strjoin(*line, buf);
		if (!*line)
			return (-1);
		if (!newline)
			ft_memset(buf, '\0', (BUFF_SIZE + 1));
	}
	free(cache[fd]);
	cache[fd] = ft_strdup(newline); //stash cache
	return (1);
}
