# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 00:26:13 by sehhong           #+#    #+#              #
#    Updated: 2022/04/19 12:57:21 by sehhong          ###   ########.fr        #
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
				call_philo_bonus.c \
				check_if_full_bonus.c \
				main_bonus.c \
				semaphore_bonus.c \
				set_table_bonus.c \
				utils_bonus.c \
				)
OBJS_B		= $(SRCS_B:.c=.o)


ifdef WITH_BONUS
	OBJS 	= $(OBJS_B)
else
	OBJS 	= $(OBJS_M)
endif

CC 			= cc
RM 			= rm -f
INCLUDE		= -I./includes/
CFLAGS 	= -Wall -Wextra -Werror

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
