# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 01:40:02 by sehhong           #+#    #+#              #
#    Updated: 2022/04/29 01:40:02 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR	= ./
SRCS		= $(addprefix $(SRCS_DIR), \
				call_philos_bonus.c \
				exit_bonus.c \
				main_bonus.c \
				rm_table_bonus.c \
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
