# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jovieira <jovieira@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/30 16:44:34 by jovieira      #+#    #+#                  #
#    Updated: 2024/01/15 15:29:16 by jovieira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
HEADER 	= philo.h
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3
DEBUG = 0  # Set to 1 for debug mode, 0 for regular mode
LEAK = 0

ifeq ($(DEBUG), 1)
    CFLAGS	+= -fsanitize=thread -g
endif

ifeq ($(LEAK), 1)
	CFLAGS	+= -fsanitize=address -g
endif

# CFLAGS	+= -fsanitize=thread -g
# CFLAGS	+= -fsanitize=address -g
SRC_DIR	= philo
OBJ		= $(SRC:%.c=obj/%.o)
OBJ_DIR	= obj

SRC		= main.c\
		  admin.c\
		  rotine.c\
		  parsing.c\
		  var_init.c\
		  end_prog_.c\
		  print_mach.c\
		  time_utils_.c\
		  mutex_utils_.c\


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