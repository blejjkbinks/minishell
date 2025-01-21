CFLAGS := -Wall -Wextra -Werror

all:
	$(MAKE) -C ../libft
	cc pipe.c ../libft/libft.a -o p && ./p

clean:
	rm -rf p

