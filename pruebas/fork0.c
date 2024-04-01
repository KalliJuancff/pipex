// "fork(). Parte I: ,Creación de un nuevo proceso, hijos, padres, zombies y huérfanos"
#include <unistd.h>		// getpid, fork, pid_t
#include <stdio.h>		// printf
#include <stdlib.h>		// exit

int variable = 7;

int main(void)
{
	pid_t pid;

	printf("[Proceso padre (PID = %d)] ¡Hola, soy papá! :-D  NOTA: Esta línea es anterior a 'fork', por lo que se ejecuta 1 sola vez.\n", getpid());

	pid = fork();
	if (pid == -1)
	{
		perror("La llamada a 'fork' falló");
		exit(-1);
	}

	printf("        [Proceso PID = %d] Ejecutando línea tras 'fork'. Valor de variable: %d (el inicial).  NOTA: Esta línea se ejecuta 2 veces.\n", getpid(), variable);

	if (pid > 0)
	{
		variable = 77;
		printf("[Proceso padre (PID = %d)] Ejecutando línea en 'IF (PID > 0)'.  Valor de variable: %d\n", getpid(), variable);
	}
	else
	{
		variable = 777;
		printf(" [Proceso hijo (PID = %d)] Ejecutando línea en 'ELSE (PID == 0)'.   Valor de variable: %d\n", getpid(), variable);
	}

	while (1)
	{
		sleep(1);
		printf("        [Proceso PID = %d] Ejecutando bucle while...  Valor de variable: %d\n", getpid(), variable);
	}

	return (0);
}
