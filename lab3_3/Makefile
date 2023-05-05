CC = gcc

base:
	$(CC) -c hash_table.c
	$(CC) -c parse_input.c
	$(CC) -c input_funcs.c
	$(CC) -c lab3_3.c
	$(CC) -o lab3_3 lab3_3.o input_funcs.o parse_input.o hash_table.o -lm
	rm *.o
