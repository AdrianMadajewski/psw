#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 512

int main(int argc, char *argv[]) {
	char buffer[MAX];

	if(argc != 3) {
		perror("Za malo argumentow");
		exit(1);
	}

	if(close(1) == -1) {
		perror("Blad zamkniecia stdout");
		exit(1);
	}

	if((open(argv[2], O_CREAT | O_RDWR, 0644)) == -1) {
		sprintf(buffer, "Wystapil blad otwierania pliku %s\n", argv[2]);
		perror(buffer);
		exit(1);
	}

	int n = atoi(argv[1]);
	int result = 1;
	int desc;

	if(n < 0) {
		perror("Bledna liczba");
		exit(1);
	}

	for(int i = 1; i <= n; i++) {
		result *= i;
	}

	printf("%d\n", result);

	sprintf(buffer, "Wynik %d", result);
	perror(buffer);

	freopen("/dev/tty", "w", stdout);

	return 0;
}