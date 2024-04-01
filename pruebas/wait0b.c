// "fork(). Parte II. wait, fork, exit status, múltiples hijos"

/*
	NOTA:
	El siguiente experimento, fallido, tiene una salida distinta cuando la salida se realiza por pantalla (stdout) a
	cuando la salida se redirecciona a un fichero.
	En el primer caso, los mensajes "Deteniendo proceso hijo (...)" se entremezclan, mientras que en el segundo caso
	son mostrados todos secuencialmente al inicio de la salida.
	Por lo visto el problema radica en que los procesos hijo y el proceso padre comparten la salida estándar (stdout), y
	cuando varios procesos escriben en stdout simultáneamente, puede ocurrir esta mezcla de mensajes.
	Una posible solución sería redirigir la salida estándar de cada proceso hijo a un fichero y después de que el
	proceso padre espere a que cada hijo termine, lea y muestre la salida del fichero correspondiente al hijo.
	Lógicamente esto lo probará mi descendencia, no un servidor, que en lugar de estar programando 'pipex', se está
	entreteniendo en probar los distintos comandos asociados (lo que otros dirían "enredando, estás enredando, JC!")
*/

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
