NAME = minishell

SRCS_DIR = ./src/
PARSE_FILE = split_args.c lst_cmd_utils.c lexing_check.c parsing.c mini_commande_parse.c token.c initialization.c exce_builtin.c lst_token_utils.c save_token.c lexing.c 
EXEC_FILE = ft_echo.c ft_pwd.c mini_cd.c mini_exec_utils.c env.c env_utils.c unset.c export.c export_utils.c

DIR_PARSE = $(SRCS_DIR)parse/
DIR_EXEC = $(SRCS_DIR)exec/

PARSE = $(addprefix $(DIR_PARSE), $(PARSE_FILE))
EXEC = $(addprefix $(DIR_EXEC), $(EXEC_FILE))
SRCS = $(addprefix $(SRCS_DIR), main.c) $(PARSE) $(EXEC)

OBJS = $(SRCS:.c=.o)

LIBFT = ./lib/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

# Compilation des fichiers objets
%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
	make all -C lib

clean:
	-rm -f $(OBJS)
	make clean -C lib

fclean: clean
	-rm -f $(NAME)
	make fclean -C lib

re: fclean all
	make re -C lib

