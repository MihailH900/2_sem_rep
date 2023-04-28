#include <stdio.h>
#include <stdlib.h>

#define MOD 31

char alf[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

size_t hash_function(void* data_ptr, size_t size)
{
	char* byte = data_ptr;
	size_t res = 0, m = 1;
	size_t i = 0;

	while (i < size)
	{
		res += m * (*byte);
		m = m * MOD;
		i++;
	}

	return res;
}

void gen(char* s, size_t n, FILE* f, size_t size)
{
	 for (size_t i = 0; i < 26; i++)
	 {
		 if (n > 1)
		 {
			 gen(s, n-1, f, size);
		 }
		 else
		 {
			s[n-1] = alf[i];
			//printf("%s %zu\n", s, hash_function(s, size));
			fprintf(f, "%s %zu\n", s, hash_function(s, size));
		 }
	 }
}

int main()
{
	FILE* f = fopen("hashes", "w");

	for (size_t i = 1; i < 5; i++)
	{
		char* s = (char* ) malloc(i+1);
		s[i] = '\0';
		for (int j = 0; j < i; j++)
		{
			s[j] = 'a';
		}
		gen(s, i, f, i);
		fprintf(f, "\n");
		free(s);
	}

	fclose(f);

	return 0;
}
