#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>


// Przyklad tworzenia i otwierania lacza nazwanego

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
		case 0: // Proces potomny
			pdesk = open("/tmp/fifo", O_WRONLY);
			if(pdesk == -1) {
				perror("Otwarcie potoku do zapisu");
				exit(1);
			}

			if(write(pdesk, "Hallo!", 7) == -1) {
				perror("Zapis do potoku");
				exit(1);
			}
			exit(0);
		default: // Proces macierzysty
		{
			char buf[10];
			pdesk = open("/tmp/fifo", O_RDONLY);
			if(pdesk == -1) {
				perror("Otwarcie potoku do odczytu");
				exit(1);
			}

			if(read(pdesk, buf, 10) == -1) {
				perror("Odczyt z potoku");
				exit(1);
			}

			printf("Odczytano z potoku: %s\n", buf);
		}
	}

	return 0;
}