# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 10:09:05 by vrandria          #+#    #+#              #
#    Updated: 2024/12/14 08:52:40 by vrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCSLIB_DIR = ./libft/

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

SRCS = $(SRCSLIB)
 

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME)	: $(OBJS)
		ar rcs $(NAME) $(OBJS)
all : $(NAME)

clean :
		$(RM) $(OBJS)

fclean	: clean
		$(RM) $(NAME)

re : fclean all

