#include <unistd.h>		// getpid, fork, pid_t
#include <stdio.h>		// printf
#include <stdlib.h>		// exit

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

	printf("        [Proceso PID = %d] Ejecutando línea tras 'fork'.  NOTA: Esta línea se ejecuta 2 veces.\n", getpid());

	if (pid == 0)
		printf(" [Proceso hijo (PID = %d)] Ejecutando línea en 'IF (PID == 0)'.\n", getpid());	
	else
		printf("[Proceso padre (PID = %d)] Ejecutando línea en 'ELSE (PID > 0)'.\n", getpid());	

	while (1)
	{
		sleep(1);
		printf("        [Proceso PID = %d] Ejecutando bucle while...\n", getpid());
	}

	return (0);
}
