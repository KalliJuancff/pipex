// "execv(...): llamada al sistema, familia "exec". Linux, C"
#include <stdio.h>		// printf
#include <unistd.h>		// execv, getpid

char nombre_proceso[] = "./execv0b.out";

int main(int argc, char *argv[])
{
	printf("PROCESO ID : %d (EJECUTABLE: \"%s\")\n", getpid(), argv[0]);
	printf("      NOTA : A continuación se ejecutará \"%s\". El proceso ejecutado tendrá el MISMO pid.\n", nombre_proceso);
	printf("\n");

	char *argv_exec[] = {nombre_proceso, "--g", "--o", "--tt", NULL};
	execv(nombre_proceso, argv_exec);

	// NOTA:
	// La ejecución sólo llegará a esta línea cuando la llamada a 'execv' falle. Si no falla, la siguiente línea nunca se ejecutará
	perror("La ejecución falló");

	return(-1);


	argc++;  // Evitamos el warning por no utilizar argc
}
