CC = gcc
CFLAGS = -Wall -Wextra -g

launch :
	make build
	make run
	make clean
	
run :
	./exe
	
clean :
	rm exe *.o
	
build : all.o game1.o game2.o main.o
	$(CC) $(CFLAGS) -o exe all.o game1.o game2.o main.o -lSDL2

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

	
	

