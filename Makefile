CC=gcc
CFLAGS=
LDFLAGS=-lreadline

SRC= src/main.c src/modules/*.c

build:
	@$(CC) $(SRC) -o whyshell $(LDFLAGS)

all:
	build