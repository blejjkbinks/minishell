CFLAGS := -Wall -Wextra -Werror

all:
	$(MAKE) -C ../libft
	cc pipe.c ../libft/libft.a -o p && ./p
	@rm -rf ./p

clean:
	rm -rf p

