/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:22:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/04 17:47:21 by elehtora         ###   ########.fr       */
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
//	int		i;

	if (argc != 2)
		return -1;
	file = argv[1];
	fd = open(file, O_RDONLY);

//	i = 0;
	while (ret)
	{
		ft_putendl(line);
		ret = get_next_line(fd, &line);
	}

	free(line);
	close(fd);
	return 0;
}
