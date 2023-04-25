CC = gcc

base:

	$(CC) -c table.c
	$(CC) -c parse_input.c
	$(CC) -c input_funcs.c
	$(CC) -c table.c
	$(CC) -c task_a.c
	$(CC) -o task_a task_a.o parse_input.o input_funcs.o table.o -lm
	rm *.o
