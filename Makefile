CFLAGS ?= -Wall -Wextra -Werror -pedantic -ggdb

build/main: src/main.c src/textures.h build/board.o build/board_renderer.o
	$(CC) $(CFLAGS) -o $@ -lraylib $^

build/board_renderer.o: src/board_renderer.c \
                        src/board_renderer.h \
                        src/textures.h       \
                        build/board.o
	$(CC) $(CFLAGS) -c -o $@ $<

build/board.o: src/board.c src/board.h
	$(CC) $(CFLAGS) -c -o $@ $<
