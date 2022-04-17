# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 00:26:13 by sehhong           #+#    #+#              #
#    Updated: 2022/04/17 11:12:21 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_M_DIR 	= ./srcs/mandatory/
SRCS_M 		= $(addprefix $(SRCS_M_DIR), \
				check_error.c \
				main.c \
				mutex_utils.c \
				parse_arguments.c \
				print_msg.c \
				routine_of_philosophers.c \
				start_routine.c \
				thread_utils.c \
				time_utils.c \
				update_philo_status.c \
				)
OBJS_M 		= $(SRCS_M:.c=.o)

SRCS_B_DIR	= ./srcs/bonus/
SRCS_B		= $(addprefix $(SRCS_B_DIR), \
				call_philos_bonus.c \
				exit_with_err_bonus.c \
				main_bonus.c \
				routine_bonus.c \
				set_table_bonus.c \
				time_utils_bonus.c \
				)
OBJS_B		= $(SRCS_B:.c=.o)


ifdef WITH_BONUS
	OBJS 	= $(OBJS_B)
else
	OBJS 	= $(OBJS_M)
endif

ifdef DEBUG
	CFLAGS 	= -g3 -fsanitize=address
else
	CFLAGS 	= -Wall -Wextra -Werror
endif

CC 			= cc
RM 			= rm -f
INCLUDE		= -I./includes/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

bonus:
	make WITH_BONUS=1 all

clean:
	$(RM) $(OBJS_M) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
