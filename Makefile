# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:19:31 by mbaron            #+#    #+#              #
#    Updated: 2018/01/10 17:31:11 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		fillit

DIR			=		./scr

DIR_HEADERS	=		./inc

LIB			=		-L./libft -lft

HEADERS		=		-I$(DIR_HEADERS)

SRCS		=		main.c		\
					solver.c		\
					output.c	\
					test.c		\
					tetras_lib.c

OBJS		=		$(SRCS:.c=.o)

CC			=		gcc

CFLAGS		=		-Wall -Wextra

RM			=		rm -f

all			:		$(NAME)

$(NAME)		:		$(OBJS)
					$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(HEADERS) $(LIB)

%.o			:		%.c
					$(CC) -o $@ -c $< $(CFLAGS) $(HEADERS)

clean		:
					$(RM) $(OBJS)

fclean		:		clean
					$(RM) $(NAME)

re			:		fclean all
