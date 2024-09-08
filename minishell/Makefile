
NAME = minishell

SRCS_DIR = ./src/

PARSE_FILE = mini_commande_parse.c token.c initialization.c exce_builtin.c

EXEC_FILE =	ft_echo.c	\
			ft_pwd.c	\
			mini_cd.c	\
			mini_exec_utils.c 

DIR_PARSE = ${SRCS_DIR}parse/

DIR_EXEC = ${SRCS_DIR}exec/

PARSE = $(addprefix $(DIR_PARSE), ${PARSE_FILE})

EXEC = $(addprefix $(DIR_EXEC), ${EXEC_FILE})

SRCS = $(addprefix $(SRCS_DIR), main.c) ${PARSE} ${EXEC}

LIBFT = ./lib/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

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
