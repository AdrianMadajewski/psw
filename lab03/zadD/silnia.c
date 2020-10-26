#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	if(argc != 3) {
		perror("Za malo argumentow");
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
		sleep(5);
	}

	printf("%d\n", result);

	if((desc = open(argv[2], O_CREAT | O_RDWR, 0644)) == -1) {
		perror("Wystapil blad otwarcia pliku");
		exit(1);
	}

	if(write(desc, &result, sizeof(result)) == -1) {
		perror("Blad zapisu wyniku");
		exit(1);
	}

	if(close(desc) == -1) {
		perror("Blad zamkniecia pliku");
		exit(1);
	}

	return 0;
}