/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:22:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/06 14:56:14 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*line;
	int		fd;
	ssize_t	ret;
	char	*file;

	if (argc != 2)
		return -1;
	file = argv[1];
	fd = open(file, O_RDONLY);

	ret = 1;
	while (ret)
	{
		ft_putendl(line);
		ret = get_next_line(fd, &line);
//		if (ret == 1)
//			ft_putendl("GNL read a line. (returned 1");
	}
	if (ret == -1)
		ft_putendl("\n***\nError was produced. (returned -1)");
	if (ret == 0)
		ft_putendl("\n***\nReading was completed (GNL exited with 0).");

	close(fd);
	return 0;
}