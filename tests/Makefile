# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 03:24:01 by elehtora          #+#    #+#              #
#    Updated: 2022/02/25 03:34:37 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= a.out

SRCS	= get_next_line.c tests/main.c
OBJS	= $(SRCS:.c=.o)

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -Wconversion

RM		= /bin/rm -f

# RECIPES #

all :
	$(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
