CFLAGS = -Wall -Wextra -g

%: %.c
	gcc $(CFLAGS) $^ -o $@
