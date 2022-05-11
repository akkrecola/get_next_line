/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:22:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:47 by elehtora         ###   ########.fr       */
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
	size_t	lines;
	size_t	i;

	if (argc != 2 && argc != 3)
	{
		ft_putendl("Usage: 1. enter the file to be read through, (2. number of lines to read (leave blank to read entirely)).");
		return (-1);
	}
	if (argc == 3)
		lines = (size_t) ft_atoi(argv[2]);
	else
		lines = 0;

	if (*argv[1] == '0')
		fd = 0;
	else
	{
		file = argv[1];
		fd = open(file, O_RDONLY);
	}

	line = NULL;
	ret = 1;
	i = 0;
	while (ret > 0 && (lines == 0 || i < lines))
	{
		ret = get_next_line(fd, &line);
		if (ret > 0)
			ft_putendl(line);
		if (line)
			free(line);
		i++;
	}
	if (ret == -1)
		ft_putendl("\n***\n\nError was produced. (returned -1)");
	if (ret == 0)
		ft_putendl("\n***\nReading was completed (GNL exited with 0).");
	close(fd);
	return (0);
}
