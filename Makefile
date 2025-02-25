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

SRC_DIR := src
HDR_DIR := header
OBJ_DIR := obj
CFLAGS := -Wall -Wextra -Werror -g -I$(HDR_DIR)
MS_CUTE := 1
MS_DEBUG := 0
CFLAGS += -D MS_CUTE=$(MS_CUTE) -D MS_DEBUG=$(MS_DEBUG)
CC := cc $(CFLAGS)
RM := rm -rf
MKD := mkdir -p

LIBFT := libft
LIBFT_A := $(LIBFT)/libft.a

L_FT := -Llibft -lft
L_READLINE := -L/usr/local/opt/readline/lib -lreadline

MAKEFLAGS += --no-print-directory

SRC := $(wildcard $(SRC_DIR)/*.c)
#	was wildcard always allowed?
#	i could always write them all down haha zzz
#SRC := \
	cd_pwd.c	env_builtin.c	env_help.c \
	exec_pipe.c		find_builtin.c	exec_builtin.c \
	minishell.c		get_prompt.c \
	cash_money.c	double_exclam.c		redirection.c \

#SRC := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

##  rules  ##

all: $(NAME)

$(LIBFT):
	git clone git@github.com:blejjkbinks/libft.git libft
	$(RM) $(LIBFT)/.git
	$(RM) $(LIBFT)/readme.md

$(LIBFT_A): $(LIBFT)
	@$(MAKE) -C libft

$(OBJ_DIR):
	@$(MKD) $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	@$(CC) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJ)
	@echo compiling $(NAME)
	@$(CC) $(OBJ) $(L_FT) $(L_READLINE) -o $(NAME)

clean:
	@echo cleaning $(NAME)
	@$(RM) $(OBJ_DIR)
	@$(RM) testing/results.log

fclean: clean
	@$(RM) $(NAME)
	@if [ -d "$(LIBFT)" ]; then \
		$(MAKE) -C libft fclean; \
	fi

re: fclean all

##  funny rules  ##

gitstat: fclean
	find . -name '.DS_Store' -type f -delete
	git status

m := pushed from libft makefile on $(shell date +"%d/%m %H:%M")
GIT_PUSH_MESSAGE := $(m)

gitpush: gitstat
	git add .
	git commit -m "$(GIT_PUSH_MESSAGE)"
	git push

print:
	@echo $(SRC)

SOURCE_TXT := minishell_source.txt
source_txt:
	@> $(SOURCE_TXT)
	@for file in $(shell echo $(SRC_DIR)/*.c); do \
		tail -n +14 $$file >> $(SOURCE_TXT); \
	done
	@for file in $(shell echo $(LIBFT)/src/*/*.c); do \
		tail -n +14 $$file >> $(SOURCE_TXT); \
	done
	@mv $(SOURCE_TXT) ~/Desktop/$(SOURCE_TXT)
	@echo ok its on your desktop

.PHONY: all clean fclean re print gitstat gitpush source_txt
