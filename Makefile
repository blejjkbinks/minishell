# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 14:41:49 by rdomange          #+#    #+#              #
#    Updated: 2025/02/06 14:42:52 by rdomange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := src/
HDR_DIR := header/
OBJ_DIR := obj/
CFLAGS := -Wall -Wextra -Werror -O3 -I$(HDR_DIR)
CC := cc $(CFLAGS)
RM := rm -rf
MKD := mkdir -p

LIBFT := libft/
LIBFT_A := libft.a

L_FT := -Llibft -lft
L_READLINE := -L/usr/local/opt/readline/lib -lreadline

SRC := $(wildcard $(SRC_DIR)*.c)
#	was wildcard always allowed?
#	i could always write them all down haha zzz

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

##  rules  ##

all: $(NAME)

$(LIBFT):
	git clone git@github.com:blejjkbinks/libft.git libft

pull_libft:
	@echo pulling libft
#	i wanna check that nothing changed in the cloud or the clone

$(LIBFT_A): $(LIBFT) pull_libft
	$(MAKE) -C libft

$(OBJ_DIR):
	$(MKD) $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	$(CC) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(OBJ) $(L_FT) $(L_READLINE) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

gitstat: fclean
	find . -name '.DS_Store' -type f -delete
	git status

gitpush:
	git add .
	git commit -m "pushed from minishell makefile on $(shell date +"%d/%m %H:%M")"
	git push

print:
	@echo i love makefile

.PHONY: all clean fclean re print
