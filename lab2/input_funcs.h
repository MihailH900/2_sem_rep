#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include <stdlib.h>

typedef struct Process
{
	unsigned int id;
	unsigned int tc;
	unsigned int te;
	unsigned int te_copy;

} Process;

char* readline();
char get_queue_size(char* in, unsigned int* size);
size_t check_format(char* in);
void parse_input(char* in, Process* p, unsigned int* time_step);
unsigned int get_numb_in_str(char** c, char ch1, char ch2);
char shift(char** c, char ch1, char ch2);

#endif
