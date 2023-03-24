CC=gcc

queue_vector:
	$(CC) -c ./queue_vec/queue_vec.c
	mv queue_vec.o ./queue_vec/
	ar r libqueue_vec.a ./queue_vec/queue_vec.o
	mv libqueue_vec.a ./queue_vec/
	$(CC) -c task.c
	$(CC) -c input_funcs.c
	$(CC) -o task_vec task.o input_funcs.o -L./queue_vec -lqueue_vec -lm
	rm *.o

queue_list:
	$(CC) -c ./queue_list/list.c
	$(CC) 
