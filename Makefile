CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/executor.c src/parser.c src/redirection.c 
OUT = tinysh

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	$(RM) $(OUT)
