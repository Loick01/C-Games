
launch :
	make build
	make run
	make clean
	
run :
	./exec

build :
	gcc -o exec main.c -lSDL2
	
clean :
	rm exec

