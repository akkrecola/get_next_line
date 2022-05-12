/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:22:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/12 15:14:22 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd_file;
	int		fd_output;
	char	*line;
	char	*file;
	ssize_t	ret;
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

	file = argv[1];
	fd_file = open(file, O_RDONLY);
	fd_output = open("output", O_RDWR | O_TRUNC | O_CREAT, 0666);

	line = NULL;
	ret = 1;
	i = 0;
	while (ret > 0 && (lines == 0 || i < lines))
	{
		ret = get_next_line(fd_file, &line);
		if (ret > 0)
			ft_putendl_fd(line, fd_output);
		/* If 1 returns are needed, uncomment below */
//		if (ret == 1)
//			ft_putendl("^ Returned 1.");
		/* End uncomment */
		free(line);
		i++;
	}
	if (ret == 0)
		ft_putendl(">>>>> Reading was completed (GNL exited with 0).");
	if (ret == 1 && i == lines)
	{
		ft_putstr(">>>>> Reading was completed.\n>>>>> Read lines: ");
		ft_putnbr((int) i);
		ft_putendl("");
	}
	if (ret == -1)
		ft_putendl(">>>>> Error was produced (GNL exited with -1).");

	close(fd_file);
	close(fd_output);
	return (0);
}
