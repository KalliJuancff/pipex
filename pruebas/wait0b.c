// "fork(). Parte II. wait, fork, exit status, múltiples hijos"
#include <stdio.h>		// perror, printf
#include <stdlib.h>		// exit, srand, rand, wait, WEXITSTATUS
#include <unistd.h>		// fork, getpid, pid_t, sleep

#define NUM_CHILDREN 4

int obtener_numero_aleatorio(int numero_maximo)
{
	int retorno;

	srand(getpid());
	retorno = (rand() % (numero_maximo + 1));

	return (retorno);
}

void salir_con_codigo_de_salida_y_espera_aleatorios(void)
{
	int codigo_salida = obtener_numero_aleatorio(126) + 1;
	int segs_pausa = obtener_numero_aleatorio(2) * 5;  // 0 (sin pausa), 5 o 10 segundos de pausa

	printf("    Deteniendo proceso hijo [PID = %d] durante %d segundos...\n", getpid(), segs_pausa);
	sleep(segs_pausa);
	exit(codigo_salida);
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
			salir_con_codigo_de_salida_y_espera_aleatorios();
	}

	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		printf("Proceso padre [PID = %d] esperando que finalice el hijo #%d.\n", getpid(), i+1);
		pid = wait(&status);
		printf("    Finalizado proceso hijo [PID = %d] con código de salida %d.\n", pid, WEXITSTATUS(status));
	}

	return (0);
}
