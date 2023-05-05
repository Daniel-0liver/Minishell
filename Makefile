GREEN		= 	\033[0;32m
RED			= 	\033[0;31m
RESET		= 	\033[0m

NAME		=	minishell

HEADER		=	./includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))

SRC			=	src/minishell.c \
				src/parse/parse_init.c \
				src/parse/parse_utils.c

CC			=	cc
FLAGS		=	-I${HEADER} -lreadline #-Wall -Wextra -Werror -g -fsanitize=thread

all:		obj $(NAME)

$(NAME):	$(OBJ)
			@$(CC) -o $@ $^ $(FLAGS)

obj:
			@mkdir -p obj/parse

obj/%.o:	src/%.c ./includes/minishell.h
			@$(CC) $(FLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

valgrind:	all
			valgrind --leak-check=full --show-leak-kinds=all --quiet ./minishell

clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re