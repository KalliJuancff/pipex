#include <stdio.h>		// printf
#include <unistd.h>		// getpid

int main(int argc, char *argv[])
{
	printf("PROCESO ID : %d (EJECUTABLE: \"%s\")\n", getpid(), argv[0]);
	printf("ARGUMENTOS : %d\n", argc);
	for(int i = 0; i < argc; i++)
	{
		printf("         %d : \"%s\"\n", i, argv[i]);
	}

	return(0);
}
