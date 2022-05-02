# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 03:24:01 by elehtora          #+#    #+#              #
#    Updated: 2022/04/17 00:48:26 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl.out

SRCS	= ../get_next_line.c main.c
OBJS	= $(SRCS:.c=.o)

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -Wconversion

RM		= /bin/rm -f

# RECIPES #

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
