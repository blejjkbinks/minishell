NAME := libft.a

SRC_DIR := ./src/
HDR_DIR := ./header/
OBJ_DIR := ./obj/
CFLAGS := -Wall -Wextra -Werror -I$(HDR_DIR)
CC := cc $(CFLAGS)
AR := ar rcs
RM := rm -rf
MKD := mkdir -p
CATS := CHR FUN LST MEM NBR SPL STR WRT

SRC_CHR := \
	isalnum		isalpha		isalpha_lower		isalpha_upper \
	isascii		isdigit		isprint		isspace \
	strcapital	strtolower	strtoupper	tolower	toupper \

SRC_FUN := \
	printmemory		bit		free	malloc \

SRC_LST := \
	lstadd_back		lstadd_front	lstclear	lstdelone \
	lstlast			lstnew			lstlen 		lstindex	lstfind \

SRC_MEM := \
	bzero	calloc	realloc	memchr	memcmp	memcpy	memmove	memset \
	strdup \

SRC_NBR := \
	atoabase	atoi	itoa	itoa_ulong	nbrlen \
	min	max	abs \

SRC_SPL := \
	split	split_free	split_len	split_realloc	split_remove \

SRC_STR := \
	strchr	strrchr	strjoin	strjoin_free	strnjoin \
	strlcat	strlcpy	strlen strnlen \
	strncmp	strnstr	strtrim	substr \

SRC_WRT := \
	putchar_fd	putendl_fd \
	putnbr_fd	putstr_fd \
	get_next_line	printf	\

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

TEST := test.c

testclean:
	@$(RM) $(TEST)
	@$(RM) a.out
	@$(RM) a.out.dSYM

$(TEST):
	@touch $@
	@echo '#include "libft.h"' > $@
	@echo '#include <stdio.h>' >> $@
	@echo '' >> $@
	@echo 'int main()' >> $@
	@echo '{' >> $@
	@echo '	ft_printf(".  %-15.13s.\\n", "new test file;");' >> $@
	@echo '}' >> $@

test: all $(TEST)
	$(CC) $(TEST) $(NAME)
	@echo "letsgo :)\nvvvvv"
	@./a.out
	@echo "\n^^^^^\ndone :)"

countfiles: all testclean
	@printf "norminette KOs: "
	@norminette | grep "Error!" | wc -l
	@printf "src: "
	@tree $(SRC_DIR) | grep files
	@printf "obj: "
	@tree $(OBJ_DIR) | grep files
	@$(MAKE) fclean

#for parent Makefile
#$(CC) $(OBJ) -Llibft -lft -ledit -o $(NAME)

.PHONY: all clean fclean bonus test testclean countfiles
