CC = gcc

base:

	$(CC) -c table.c
	$(CC) -c parse_input.c
	$(CC) -c input_funcs.c
	$(CC) -c table.c
	$(CC) -c task_b.c
	$(CC) -o task_b task_b.o parse_input.o input_funcs.o table.o -lm
	rm *.o
