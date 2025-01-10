CFLAGS ?= -Wall -Wextra -Werror -pedantic -ggdb

build/main: src/main.c src/textures.h build/board.o
	$(CC) $(CFLAGS) -o $@ -lraylib $^

build/board.o: src/board.c src/board.h
	$(CC) $(CFLAGS) -c -o $@ $<
