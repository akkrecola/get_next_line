/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/03/21 19:05:15 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * get_next_line() reads line-by-line the file at file descriptor
 * fd into a buffer.
 */

char	*copy_until_newline();
{
	
}

int	get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE];

	bytes_read = read(fd, buf, BUFF_SIZE);
	if (bytes_read == 0)
		return (0);
	copy_until_newline();
}
