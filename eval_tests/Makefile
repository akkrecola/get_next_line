# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 03:24:01 by elehtora          #+#    #+#              #
#    Updated: 2022/05/12 21:12:14 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl.out

SRCS		= ../get_next_line.c main.c
OBJS		= $(SRCS:.c=.o)
LIB			= -lft

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Wconversion
DEBUG		= -g -Wall

INCL		= -I..
LIBPATH		= -L../libft

RM			= /bin/rm -rf

# RECIPES #

all : $(NAME)

$(NAME) : $(OBJS)
	@echo 'Making executable.'
	@$(CC) $(CFLAGS) $(OBJS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

debug : $(SRCS)
	@echo 'Making debug executable.'
	@$(CC) $(DEBUG) $(SRCS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

sanitize : $(SRCS)
	@echo 'Making debug executable with -fsanitize=address.'
	@$(CC) $(DEBUG) -fsanitize=address $(SRCS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

clean :
	@echo 'Directory cleaned by make.'
	@$(RM) $(OBJS) $(NAME).dSYM

fclean : clean
	@echo 'Executable removed.'
	@$(RM) $(NAME)

re : fclean all
