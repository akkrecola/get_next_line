/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:22:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/04 17:57:52 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*line;
	char	*file;
	int		fd;
	ssize_t	ret;

	if (argc != 4)
		return -1;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);

		ft_putendl(line);
		ret = get_next_line(fd, &line);

	free(line);
	close(fd);
	return 0;
}
