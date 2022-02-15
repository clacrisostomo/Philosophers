# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 00:34:28 by csantos-          #+#    #+#              #
#    Updated: 2022/02/14 03:28:17 by csantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./includes/philo.h

SRC_PATH =	./sources \

SRC =		main.c\
			parse.c\
			time.c\
			utils.c\
			actions.c\
			dinner.c\
			routine.c\


OBJ_DIR	=	./builds
OBJ		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

vpath %.c $(SRC_PATH)

all: $(NAME)

$(NAME): $(OBJ)
		gcc $(CFLAGS) -pthread -g -o $(NAME) $(OBJ) -I includes
#-fsanitize=thread
#-fsanitize=leak

$(OBJ_DIR)/%.o:	%.c ./includes/philo.h
	mkdir -p $(OBJ_DIR)
	gcc -c -o $@ $(CFLAGS) -I includes -g3 $<

valgrind:
	valgrind --tool=drd --log-file="out.txt" ./philo 10 2000 100 100 3
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="out.txt" ./philo 2 202 100 100 3

git:
	@git add .
	@git commit -m "$m"
	@git push

clean:
		rm -f $(OBJ)
		rm -rf ./builds

fclean: clean
		rm -f $(NAME) $(OBJ)

re: fclean all