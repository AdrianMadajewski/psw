#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>


// Programowa realizacja potoku ls | tr a-z A-Z na laczu nazwanym

int main(int argc, char *argv[]) {
	int pdesk;

	if(mkfifo("/tmp/fifo", 0600) == -1) {
		perror("Tworzenie kolejki FIFO");
		exit(1);
	}

	switch(fork()) {
		case -1:
			perror("Tworzenie procesu");
			exit(1);
		
		case 0:
			close(1);
			pdesk = open("/tmp/fifo", O_WRONLY);
			if(pdesk == -1) {
				perror("Otwarcie potoku do zapisu");
				exit(1);
			}
			else if(pdesk != 1) {
				fprintf(stderr, "Niewlasciwy deskryptor do zapisu\n");
				exit(1);
			}

			execvp("ls", argv);
			perror("Uruchomienie programu ls");
			exit(1);

		default: {
			close(0);
			pdesk = open("/tmp/fifo", O_RDONLY);
			if(pdesk== -1) {
				perror("Otwarcie potoku do odczytu");
				exit(1);
			}
			else if(pdesk != 0) {
				fprintf(stderr, "Niewlasciwy deskryptor do odczytu\n");
				exit(1);
			}
			execlp("tr", "tr", "a-z", "A-Z", NULL);
			perror("Uruchomienie programu tr");
			exit(1);
		}
	}


	return 0;
}