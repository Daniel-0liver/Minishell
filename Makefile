GREEN		= 	\033[0;32m
RED			= 	\033[0;31m
RESET		= 	\033[0m

NAME		=	minishell

LFT			=	libft/obj libft/libft.a

HEADER		=	./includes -I ./libft/includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))

SRC			=	src/minishell.c \
				src/parse/utils.c \
				src/parse/utils2.c \
				src/parse/parse_init.c \
				src/parse/parse_utils.c \
				src/parse/parse_quotes.c \
				src/cmd_handler/cmds.c \
				src/cmd_handler/free.c \
				src/cmd_handler/cmds_utils.c \
				src/cmd_handler/cmds_utils2.c \
				src/cmd_handler/cmds_utils3.c \
				src/cmd_handler/cmds_utils4.c \
				src/cmd_handler/split_cmds.c \
				src/execution/ft_exec.c \
				src/execution/ft_exec_utils.c \
				src/execution/ft_redirect.c \
				src/execution/ft_input.c \
				src/builtins/ft_cd.c \
				src/builtins/ft_pwd.c \
				src/builtins/ft_env.c \
				src/builtins/ft_exit.c \
				src/builtins/ft_echo.c \
				src/builtins/ft_unset.c \
				src/builtins/ft_export.c \
				src/builtins/error_msg.c \
				src/builtins/check_builtins.c

CC			=	cc
FLAGS		=	-I${HEADER} -Wall -Wextra -Werror -g -fsanitize=address

all:		$(LFT) obj $(NAME) 

$(NAME):	$(OBJ)
			@$(CC) -o $@ $^ $(FLAGS) -lreadline -L ./libft -lft

$(LFT):		
			@@echo " [ .. ] | Compiling libft.."
			@$(MAKE) -C libft -f Makefile all --no-print-directory
			@@echo " [ $(GREEN)OK$(RESET) ] | Libft ready!"

obj:
			@mkdir -p obj/parse obj/execution obj/builtins obj/cmd_handler

obj/%.o:	src/%.c ./includes/minishell.h
			@$(CC) $(FLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

valgrind:	all
			valgrind --leak-check=full --show-leak-kinds=all ./minishell

clean:
			@rm -rf $(OBJ) obj
			@$(MAKE) -C libft -f Makefile clean --no-print-directory
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)
			@$(MAKE) -C libft -f Makefile fclean --no-print-directory

re:			fclean all

.PHONY:		all clean fclean re