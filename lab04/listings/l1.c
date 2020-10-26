#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Przyklad uzycia lacza nienazwanego w komunikacji przodek-potomek

int main(int argc, char *argv[]) {

	int pdesk[2];
	
	if(pipe(pdesk) == -1) {
		perror("Tworzenie potoku");
		exit(1);
	}

	switch(fork()) {

		case -1: // blad tworzenia procesu
			perror("Tworzenie procesu");
			exit(1);

		case 0: // proces potomny
			if(write(pdesk[1], "Hallo!", 7) == -1) {
				perror("Zapis do potoku");
				exit(1);
			}
			exit(0);

		default: {// proces macierzysty
			char buf[10];
			if(read(pdesk[0], buf, 10) == -1) {
				perror("Odczyt z potoku");
				exit(1);
			}
			printf("Odczytano z potoku: %s\n", buf);
		}
	}
	
	return 0;
}