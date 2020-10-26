#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

// Programowa realizacja potoku ls | tr a-z A-Z na laczu nienazwanym

int main(int argc, char *argv[]) {

	int pdesk[2];
	
	if(pipe(pdesk) == -1) {
		perror("Tworzenie potoku");
		exit(1);
	}

	switch(fork()) {
		case -1:
			perror("Tworzenie procesu");
			exit(1);
		case 0: // Proces potomny
			dup2(pdesk[1], 1);
			execvp("ls", argv);

			perror("Uruchomienie programu ls");
			exit(1);
		default: { // Proces macierzysty
			close(pdesk[1]);
			dup2(pdesk[0], 0);
			execlp("tr", "tr", "a-z", "A-Z", NULL);
			perror("Uruchomienie programu tr");
			exit(1);
		}
	}
	
	return 0;
}