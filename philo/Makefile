# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 16:44:34 by jovieira          #+#    #+#              #
#    Updated: 2023/09/20 16:43:59 by jovieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
HEADER 	= philo.h
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
# CFLAGS	+= -fsanitize=thread -g
# CFLAGS	+= -fsanitize=address -g
SRC_DIR	= philo #$(shell find src -type f -name "*.c")
OBJ		= $(SRC:%.c=obj/%.o)
OBJ_DIR	= obj

SRC		= main.c\
		  admin.c\
		  print.c\
		  thread.c\
		  parsing.c\
		  extra_utils.c\


all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	
$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)


obj/%.o: %.c | $(OBJ_DIR)
	gcc $(INCLUDES) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)
re: fclean all