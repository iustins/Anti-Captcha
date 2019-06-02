CC = gcc
CFLAGS = -Wall

SRCS = utils.c main.c
HEAD = utils.h structs.h
EXEC = tema3

build: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

rebuild:
	rm -f $(EXEC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)