# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 00:26:13 by sehhong           #+#    #+#              #
#    Updated: 2022/04/27 14:32:15 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR 	= ./
SRCS 		= $(addprefix $(SRCS_DIR), \
				check_error.c \
				do_routine.c \
				fill_up_box.c \
				main.c \
				monitor_philos.c \
				rm_table.c \
				run_simulation.c \
				set_table.c \
				utils.c \
				)
OBJS 		= $(SRCS:.c=.o)

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
