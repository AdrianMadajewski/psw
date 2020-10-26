#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// Przyklad tworzenia i otwierania lacza nazwanego

int main(int argc, char *argv[]) {
	mkfifo("kolFIFO", 0600);
	open("kolFIFO", O_RDONLY);
	return 0;
}