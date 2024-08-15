# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrandria <vrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 10:09:05 by vrandria          #+#    #+#              #
#    Updated: 2024/03/23 16:00:51 by vrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	= libft.a
SRCSLIB_DIR = ./libft/
SRCSPR_DIR = ./libft/printf/
SRCSLIB	= $(addprefix $(SRCSLIB_DIR),\
		ft_atoi.c get_next_line.c\
		ft_bzero.c ft_calloc.c \
		ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_split.c \
		ft_strchr.c ft_strdup.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c \
		ft_toupper.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putnbr_fd.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c )

SRCSPR = $(addprefix $(SRCSPR_DIR),\
		ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_put_hex.c ft_putptr.c)

SRCS = $(SRCSLIB) $(SRCSPR)
 

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

.c.o	:
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS)
		ar rcs $(NAME) $(OBJS)
all : $(NAME)

clean :
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean	: clean
		$(RM) $(NAME)

re : fclean all

