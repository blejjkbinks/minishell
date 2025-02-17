# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 14:35:21 by rdomange          #+#    #+#              #
#    Updated: 2025/02/13 20:50:54 by rdomange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

#for parent Makefile
#$(MAKE) -C libft
#$(CC) $(OBJ) -Llibft -lft -o $(NAME)

SRC_DIR := ./src/
HDR_DIR := ./header/
OBJ_DIR := ./obj/
CFLAGS := -Wall -Wextra -Werror -g -I$(HDR_DIR)
CC := cc $(CFLAGS)
CC_NOFLG := cc
AR := ar rcs
RM := rm -rf
MKD := mkdir -p
CATS := CHR FUN LIST MEM NBR SPLIT STR WRT

#when changing: CATS, SRC_CATS, libft.h, filename, stdheader

MAKEFLAGS += --no-print-directory

SRC_CHR := \
	isalnum		isalpha		isalpha_lower		isalpha_upper \
	isascii		isdigit		isprint		isspace \
	strcapital	strtolower	strtoupper	tolower	toupper \
	strisdigit \

SRC_FUN := \
	printmemory		bit		free	malloc	sort \
	random		test_libft \

SRC_LIST := \
	lstadd_back		lstadd_front	lstclear	lstdelone \
	lstlast			lstcreate_node			lstlen \
	lstindex_at		lstindex_get	lstfind \
	lstsort		lstmerge	lstadd_sort		lstmerge_sort \
	lstremove	lstreverse	lstprint \

SRC_MEM := \
	bzero	calloc	realloc	memchr	memcmp	memcpy	memmove	memset \
	strdup \

SRC_NBR := \
	atoabase	atoi	itoa	itoa_ulong	nbrlen \
	min		max		abs		mod_range	numcmp \

SRC_SPLIT := \
	split	split_set	split_free	split_len \
	isquoted	split_quotes	splittrim_quotes	strtrim_quotes \
	isquoted_closed \

SRC_STR := \
	strchr	strrchr	strjoin	strjoin_free	strnjoin \
	strlcat	strlcpy	strlen strnlen \
	strncmp	strcmp	strnstr	strtrim	substr \

SRC_WRT := \
	putchar_fd	putendl_fd \
	putnbr_fd	putstr_fd \
	get_next_line	printf \
	putchar	putstr	putnbr \

tolower = $(shell echo '$1' | tr '[:upper:]' '[:lower:]')

$(foreach c, $(CATS), \
	$(foreach i, $(SRC_$(c)), \
		$(eval SRC += $(SRC_DIR)$(call tolower,$(c))/ft_$(i).c)))

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(OBJ_DIR):
	@$(MKD) $(foreach c, $(CATS), $@/$(call tolower,$(c)))
	@echo "libft compiling objects"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "libft compiling archive"

clean: testclean
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "libft fcleaning"

re: fclean all

countfiles: all testclean
	@printf "norminette KOs: "
	@norminette | grep Error! | wc -l
	@printf "src: "
	@tree $(SRC_DIR) | grep files
	@printf "obj: "
	@tree $(OBJ_DIR) | grep files
	@$(MAKE) fclean

gitstat: fclean
	find . -name '.DS_Store' -type f -delete
	git status

m := pushed from libft makefile on $(shell date +"%d/%m %H:%M")
GIT_PUSH_MESSAGE := $(m)

gitpush: gitstat
	git add .
	git commit -m "$(GIT_PUSH_MESSAGE)"
	git push

TEST_A := test
TEST_C := test.c

testclean:
	@$(RM) $(TEST_C)
	@$(RM) $(TEST_A)
	@$(RM) $(TEST_A).dSYM

$(TEST_C):
	@touch $@
	@echo '#include "libft.h"' > $@
	@echo '#include <stdio.h>' >> $@
	@echo '' >> $@
	@echo 'int	main(void)' >> $@
	@echo '{' >> $@
	@echo '	ft_printf(".%-15.13s.\\n", "new test file");' >> $@
	@echo '	//ft_test_libft();' >> $@
	@echo '}' >> $@

test: all $(TEST_C)
	$(CC) $(TEST_C) $(NAME) -o $(TEST_A)
	@echo "letsgo :)\nvvvvv"
	@./$(TEST_A)
	@printf "###\n^^^^^\ndone :)\n"

.PHONY: all clean fclean bonus test testclean countfiles gitstat gitpush
