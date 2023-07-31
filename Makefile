CC=gcc
CFLAGS=-g -Wall -Wextra
LEAK=leaks
LFLAGS=-atExit --

STRUCTS=structs
GLOBAL=utils
WORLD=world_utils
MOVE=movement_utils

build: TerminalSnake

TerminalSnake: main.o $(GLOBAL).o $(WORLD).o $(MOVE).o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) $^ -c

$(GLOBAL).o: $(GLOBAL).c $(GLOBAL).h
	$(CC) $(CFLAGS) $^ -c

$(WORLD).o: $(WORLD).c $(WORLD).h
	$(CC) $(CFLAGS) $^ -c

$(MOVE).o: $(MOVE).c $(MOVE).h
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -rf *.o *.gch

run:
	./TerminalSnake