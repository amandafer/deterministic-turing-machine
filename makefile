all:machine memory io
	gcc -g main.c mem_function.o MT.o archive.o -lm -o machine

machine:
	gcc -g -c MT.c

memory:
	gcc -g -c mem_function.c

io:
	gcc -g -c archive.c
