# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 03:24:01 by elehtora          #+#    #+#              #
#    Updated: 2022/05/04 17:44:32 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl.out

SRCS		= ../get_next_line.c main.c
OBJS		= $(SRCS:.c=.o)
LIB			= -lft

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Wconversion
DEBUG		= -g

INCL		= -I..
LIBPATH		= -L../libft

RM			= /bin/rm -rf

# RECIPES #

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

debug : $(SRCS)
	$(CC) $(DEBUG) $(SRCS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)


clean :
	$(RM) $(OBJS) $(NAME).dSYM

fclean : clean
	$(RM) $(NAME)

re : fclean all
