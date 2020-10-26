#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX 512

// Konwersja wyniku polecenia ls

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
			char buf[MAX];
			int lb, i;

			close(pdesk[1]);


			while((lb = read(pdesk[0], buf, MAX)) > 0) {
				for(i = 0; i < lb; i++) {
					buf[i] = toupper(buf[i]);
					if(write(1, buf, lb) == -1) {
						perror("Zapis na standardowe wyjscie");
						exit(1);
					}
				}
			}
			if(lb == -1) {
				perror("Odczyt z potoku");
				exit(1);
			}
		}
	}
	
	return 0;
}