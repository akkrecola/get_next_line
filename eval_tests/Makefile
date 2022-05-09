# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 03:24:01 by elehtora          #+#    #+#              #
<<<<<<< Updated upstream
#    Updated: 2022/05/04 17:44:32 by elehtora         ###   ########.fr        #
=======
#    Updated: 2022/05/09 13:27:13 by elehtora         ###   ########.fr        #
>>>>>>> Stashed changes
#                                                                              #
# **************************************************************************** #

NAME		= gnl.out

SRCS		= ../get_next_line.c main.c
OBJS		= $(SRCS:.c=.o)
LIB			= -lft

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Wconversion
<<<<<<< Updated upstream
DEBUG		= -g
=======
DEBUG		= -g -Wall
>>>>>>> Stashed changes

INCL		= -I..
LIBPATH		= -L../libft

RM			= /bin/rm -rf

# RECIPES #

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

debug : $(SRCS)
	$(CC) $(DEBUG) $(SRCS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

<<<<<<< Updated upstream

clean :
	$(RM) $(OBJS) $(NAME).dSYM
=======
sanitize : $(SRCS)
	$(CC) $(DEBUG) -fsanitize=address $(SRCS) $(INCL) $(LIBPATH) $(LIB) -o $(NAME)

clean :
	$(RM) $(OBJS) $(NAME).dSYM output
>>>>>>> Stashed changes

fclean : clean
	$(RM) $(NAME)

re : fclean all
