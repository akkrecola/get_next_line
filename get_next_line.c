/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:03:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/06 15:04:58 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ft_strjoin_memsafe() concatenates heap allocated (!) strings s1 and s2 into
   a string that is returned by the function.

   The use of the function is to ensure that previously allocated memory is
   properly freed without useless boilerplate in implementations. This comes in
   use when concatenating repeatedly.

   The joining is done through a temporary pointer, so that the allocated area
   is not lost.

   The function returns a pointer to the new heap allocated string.
*/
/*
char	*ft_strjoin_heapsafe(char const *s1, char const *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	ft_strdel(tmp);
	return (s1);
}
*/

static int	free_on_error(char **cache)
{
	if (*cache)
		ft_strdel(cache);
	return (-1);
}

static ssize_t	join(char **line, char **cache, char **newline)
{
	char	*tmp;

	*newline = ft_strsep(cache, '\n');
	tmp = *line;
	if (!(*line = ft_strjoin(tmp, *cache)))
		return (free_on_error(cache));
	ft_strdel(&tmp);
	if (*newline)
	{
		tmp = *cache;
		if (!(*cache = ft_strdup(*newline))) // no alloc protection
			return (free_on_error(cache));
		ft_strdel(&tmp);
		return (1);
	}
	else
		ft_strdel(cache);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;
	ssize_t		ret;

	if (fd < 0 || !line || fd > MAX_FD)
		return (free_on_error(&cache[fd]));
	if (*line)
		ft_strdel(line);
	if (!(*line = ft_strnew(0)))
		return (free_on_error(&cache[fd]));
	if (cache[fd]) //pop
	{
		if ((ret = join(line, &cache[fd], &newline))) //join
			return ((int) ret);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (free_on_error(&cache[fd]));
		buf[ret] = 0;
		if (!(cache[fd] = ft_strdup(&buf[0])))
			return (free_on_error(&cache[fd]));
		if ((ret = join(line, &cache[fd], &newline))) //join
			return ((int) ret);
	}
	if (**line)
		return (1);
	ft_strdel(line);
	return (0);
}
