
CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic 



%.o:  %.c
	$(CC) $(CFLAGS) -o $@ $<

