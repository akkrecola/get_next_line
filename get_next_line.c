/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/03/23 13:10:54 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_cache(char **cache, char **newline, char **line)
{
	*newline = NULL;
	if (*cache)
	{
		*newline = ft_strsep(*cache, '\n');
		if (*newline)
		{
			*line = ft_strdup(*cache);
			ft_strcpy(*cache, *newline);
		}
		else
		{
			*line = ft_strdup(*cache);
			ft_strclr(*cache);
		}
	}
	else
		*line = ft_strnew(0); //creates empty string
	if (!(*line))
		return (-1);
	return (0);
}

static int	update_cache()
{
	/* TODO Check operation order */
	*newline = ft_strsep(*cache); // Check if newline in cache
	if (!*cache) // Cache had leftover content from previous call to gnl()
		return (2); //return recall identifier for join()
	/*
	 * TODO Add cases for 1. no newline (cache emptied) 
	 * 2. newline found (cache left with residue) 
	 */
}

/*
 * If there's something in cache after the join operation, it means there's
 * been a new line. The condition for the join can hence be checked by checking
 * the state of *cache.
 */

static int	join(char **line, char **cache, char **newline)
{
	short	op;

	op = update_cache();
	if (op == 2) // Cache was not empty (buffer residue from previous call)
	{
		// join residue
	}
	else if (op == 1) //cache contained newline
	{
		// join the first substring with *line
		// leave rest in cache (starting at *newline)
	}
	else // no newline in cache
	{
		// join the entire cache to *line
		// clear cache
	}
}


int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1]; 	//to have size for string operations
	static char	*cache[MAX_FD];			//string array to fit tmp caches for new lines
	int			ret;	//ssize_t defined in stddef.h, so not included
	char	*newline;

	if (!(*line))
		*line = ft_strnew(0);
	if (!get_cache())
		return (-1);
	while (ret && !newline)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!update_cache())
			return (-1);
		if (!join())
			return (-1);
	}
	return (0);
}
