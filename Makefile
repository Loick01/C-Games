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
	
build : all.o game1.o game2.o game3.o game4.o game5.o main.o
	$(CC) $(CFLAGS) -o exe all.o game1.o game2.o game3.o game4.o game5.o main.o -lSDL2 -lSDL2_ttf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind :
	make build
	valgrind ./exe
	
install :
	sudo apt-get install libsdl2-dev libsdl2-ttf-dev
	
	

