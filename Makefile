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

SRC_DIR := ./src/
HDR_DIR := ./header/
OBJ_DIR := ./obj/
CFLAGS := -Wall -Wextra -Werror -O3 -I$(HDR_DIR)
CC := cc $(CFLAGS)
RM := rm -rf
MKD := mkdir -p

LIBFT := ./libft/
LIBFT_A := libft.a

L_FT := -Llibft -lft
L_READLINE := -L/usr/local/opt/readline/lib -lreadline

SRC := $(wildcard $(SRC_DIR)/*.c)
#	was wildcard always allowed?
#	i could always write them all down haha zzz

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

##  rules  ##

$(LIBFT):
	git clone git@github.com:blejjkbinks/libft.git libft

$(LIBFT_A): $(LIBFT)
	$(MAKE) -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MK) $(OBJ_DIR)
	@$(CC) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(OBJ) $(L_FT) $(L_READLINE) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
