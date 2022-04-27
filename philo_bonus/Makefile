# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 00:26:13 by sehhong           #+#    #+#              #
#    Updated: 2022/04/27 18:40:14 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS_DIR	= ./
SRCS		= $(addprefix $(SRCS_DIR), \
				do_routine_bonus.c \
				exit_bonus.c \
				main_bonus.c \
				run_simulation.c \
				semaphore_bonus.c \
				set_table_bonus.c \
				utils_bonus.c \
				)
OBJS		= $(SRCS:.c=.o)

CC 			= cc
RM 			= rm -f
CFLAGS 		= -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
