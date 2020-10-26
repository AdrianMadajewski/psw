#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Przyklad odczytu z pustego lacza

int main(int argc, char *argv[]) {

	int pdesk[2];
	pipe(pdesk);

	if(fork() == 0) { // Proces potomny
		write(pdesk[1], "Hallo!", 7);
		exit(0);
	} else {
		char buf[10];
		read(pdesk[0], buf, 10);
		read(pdesk[0], buf, 10);
		printf("Odczytano z potoku: %s\n", buf);
	}
	
	return 0;
}