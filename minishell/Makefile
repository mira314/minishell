
NAME = minishell

SRCS_DIR = ./src/

SRCS = $(addprefix $(SRCS_DIR), main.c)

LIBFT = ./lib/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) ${FLAGS} -o $@ -c $?

$(NAME): ${LIBFT} $(OBJS)
	${CC} ${FLAGS} ${SRCS} -o $(NAME) ${LIBFT}

${LIBFT}:
	make all -C lib

clean:
	-rm -f ${OBSJ}
	make clean -C lib

fclean: clean
	-rm -f $(NAME)
	make fclean -C lib

re: fclean all
	make re -C lib
