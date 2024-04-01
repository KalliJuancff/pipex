// "Comunicar dos procesos "ls -l" y "wc" con un pipe y redireccionar la salida a un archivo de texto."
#include <fcntl.h>		// open, O_WRONLY
#include <stdlib.h>		// wait
#include <unistd.h>		// close, execlp, fork, pid_t

#define READ_END 0
#define WRITE_END 1

// NOTA IMPORTANTE:
// Este fichero, ¡debe existir!
#define FILE_NAME "output.txt"

int main(void)
{
	int fd1[2], fd2, status, pid;

	// Para comunicar el comando "ls" con el comando "wc"
	pipe(fd1);

	pid = fork();

	if(pid == 0)
	{
		// Proceso hijo

		close(fd1[READ_END]);

		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);

		execlp("/bin/ls", "ls", "-l", NULL);
	}
	else
	{
		// Proceso padre
		close(fd1[WRITE_END]);
		
		pid = fork();

		if(pid == 0)
		{
			// [Segundo] Proceso hijo

			fd2 = open(FILE_NAME, O_WRONLY);

			dup2(fd1[READ_END], STDIN_FILENO);
			close(fd1[READ_END]);

			dup2(fd2, STDOUT_FILENO);

			execlp("/usr/bin/wc", "wc", NULL);
		}
		else
			close(fd1[READ_END]);
	}

	// Un wait por cada hijo
	wait(&status);
	wait(&status);

	return(0);
}
