NAME = minishell

SRCS_DIR = ./src/
PARSE_FILE = split_args.c var_processing.c lst_cmd_utils.c lexing_check.c parsing.c \
			mini_commande_parse.c token.c initialization.c exce_builtin.c \
			lst_token_utils.c save_token.c lexing.c var_proces_utils.c \
			var_proces_utils_2.c var_proces_utils_3.c pipe_proces.c \
			split_args_other.c input_process.c append_process.c \
			herdoc_process.c  output_process.c trunc_process.c \
			quote_process_utils.c quote_process.c

EXEC_FILE = exec.c find_file.c ft_echo.c ft_pwd.c mini_cd.c mini_exec_utils.c env.c env_utils.c unset.c export.c export_utils.c mini_exit.c var.c

DIR_PARSE = $(SRCS_DIR)parse/
DIR_EXEC = $(SRCS_DIR)exec/

PARSE = $(addprefix $(DIR_PARSE), $(PARSE_FILE))
EXEC = $(addprefix $(DIR_EXEC), $(EXEC_FILE))
SRCS = $(addprefix $(SRCS_DIR), main.c utils.c clear.c start_up.c signal.c) $(PARSE) $(EXEC)

OBJS = $(SRCS:.c=.o)

LIBFT = ./lib/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	clear

$(LIBFT):
	make all -C lib
	clear
clean:
	-rm -f $(OBJS)
	make clean -C lib

fclean: clean
	-rm -f $(NAME)
	make fclean -C lib

re: fclean all
	make re -C lib

test :
	valgrind --suppressions=leak_ignore.sup --leak-check=full --show-leak-kinds=all ./minishell

