// "fork(). Parte II. wait, fork, exit status, múltiples hijos"
#include <stdio.h>		// perror, printf
#include <stdlib.h>		// exit, srand, rand, wait, WEXITSTATUS
#include <unistd.h>		// fork, getpid, pid_t

#define NUM_CHILDREN 7

int obtener_numero_salida_aleatorio(void)
{
	int retorno;

	srand(getpid());
	retorno = (rand() % 256);

	return (retorno);
}

int main(void)
{
	pid_t pid;
	int status;

	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error al ejecutar 'fork'");
			exit(-1);
		}
		if(pid > 0)
			continue;
		else if (pid == 0)
		{
			int codigo_salida = obtener_numero_salida_aleatorio();
			exit(codigo_salida);
		}
	}

	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		printf("Proceso padre [PID = %d] esperando que finalice el hijo #%d.\n", getpid(), i+1);
		pid = wait(&status);
		printf("    Finalizado proceso hijo [PID = %d] con código de salida %d.\n", pid, WEXITSTATUS(status));
	}

	return (0);
}
