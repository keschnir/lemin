# ************************************************************************** #
#                                                          LE - /            #
#                                                              /             #
#   Makefile                                         .::    .:/ .      .::   #
#                                                 +:+:+   +:    +:  +:+:+    #
#   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     #
#                                                 #+#   #+    #+    #+#      #
#   Created: 2018/07/25 16:44:31 by fablin       #+#   ##    ##    #+#       #
#   Updated: 2018/08/31 19:44:05 by fablin      ###    #+. /#+    ###.fr     #
#                                                         /                  #
#                                                        /                   #
# ************************************************************************** #

SRC_DIR	=	./src/

OBJ_DIR	=	./obj/

INC_DIR =	./inc/

NAME	=	lem-in

CFILES	=	main.c	exit.c	init.c	input.c		output.c	solve.c		env.c\
			ant.c	utils.c	init_ext.c			input_ext.c

SOURCES	=	$(addprefix $(SRC_DIR), $(CFILES))

OFILES	=	$(CFILES:.c=.o)

OBJECTS	=	$(addprefix $(OBJ_DIR), $(OFILES))

FLAGS	=	-Wall -Wextra -Werror

MAP		=	maps/s.map

all 	:	$(NAME)

$(NAME)	:	$(OBJECTS)
			@make libft
			gcc $(FLAGS) $(OBJECTS) -L ./libft/ -lft -o $(NAME)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					@make obj
					gcc $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I ./libft/inc/

clean	:	obj
			@make clean -C ./libft/
			@rm -rf $(OBJ_DIR)

fclean	:	obj
			@make fclean -C ./libft/
			@rm -f $(NAME)
			@rm -rf $(OBJ_DIR)

re		:	fclean all

obj		:
			@mkdir -p $(OBJ_DIR)

libft	:
			@make -C ./libft/

test	:	libft
			gcc $(SOURCES) ./libft/libft.a -I ./libft/inc -I ./inc -o lemin_test
			./lemin_test < $(MAP)

debug	:	libft
			gcc -ggdb $(SOURCES) ./libft/libft.a -I ./libft/inc -I ./inc -o lemin_debug
			lldb ./lemin_debug

valgrind:	test
			valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./lemin_test < $(MAP)

.PHONY	:	all clean fclean re libft obj