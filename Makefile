CC = gcc
CFLAGS = -Wall -g

SRC = src/main.c src/executor.c
OUT = tinysh

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
