# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 00:26:13 by sehhong           #+#    #+#              #
#    Updated: 2022/03/03 13:43:00 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR = ./srcs/mandatory/
SRCS = $(addprefix $(SRCS_DIR), \
			check_error.c main.c mutex_utils.c parse_arguments.c \
			print_msg.c routine_of_philosophers.c start_routine.c \
			thread_utils.c time_utils.c update_philo_status.c \
			)
OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I./includes/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
