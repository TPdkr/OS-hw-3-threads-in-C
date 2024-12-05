#this was done by Timofei Podkorytov
#for assignment 3 for Operating Systems course
#fall 2024
test: test.c utils.c numar.c
	gcc -Wall -o test test.c utils.c numar.c
main: pdi-numbers.c utils.c numar.c
	gcc -Wall -o pdi-numbers pdi-numbers.c utils.c numar.c
all: pdi-numbers.c utils.c numar.c test.c
	gcc -Wall -o pdi-numbers pdi-numbers.c utils.c numar.c
	gcc -Wall -o test test.c utils.c numar.c
