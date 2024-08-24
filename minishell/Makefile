
NAME = minishell

SRCS_DIR = ./src/

PARSE_FILE = 

EXEC_FILE = 

DIR_PARSE = ${SRCS_DIR}parse/

DIR_EXEC = ${SRCS_DIR}exec/

PARSE = $(addprefix $(DIR_PARSE), ${PARSE_FILE})

EXEC = $(addprefix $(DIR_EXEC), ${EXEC_FILE})

SRCS = $(addprefix $(SRCS_DIR), main.c) ${PARSE} ${EXEC}

LIBFT = ./lib/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) ${FLAGS} -o $@ -c $?

$(NAME): ${LIBFT} $(OBJS)
	${CC} ${FLAGS} ${SRCS} -o $(NAME) ${LIBFT} -lreadline

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
