# Build target
apc.out: main.o division.o multiplication.o addition.o modulus.o helper.o operations.o square.o subtraction.o
	gcc -o $@ $^

# Compilation rules for each .c file
main.o: main.c apc.h
	gcc -c main.c -o main.o

division.o: division.c apc.h
	gcc -c division.c -o division.o

multiplication.o: multiplication.c apc.h
	gcc -c multiplication.c -o multiplication.o

addition.o: addition.c apc.h
	gcc -c addition.c -o addition.o

modulus.o: modulus.c apc.h
	gcc -c modulus.c -o modulus.o

helper.o: helper.c apc.h
	gcc -c helper.c -o helper.o

operations.o: operations.c apc.h
	gcc -c operations.c -o operations.o

square.o: square.c apc.h
	gcc -c square.c -o square.o

subtraction.o: subtraction.c apc.h
	gcc -c subtraction.c -o subtraction.o

# Clean rule
clean:
	rm -f *.o apc.out

