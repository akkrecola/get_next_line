/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:47:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/03/21 19:05:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Include libft from project root, as it's used in the entire project. */
# include "libft.h"

/* System includes for permitted functions. */
# include <stdlib.h>
# include <unistd.h>

/* Definition for read() size. Varied during defence. */
# define BUFF_SIZE 100

/* Function prototype */
int		get_next_line(const int fd, char **line);

#endif
