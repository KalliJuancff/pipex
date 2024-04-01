// "fork() y pipe(fd) , Hijo y padre se comunican con un pipe, C, linux"
#include <stdio.h>		// perror, printf
#include <stdlib.h>		// exit
#include <unistd.h>		// close, fork, pid_t, read, write

#define READ_END 0
#define WRITE_END 1

int main(void)
{
	int fd[2];
	pid_t pid;
	char buffer[5];
	int num_bytes;

	pipe (fd);
	pid = fork();
	if (pid == -1)
	{
		perror("Error en la ejecución del comando 'fork'.\n");
		exit(-1);
	}

	if (pid == 0)
	{
		// Proceso hijo
		close(fd[READ_END]);
		write(fd[WRITE_END], "gott", 4);
		close(fd[WRITE_END]);
		exit(0);
	}
	else
	{
		// Proceso padre
		close(fd[WRITE_END]);
		// El 'read' hace que no necesitemos utilizar la función 'wait'
		num_bytes = read(fd[READ_END], buffer, sizeof(buffer));
		buffer[num_bytes] = '\0';	
		printf("Mensaje escrito por el hijo y leído por el proceso padre: \"%s\" (%d bytes)\n", buffer, num_bytes);
		close(fd[READ_END]);
	}

	return (0);
}
