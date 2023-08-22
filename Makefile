all: main.c
	cc src/main.c -Wall -lm -o birdOS
run:
	cc src/main.c -Wall -lm -o birdOS
	./birdOS
debug:
	cc src/main.c -Wall -lm -o birdOS
	./birdOS debug