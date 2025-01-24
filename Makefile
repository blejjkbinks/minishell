# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 19:49:07 by rdomange          #+#    #+#              #
#    Updated: 2024/09/19 20:01:06 by rdomange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

HDR := ./header
CFLAGS := -Wall -Wextra -Werror -I$(HDR) -g
CC := cc $(CFLAGS)
AR := ar rcs
RM := rm -rf
MK := mkdir -p

SRC_DIR := ./src
OBJ_DIR := ./obj

SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MK) $(OBJ_DIR)
	@$(CC) -c $< -o $@

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	$(CC) $(OBJ) -Llibft -lft -ledit -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: clean all

print:
	@echo $(SRC)
	@echo $(CC)

#gpt boss
GPT_BIN = gpt_exec

gpt_%: gpt_%.c
	cc -o $(GPT_BIN) $<

gpt_clean:
	rm -f $(GPT_BIN)
#gpt boss

.PHONY: all clean fclean re print gpt_clean
