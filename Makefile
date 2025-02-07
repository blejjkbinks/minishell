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

#SRC := $(wildcard $(SRC_DIR)*.c)
#	was wildcard always allowed?
#	i could always write them all down haha zzz

SRC := \
	minishell.c		env_builtin.c		env_help.c	cd_pwd.c \

SRC := $(addprefix src/, $(SRC))

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

##  rules  ##

all: $(NAME)

$(LIBFT):
	git clone git@github.com:blejjkbinks/libft.git libft
	$(RM) libft/.git

$(LIBFT_A): $(LIBFT)
	@$(MAKE) -C libft | grep -v "Nothing to be done for 'all'." || echo "libft ready"

$(OBJ_DIR):
	@$(MKD) $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	@$(CC) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJ)
	@echo compiling $(NAME)
	@$(CC) $(OBJ) $(L_FT) $(L_READLINE) -o $(NAME)

clean:
	@echo cleaning $(NAME)
	@$(RM) $(OBJ_DIR)

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

.PHONY: all clean fclean re print gitstat gitpush
