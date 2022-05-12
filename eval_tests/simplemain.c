/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplemain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:10:08 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/11 13:17:01 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	if (argc != 2)
	{
		printf("Usage: Enter a file with path to read a single line from.");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	printf("Read line:\n%s\n", line);
	free(line);

	return (0);
}
