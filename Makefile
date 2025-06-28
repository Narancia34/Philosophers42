# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 11:08:29 by mgamraou          #+#    #+#              #
#    Updated: 2025/06/28 11:12:31 by mgamraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = $(shell ls *.c)
OFILES = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) 

clean:
	rm -f $(OFILES)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
