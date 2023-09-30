#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	int choice;
	printf("1 for zombie or 2 for orphan process ");
	scanf("%d", &choice);
	// zombie process
	if (choice == 1)
	{
		pid_t child_pid = fork();

		// parent process
		if (child_pid > 0)
		{
			sleep(2);
			printf("this is parent process --zombie\n");
		}

		// Child process
		else if (child_pid == 0)
			printf("this is child process\n");
	}

	// orphan process

	if (choice == 2)
	{
		int pid = fork();
		// parent process
		if (pid > 0)
			printf("in parent process\n");
		else if (pid == 0)
		{ // child process
			sleep(2);
			printf("in child process--orphan\n");
		}
	}
	return 0;
}
