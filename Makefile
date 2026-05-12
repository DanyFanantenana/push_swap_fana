# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainarako <ainarako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/24 01:36:54 by ainarako          #+#    #+#              #
#    Updated: 2026/05/11 08:57:09 by faharila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CHECK = checker

ALL_SRCS = check_args.c ft_atoi.c ft_isdigit.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strcmp.c \
		index.c push.c swap.c rotate.c revrotate.c radix.c simple.c \
		simple_sort.c medium.c get_next_line.c get_next_line_utils.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_bzero.c t_list.c utils.c \
		adaptive.c bench.c bench_utils.c bench_p_utils.c bench_r_utils.c bench_s_utils.c

SRCS = $(ALL_SRCS) main.c
CHECK_SRCS = $(ALL_SRCS) checker.c

OBJS = ${SRCS:.c=.o}
CHECK_OBJS = ${CHECK_SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDLIBS = -lm

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

RM = rm -rf

all: ${NAME} ${CHECK}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LDLIBS}

${CHECK}: ${CHECK_OBJS}
	@${CC} ${CFLAGS} ${CHECK_OBJS} -o ${CHECK} ${LDLIBS}

clean:
	@${RM} ${OBJS}
	@${RM} ${CHECK_OBJS}

fclean: clean
	@${RM} ${NAME}
	@${RM} ${CHECK}

re: fclean all

.PHONY: all clean fclean re
