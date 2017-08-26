#include <signal.h>
#include <libgen.h>
#include "tlpi_header.h"

#define CMD_SIZE 200

int main(int argc, char *argv[])
{
	char cmd[CMD_SIZE];
	pid_t childPid;

	setbuf(stdout, NULL);

	printf("Parent PID=%ld\n");

	switch(childPid = fork()) {
		case -1:
			printf("FORK FAIL");
		case 0:
			printf("Child (PID=%ld) exiting\n", (long) getpid());

		default:
			sleep(3);
			snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
			system(cmd);

			if(kill(childPid, SIGKILL) == -1)
				printf("KILL FAIL");

			sleep(3);
			printf("After sending SIGKILL to zombie (PID=%ld):\n", (long) childPid);
			system(cmd);
	}
}